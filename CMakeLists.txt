cmake_minimum_required(VERSION 3.0.2)
project(control_wheels)
set(CMAKE_CXX_STANDARD 14) # C++14...
## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy geometry_msgs genmsg)
find_package(Threads REQUIRED)

# add_subdirectory(src)
include_directories(src)
## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES geometry_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

## wheels_listener
add_executable(wheels_listener src/wheels_listener)
target_link_libraries(wheels_listener ${catkin_LIBRARIES})
target_link_libraries(wheels_listener Threads::Threads)
target_link_libraries(wheels_listener pigpiod_if2)
add_dependencies(wheels_listener control_wheels_generate_messages_cpp)