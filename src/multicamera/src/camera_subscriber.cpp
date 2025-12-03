#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <mutex>
#include <memory>

class CameraSubscriber : public rclcpp::Node
{
public:
    CameraSubscriber()
        : Node("camera_subscriber")
    {
        // Lista de tópicos de cámaras (modifica según tu setup)
        std::vector<std::string> topic_names = { "/camera/image_raw/compressed" };

        // Inicializar vectores de mutex y frames
        camera_mutexes_.resize(topic_names.size());
        frames_.resize(topic_names.size());

        for (auto &m : camera_mutexes_) {
            m = std::make_unique<std::mutex>();
        }

        // Crear subscribers
        for (size_t i = 0; i < topic_names.size(); ++i)
        {
            subscribers_.push_back(
                this->create_subscription<sensor_msgs::msg::CompressedImage>(
                    topic_names[i], 10,
                    [this, i](sensor_msgs::msg::CompressedImage::SharedPtr msg)
                    {
                        this->imageCallback(msg, i);
                    }
                )
            );

            RCLCPP_INFO(this->get_logger(), "Suscrito al tópico: %s",
                        topic_names[i].c_str());
        }

        // Timer para mostrar imágenes
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&CameraSubscriber::displayFrames, this)
        );
    }

private:
    void imageCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg, int cam_id)
    {
        if (!msg || msg->data.empty()) {
            RCLCPP_WARN(this->get_logger(), "Mensaje vacío en cámara %d", cam_id);
            return;
        }

        // Copiar datos a vector temporal
        std::vector<uint8_t> jpeg_buffer(msg->data.begin(), msg->data.end());
        cv::Mat jpeg(1, static_cast<int>(jpeg_buffer.size()), CV_8UC1, jpeg_buffer.data());
        cv::Mat frame = cv::imdecode(jpeg, cv::IMREAD_COLOR);

        if (frame.empty()) {
            RCLCPP_WARN(this->get_logger(),
                        "Error decodificando imagen de la cámara %d", cam_id);
            return;
        }

        // Guardar frame de forma segura
        std::lock_guard<std::mutex> lock(*camera_mutexes_[cam_id]);
        frames_[cam_id] = frame;
    }

    void displayFrames()
    {
        for (size_t i = 0; i < frames_.size(); ++i)
        {
            std::lock_guard<std::mutex> lock(*camera_mutexes_[i]);
            if (!frames_[i].empty())
                cv::imshow("Camera " + std::to_string(i), frames_[i]);
        }
        cv::waitKey(1);
    }

    // Vectores de mutex y frames por cámara
    std::vector<std::unique_ptr<std::mutex>> camera_mutexes_;
    std::vector<cv::Mat> frames_;

    // Vectores de subscribers
    std::vector<rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr> subscribers_;

    // Timer para mostrar frames
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CameraSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    cv::destroyAllWindows();
    return 0;
}