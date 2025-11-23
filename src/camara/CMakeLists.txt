cmake_minimum_required(VERSION 3.5)  # Siempre debe ser la primera línea
project(camara)  # Obligatorio

# Buscar dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

# Ejecutables
add_executable(camara_node src/camara_node.cpp)
add_executable(subscriber src/subscriber.cpp)

# Enlazar dependencias de ROS 2
ament_target_dependencies(camara_node
  rclcpp
  std_msgs
  sensor_msgs
  image_transport
)

ament_target_dependencies(subscriber
  rclcpp
  std_msgs
  sensor_msgs
  image_transport
)

# Enlazar OpenCV
target_include_directories(camara_node PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(camara_node ${OpenCV_LIBRARIES})

target_include_directories(subscriber PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(subscriber ${OpenCV_LIBRARIES})

# Instalar los ejecutables
install(TARGETS
  camara_node
  subscriber
  DESTINATION lib/${PROJECT_NAME}
)

# Obligatorio para paquetes ROS 2
ament_package()

