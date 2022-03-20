cmake_minimum_required (VERSION 3.9)
project(test LANGUAGES CUDA CXX)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CUDA_FLAGS_DEBUG "${CMAKE_CUDA_FLAGS_DEBUG} -G")

set(TESTS 
    sobel.cpp
)

add_executable(${PROJECT_NAME} ${TESTS})

target_link_libraries(
    ${PROJECT_NAME}
    image
    rgb2gray
    sobel
    ${CUDA_LIBRARIES}
)