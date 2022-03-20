cmake_minimum_required (VERSION 3.9)
project(vision_cuda LANGUAGES CUDA CXX)
set (CMAKE_CXX_STANDARD 20)

find_package(CUDAToolkit REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CUDA_FLAGS_DEBUG "${CMAKE_CUDA_FLAGS_DEBUG} -G")

add_subdirectory(image)
add_subdirectory(rgb2gray)
add_subdirectory(sobel)
add_subdirectory(test)