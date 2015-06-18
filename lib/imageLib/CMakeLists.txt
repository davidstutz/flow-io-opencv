cmake_minimum_required(VERSION 2.8)

add_library(flow_io_imagelib RefCntMem.cpp Image.cpp ImageIO.cpp ImageIOpng.cpp Convolve.cpp Convert.cpp)
