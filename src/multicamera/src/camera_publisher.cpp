#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class MultiCameraPublisher : public rclcpp::Node
{
public:
    MultiCameraPublisher() : Node("multicamera_publisher")
    {
        // Configura las cámaras que quieres publicar
        camera_ids_ = {0, 1}; // Cambia según tus cámaras conectadas

        for (size_t i = 0; i < camera_ids_.size(); ++i) {
            std::string topic_name = "camera_" + std::to_string(i) + "/image_raw";
            publishers_.push_back(image_transport::create_publisher(this, topic_name));

            cv::VideoCapture cap(camera_ids_[i]);
            if (!cap.isOpened()) {
                RCLCPP_ERROR(this->get_logger(), "No se pudo abrir la cámara %d", camera_ids_[i]);
            } else {
                caps_.push_back(std::move(cap));
            }
        }

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(30),
            std::bind(&MultiCameraPublisher::publishFrames, this)
        );
    }

private:
    void publishFrames()
    {
        for (size_t i = 0; i < caps_.size(); ++i) {
            cv::Mat frame;
            caps_[i] >> frame;
            if (frame.empty()) continue;

            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
            publishers_[i].publish(msg);
        }
    }

    std::vector<int> camera_ids_;
    std::vector<cv::VideoCapture> caps_;
    std::vector<image_transport::Publisher> publishers_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MultiCameraPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
