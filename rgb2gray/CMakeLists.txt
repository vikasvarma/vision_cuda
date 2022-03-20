cmake_minimum_required (VERSION 3.9)
project(rgb2gray LANGUAGES CUDA CXX)
set (CMAKE_CXX_STANDARD 20)

set(SOURCE "rgb2gray.cu")
set(HEADER "rgb2gray.h")

add_library(
    ${PROJECT_NAME} 
    STATIC 
    ${SOURCE} 
    ${HEADER}
)

#message(STATUS "${PROJECT_NAME} | Including directory: ${INCLUDE_DIR}")
#target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(
    ${PROJECT_NAME} 
    image
    ${CUDA_LIBRARIES}
)
