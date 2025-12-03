#!/home/luis/my_venv/bin/python
import os
import time
import cv2
import numpy as np
import torch
import threading
from ultralytics import YOLO
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge
from iarocks_py.logger import Logger

class OptimizedDetectionNode(Node):
    def __init__(self):
        super().__init__("detection_node")

        # Logger setup
        log_dir = "inference"
        os.makedirs(log_dir, exist_ok=True)
        self.logger = Logger(log_dir)

        # Device setup
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        self.get_logger().info(f"Using device: {self.device}")

        # Parameters
        self.declare_parameter("detection_conf", 0.50)
        self.declare_parameter("classification_conf", 0.60)
        self.declare_parameter("target_fps", 15)
        self.declare_parameter("inference_size", 224)

        self.detection_conf = self.get_parameter("detection_conf").get_parameter_value().double_value
        self.classification_conf = self.get_parameter("classification_conf").get_parameter_value().double_value
        self.target_fps = self.get_parameter("target_fps").get_parameter_value().integer_value
        self.inference_size = self.get_parameter("inference_size").get_parameter_value().integer_value

        # Load models
        self.load_models()

        # ROS interfaces
        self.bridge = CvBridge()
        self.pub = self.create_publisher(CompressedImage, "/rocks_image", 2)
        self.sub = self.create_subscription(
            CompressedImage, "/camara/rock_image/compressed", self.callback, 1
        )

        # Frame buffer and threading
        self.frame_queue = []
        self.queue_lock = threading.Lock()
        self.processing_thread = threading.Thread(target=self.processing_loop, daemon=True)
        self.processing_thread.start()

        self.last_processed_time = 0.0
        self.get_logger().info("Optimized detection node initialized.")

    # -------------------------------------------------------------------------
    # Model loading
    # -------------------------------------------------------------------------
    def load_models(self):
        try:
            base_path = os.path.dirname(os.path.abspath(__file__))
            model_path = os.path.join(base_path, "modelos")

            # Detection and classification models
            self.detection_model = YOLO(os.path.join(model_path, "detection", "rock-dect-100.pt"))
            self.class_model = YOLO(os.path.join(model_path, "classification", "best-class-44.pt"))

            for model in [self.detection_model, self.class_model]:
                model.fuse()
                model.to(self.device)

            self.get_logger().info("Models loaded successfully.")
        except Exception as e:
            self.get_logger().error(f"Failed to load models: {e}")
            rclpy.shutdown()

    # -------------------------------------------------------------------------
    # Frame receiving callback
    # -------------------------------------------------------------------------
    def callback(self, msg: CompressedImage):
        """Receives compressed images and adds them to the queue."""
        np_arr = np.frombuffer(msg.data, np.uint8)
        frame = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

        with self.queue_lock:
            # Keep only the most recent frame
            self.frame_queue = [frame]

    # -------------------------------------------------------------------------
    # Separate thread for processing
    # -------------------------------------------------------------------------
    def processing_loop(self):
        """Processes frames in a separate thread."""
        while rclpy.ok():
            frame = None
            with self.queue_lock:
                if self.frame_queue:
                    frame = self.frame_queue.pop(0)

            if frame is not None:
                try:
                    current_time = time.time()
                    if current_time - self.last_processed_time < 1.0 / self.target_fps:
                        continue
                    self.last_processed_time = current_time

                    annotated_frame, detected = self.process_frame(frame)

                    if detected:
                        self.logger.saveDetection(annotated_frame)

                    _, jpeg_frame = cv2.imencode(".jpg", annotated_frame, [int(cv2.IMWRITE_JPEG_QUALITY), 85])
                    compressed_msg = CompressedImage()
                    compressed_msg.header.stamp = self.get_clock().now().to_msg()
                    compressed_msg.format = "jpeg"
                    compressed_msg.data = jpeg_frame.tobytes()
                    self.pub.publish(compressed_msg)

                except Exception as e:
                    self.get_logger().warn(f"Error during frame processing: {e}")

            time.sleep(0.005)

    # -------------------------------------------------------------------------
    # Frame processing (detection + classification)
    # -------------------------------------------------------------------------
    def process_frame(self, original_frame):
        resized_frame = cv2.resize(original_frame, (self.inference_size, self.inference_size))

        with torch.no_grad():
            resized_frame = resized_frame.astype(np.float32) / 255.0
            resized_frame = np.transpose(resized_frame, (2, 0, 1))
            resized_frame = torch.tensor(resized_frame).unsqueeze(0).to(self.device)

            detections = self.detection_model.predict(
                resized_frame,
                imgsz=self.inference_size,
                conf=self.detection_conf,
                device=self.device,
                verbose=False,
            )

        scale_x = original_frame.shape[1] / self.inference_size
        scale_y = original_frame.shape[0] / self.inference_size
        detected = False

        for detection in detections:
            for box in detection.boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0].tolist())
                x1, y1, x2, y2 = int(x1 * scale_x), int(y1 * scale_y), int(x2 * scale_x), int(y2 * scale_y)
                label = detection.names[int(box.cls.item())]
                conf = box.conf.item()

                if label.lower() == "float_rock" and conf > 0.7:
                    detected = True
                    rock_img = original_frame[y1:y2, x1:x2]
                    if rock_img.size > 0:
                        class_label = self.classify_rock(rock_img)
                        cv2.rectangle(original_frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        cv2.putText(
                            original_frame,
                            f"{class_label}: {conf:.2f}",
                            (x1, y1 - 10),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.8,
                            (0, 255, 0),
                            2,
                        )

        return original_frame, detected

    # -------------------------------------------------------------------------
    # Classification handling for YOLOv8 and fallback support
    # -------------------------------------------------------------------------
    def classify_rock(self, rock_img):
        """Runs rock classification using YOLO classification model."""
        resized_rock = cv2.resize(rock_img, (224, 224))
        resized_rock = resized_rock.astype(np.float32) / 255.0
        rock_tensor = torch.from_numpy(resized_rock).float().permute(2, 0, 1).unsqueeze(0).to(self.device)

        with torch.no_grad():
            outputs = self.class_model(rock_tensor)

            # Some YOLO versions return a list
            if isinstance(outputs, list):
                outputs = outputs[0]

            # Ultralytics v8+ classification: outputs.probs is a Probs object
            if hasattr(outputs, "probs"):
                probs = outputs.probs
                # Convert Probs to tensor if needed
                if hasattr(probs, "data"):
                    probs = probs.data
                predicted_class = torch.argmax(probs).item()

            elif hasattr(outputs, "logits"):
                probs = torch.softmax(outputs.logits, dim=1)
                predicted_class = torch.argmax(probs).item()

            elif isinstance(outputs, torch.Tensor):
                _, predicted_class = torch.max(outputs, dim=1)

            else:
                self.get_logger().warn("Unknown classification output format.")
                return "Unknown"

        class_names = ["Gypsum", "Shale", "Sandstone", "Limestone"]
        return class_names[predicted_class]

    # -------------------------------------------------------------------------
    # Main ROS entry
    # -------------------------------------------------------------------------
def main(args=None):
    rclpy.init(args=args)
    node = OptimizedDetectionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
