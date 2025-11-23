#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class CameraSubscriberNode : public rclcpp::Node
{
public:
    CameraSubscriberNode() : Node("camera_subscriber_node")
    {
        // Suscribirse al tópico /camara/image/compressed
        image_sub_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
            "/camara/image/compressed", 10, std::bind(&CameraSubscriberNode::image_callback, this, std::placeholders::_1));
    }

private:
    void image_callback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
    {
        // Descomprimir la imagen desde los datos comprimidos (JPEG)
        std::vector<uchar> buffer(msg->data.begin(), msg->data.end());  // Convertir los datos del mensaje a un vector de uchar
        cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);  // Descomprimir la imagen JPEG

        if (img.empty()) {
            RCLCPP_ERROR(this->get_logger(), "No se pudo descomprimir la imagen.");
            return;
        }

        // Mostrar la imagen en una ventana
        cv::imshow("Camara", img);
        cv::waitKey(1);  // Esperar 1 ms para que OpenCV procese la ventana
    }

    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr image_sub_;  // Suscriptor
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    cv::namedWindow("Camara", cv::WINDOW_NORMAL);  // Crear una ventana para mostrar la imagen
    rclcpp::spin(std::make_shared<CameraSubscriberNode>());
    cv::destroyWindow("Camara");  // Cerrar la ventana de OpenCV al terminar
    rclcpp::shutdown();
    return 0;
}