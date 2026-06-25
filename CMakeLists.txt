cmake_minimum_required(VERSION 3.5)
project(ipp_rviz_visuals)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -O2 -fPIC)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

add_executable(robot_marker_publisher src/robot_marker_publisher.cpp)
ament_target_dependencies(robot_marker_publisher
  rclcpp
  geometry_msgs
  visualization_msgs
)
install(
  TARGETS robot_marker_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
