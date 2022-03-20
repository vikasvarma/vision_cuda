cmake_minimum_required (VERSION 3.9)
project(image LANGUAGES CUDA CXX)
set (CMAKE_CXX_STANDARD 20)

set(SOURCE "image.cpp")
set(HEADER "image.h" "stb_image.h" "stb_image_write.h")

add_library(
    ${PROJECT_NAME} 
    STATIC 
    ${SOURCE} 
    ${HEADER}
)