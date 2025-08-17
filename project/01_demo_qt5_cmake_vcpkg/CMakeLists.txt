# 子项目不需要重新设置这些，从主 CMakeLists.txt 继承
# cmake_minimum_required(VERSION 3.15)
# project(fibonacci CXX)
# set(CMAKE_CXX_STANDARD 17)

# 启用Qt的自动MOC处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)

add_executable(fibonacci main.cpp)

target_link_libraries(fibonacci
    PRIVATE
        Qt5::Core
        Qt5::Widgets
        fmt::fmt
        range-v3::range-v3
        cxxopts::cxxopts
)

# 设置输出目录
setup_project_output_dirs(fibonacci)