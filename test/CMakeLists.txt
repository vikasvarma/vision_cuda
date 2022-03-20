cmake_minimum_required (VERSION 3.9)
project(test LANGUAGES CUDA CXX)
set(TESTS 
    sobel.cpp
)

add_executable(${PROJECT_NAME} ${TESTS})

#message(STATUS "${PROJECT_NAME} | Including directory: ${INCLUDE_DIR}")
#target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(
    ${PROJECT_NAME}
    image
    rgb2gray
    sobel
    ${CUDA_LIBRARIES}
)