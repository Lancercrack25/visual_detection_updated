cmake_minimum_required(VERSION 3.5)
project(rocket)  # Asegúrate de que coincida con <name> en package.xml

# Requiere C++14 o superior
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)

# Ejecutable 1
add_executable(rocks_node src/rocks_node.cpp)
ament_target_dependencies(rocks_node
  rclcpp
  std_msgs
  sensor_msgs
  image_transport
)
target_include_directories(rocks_node PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(rocks_node ${OpenCV_LIBRARIES})

# Ejecutable 2
add_executable(subscriberock src/subscriberock.cpp)
ament_target_dependencies(subscriberock
  rclcpp
  std_msgs
  sensor_msgs
  image_transport
)
target_include_directories(subscriberock PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(subscriberock ${OpenCV_LIBRARIES})

# Instalar ejecutables
install(TARGETS
  rocks_node
  subscriberock
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()