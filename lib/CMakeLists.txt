cmake_minimum_required(VERSION 2.8)

add_subdirectory(imageLib)

find_package(OpenCV REQUIRED)
include_directories(./imageLib/ ${OpenCV_INCLUDE_DIRS})

add_library(flow_io flowIO.cpp flowIO.h colorcode.cpp motiontocolor.cpp flowIOOpenCVWrapper.cpp)
target_link_libraries(flow_io flow_io_imagelib ${OpenCV_LIBRARIES})
