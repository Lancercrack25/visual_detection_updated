#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class MultiCameraSubscriber : public rclcpp::Node
{
public:
    MultiCameraSubscriber() : Node("multicamera_subscriber")
    {
        int num_cameras = 2; // Igual que en el publicador
        for (int i = 0; i < num_cameras; ++i) {
            std::string topic_name = "camera_" + std::to_string(i) + "/image_raw";
            auto sub = image_transport::create_subscription(
                this,
                topic_name,
                std::bind(&MultiCameraSubscriber::imageCallback, this, std::placeholders::_1, i),
                "raw"
            );
            subscribers_.push_back(sub);
        }
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr &msg, int cam_id)
    {
        cv::Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::imshow("Camera " + std::to_string(cam_id), frame);
        cv::waitKey(1);
    }

    std::vector<image_transport::Subscriber> subscribers_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MultiCameraSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
