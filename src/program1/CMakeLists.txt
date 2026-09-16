# ============================================
# CMakeLists.txt - CMake构建配置文件
# ============================================
# 这个文件告诉CMake如何编译你的OpenCV项目
# 
# 【需要修改的地方】：
# 1. 第15行：OpenCV_DIR - OpenCV安装路径
# 2. 第23行：opencv_test - 可执行文件名称
# 3. 第23行：opencv.cpp - 源代码文件名
# ============================================

# CMake最低版本要求（一般不需要修改）
cmake_minimum_required(VERSION 3.10)

# 项目名称（可以修改成你的项目名）
project(OpenCVTest)

# ============================================
# C++标准设置
# ============================================
# 设置使用C++11标准（可改为14、17、20等）
set(CMAKE_CXX_STANDARD 11)
# 强制要求支持该标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================
# MSVC编译器UTF-8支持
# ============================================
# 如果使用MSVC编译器，添加/utf-8选项以支持中文
if(MSVC)
    add_compile_options(/utf-8)
endif()

# ============================================
# 【重要】OpenCV路径设置
# ============================================
# 修改这里：指向你的OpenCV安装目录的build文件夹
# 格式：使用正斜杠 / 而不是反斜杠 \
# 示例：
#   - D:/opencv/opencv/build
#   - C:/Libraries/opencv/build
set(OpenCV_DIR "D:/opencv/opencv/build")

# ============================================
# 查找OpenCV库
# ============================================
# REQUIRED表示如果找不到OpenCV就报错停止
find_package(OpenCV REQUIRED)

# 包含OpenCV头文件目录（自动设置，不需要修改）
include_directories(${OpenCV_INCLUDE_DIRS})

# ============================================
# 【重要】添加可执行文件
# ============================================
# 格式：add_executable(可执行文件名 源代码文件...)
# 
# 修改示例：
# 1. 单个源文件：
#    add_executable(my_program main.cpp)
#
# 2. 多个源文件：
#    add_executable(my_program main.cpp utils.cpp image_proc.cpp)
#
# 3. 当前配置：
add_executable(opencv_test opencv.cpp)

# ============================================
# 链接OpenCV库
# ============================================
# 将OpenCV库链接到你的可执行文件（自动设置，不需要修改）
target_link_libraries(opencv_test ${OpenCV_LIBS})

# ============================================
# 快速修改指南
# ============================================
# 场景1：更换OpenCV安装位置
#   → 修改第42行的OpenCV_DIR路径
#
# 场景2：重命名你的程序
#   → 修改第57行的opencv_test为新名称
#   → 修改第62行的opencv_test为新名称
#
# 场景3：添加更多源文件
#   → 在第57行添加文件名，用空格分隔
#   → 例如：add_executable(opencv_test opencv.cpp utils.cpp)
#
# 场景4：更换源文件名
#   → 修改第57行的opencv.cpp为新文件名
# ============================================
