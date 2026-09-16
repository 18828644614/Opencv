cmake_minimum_required(VERSION 3.20)
project(program2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "D:/opencv/opencv/build")
find_package(OpenCV REQUIRED)

add_executable(program2 opencv.cpp)
target_link_libraries(program2 PRIVATE ${OpenCV_LIBS})