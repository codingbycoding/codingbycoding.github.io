cmake_minimum_required(VERSION 2.8)
set(MY_PROJECT_NAME my_opencv)
project(${MY_PROJECT_NAME})
find_package(OpenCV REQUIRED)

# This version number
set(${MY_PROJECT_NAME}_VERSION_MAJOR 0)
set(${MY_PROJECT_NAME}_VERSION_MINOR 1)

add_executable(${MY_PROJECT_NAME} opencv.cpp)
target_link_libraries(${MY_PROJECT_NAME} ${OpenCV_LIBS})