#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "std_msgs/msg/header.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std::chrono_literals;

class CamaraNode : public rclcpp::Node
{
public:
    CamaraNode() : Node("rocks_node")
    {
        // Crear el publicador de imágenes comprimidas
        image_pub_ = this->create_publisher<sensor_msgs::msg::CompressedImage>(
            "/camara/rock_image/compressed", 1);

        // Configurar el temporizador para publicar una imagen cada 1 segundo
        timer_ = this->create_wall_timer(
            50ms, std::bind(&CamaraNode::captura_imagen, this));

        // Abrir la cámara
        cap_.open(0);  // 0 para usar la cámara por defecto
        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "No se pudo abrir la cámara");
            rclcpp::shutdown();
        }
    }

private:
    void captura_imagen()
    {
        cv::Mat frame;
        cap_ >> frame;  // Captura un frame de la cámara
        if (frame.empty()) {
            RCLCPP_ERROR(this->get_logger(), "No se pudo capturar una imagen");
            return;
        }

        // Comprimir la imagen usando OpenCV
        std::vector<uchar> buf;
        std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 90};
        cv::imencode(".jpg", frame, buf, params);

        // Crear mensaje CompressedImage
        auto msg = std::make_shared<sensor_msgs::msg::CompressedImage>();
        msg->header.stamp = this->get_clock()->now();
        msg->header.frame_id = "camera_frame";
        msg->format = "jpeg";
        msg->data = buf;

        // Publicar la imagen
        image_pub_->publish(*msg);
    }

    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr image_pub_;
};

//  main() DEBE estar fuera de la clase
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CamaraNode>());
    rclcpp::shutdown();
    return 0;
}
