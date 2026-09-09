# CMake 与 OpenCV 链接

最小结构：

```cmake
cmake_minimum_required(VERSION 3.20)
project(opencv_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

add_executable(opencv_demo main.cpp)
target_link_libraries(opencv_demo PRIVATE ${OpenCV_LIBS})
target_include_directories(opencv_demo PRIVATE ${OpenCV_INCLUDE_DIRS})
```

推荐使用独立的 `build` 目录，避免把生成文件混入源码目录。安装路径不在系统默认位置时，可在配置时传入 `OpenCV_DIR`。
