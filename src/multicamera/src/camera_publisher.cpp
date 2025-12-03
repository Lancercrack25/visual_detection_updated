#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>

/**************************************
 *   Puerto Serial (Ubuntu 24.04 OK)
 *************************************/
class SerialPort {
public:
    SerialPort(const std::string &port, int baudrate) {
        fd_ = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
        if (fd_ < 0)
            throw std::runtime_error("No se puede abrir puerto " + port);

        struct termios tty;
        if (tcgetattr(fd_, &tty) != 0)
            throw std::runtime_error("Error leyendo atributos del puerto");

        // Configurar baudrate
        speed_t speed;
        switch (baudrate) {
            case 115200: speed = B115200; break;
            case 230400: speed = B230400; break;
            case 460800: speed = B460800; break;
            case 921600: speed = B921600; break; // algunos sistemas lo soportan
            default: speed = B115200; break;
        }

        cfsetospeed(&tty, speed);
        cfsetispeed(&tty, speed);

        tty.c_cflag &= ~CRTSCTS; // sin control de flujo
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 bits
        tty.c_cflag |= CLOCAL | CREAD;

        tty.c_iflag = IGNPAR;
        tty.c_oflag = 0;
        tty.c_lflag = 0;

        tty.c_cc[VTIME] = 1;
        tty.c_cc[VMIN]  = 0;

        if (tcsetattr(fd_, TCSANOW, &tty) != 0)
            throw std::runtime_error("Error configurando puerto serial");

        tcflush(fd_, TCIOFLUSH);
    }

    ~SerialPort() { if (fd_ >= 0) close(fd_); }

    void writeBytes(const uint8_t* data, size_t size) { ::write(fd_, data, size); }

    int available() {
        int bytes = 0;
        if (ioctl(fd_, FIONREAD, &bytes) < 0) return 0;
        return bytes;
    }

    int readBytes(uint8_t* buffer, size_t max_size) { return ::read(fd_, buffer, max_size); }

private:
    int fd_;
};

/**************************************
 *     Nodo ROS2 que publica JPEG
 *************************************/
class CameraPublisher : public rclcpp::Node {
public:
    CameraPublisher()
        : Node("camera_publisher"),
          serial_("/dev/ttyUSB0", 921600),
          streaming_(true)
    {
        RCLCPP_INFO(this->get_logger(), "Nodo de cámara iniciado (921600 baud)");

        publisher_ = this->create_publisher<sensor_msgs::msg::CompressedImage>(
            "/camera/image_raw/compressed", 10);

        // Enviar comando START_VIDEO al ESP32
        sendCommand(0, 0x02);  // 0x55 00 02 AA

        // Hilo que captura bytes del serial
        read_thread_ = std::thread(&CameraPublisher::readSerialLoop, this);
    }

    ~CameraPublisher() {
        streaming_ = false;
        if (read_thread_.joinable())
            read_thread_.join();

        // STOP_VIDEO
        sendCommand(0, 0x21);
    }

private:
    void sendCommand(uint8_t cam, uint8_t cmd) {
        uint8_t packet[4] = {0x55, cam, cmd, 0xAA};
        serial_.writeBytes(packet, 4);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    void publishFrame(const std::vector<uint8_t>& jpeg) {
        auto msg = sensor_msgs::msg::CompressedImage();
        msg.header.stamp = this->now();
        msg.format = "jpeg";
        msg.data = jpeg;
        publisher_->publish(msg);
    }

    void readSerialLoop() {
        std::vector<uint8_t> buffer;
        uint8_t temp[4096];

        while (streaming_) {
            int bytes = serial_.available();
            if (bytes <= 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                continue;
            }

            int n = serial_.readBytes(temp, std::min<size_t>(sizeof(temp), bytes));
            if (n > 0) {
                buffer.insert(buffer.end(), temp, temp + n);

                // Buscar JPEG SOI y EOI
                auto start = std::search(buffer.begin(), buffer.end(),
                                         std::begin(jpeg_start_), std::end(jpeg_start_));

                while (start != buffer.end()) {
                    auto end = std::search(start, buffer.end(),
                                           std::begin(jpeg_end_), std::end(jpeg_end_));
                    if (end != buffer.end()) {
                        end += 2; // incluir 0xFFD9

                        std::vector<uint8_t> jpeg(start, end);
                        if (jpeg.size() > 100)
                            publishFrame(jpeg);

                        buffer.erase(buffer.begin(), end);
                        start = std::search(buffer.begin(), buffer.end(),
                                            std::begin(jpeg_start_), std::end(jpeg_start_));
                    } else {
                        if (start != buffer.begin())
                            buffer.erase(buffer.begin(), start);
                        break;
                    }
                }
            }
        }
    }

    SerialPort serial_;
    bool streaming_;
    std::thread read_thread_;

    rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr publisher_;

    const uint8_t jpeg_start_[2] = {0xFF, 0xD8};
    const uint8_t jpeg_end_[2]   = {0xFF, 0xD9};
};

/**************************************
 *             MAIN
 *************************************/
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CameraPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
