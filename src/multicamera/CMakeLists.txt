cmake_minimum_required(VERSION 3.5)
project(multicamera)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencias de ROS 2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

# Directorios de inclusión
include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

# Ejecutable: Publisher
add_executable(camera_publisher src/camera_publisher.cpp)
ament_target_dependencies(camera_publisher
  rclcpp
  sensor_msgs
  cv_bridge
  image_transport
  OpenCV
)
target_link_libraries(camera_publisher ${OpenCV_LIBRARIES})

# Ejecutable: Subscriber
add_executable(camera_subscriber src/camera_subscriber.cpp)
ament_target_dependencies(camera_subscriber
  rclcpp
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
)
target_link_libraries(camera_subscriber
  ${OpenCV_LIBRARIES}
)

# Instalar los ejecutables
install(TARGETS
  camera_publisher
  camera_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
