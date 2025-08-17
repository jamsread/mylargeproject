# 子项目不需要重新设置这些，从主 CMakeLists.txt 继承
# cmake_minimum_required(VERSION 3.18)
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#     CACHE STRING "Vcpkg toolchain file")
# set(VCPKG_MANIFEST_MODE ON)
# set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
# project(MyLargeProject LANGUAGES CXX)

# 设置自动工具
set(CMAKE_AUTOMOC ON)  # 对于 Qt 项目
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找所有依赖包
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS filesystem system thread REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

# 添加可执行文件
add_executable(my_large_app main.cpp)

# 设置 C++ 标准
target_compile_features(my_large_app PRIVATE cxx_std_17)

# 添加编译定义用于测试
target_compile_definitions(my_large_app PRIVATE ENABLE_TESTS)

# 包含目录（如果需要的话）
# target_include_directories(my_large_app PRIVATE src)

# 链接所有依赖
target_link_libraries(my_large_app PRIVATE
    Qt5::Core
    Qt5::Widgets
    ${OpenCV_LIBS}
    Boost::filesystem
    Boost::system
    Boost::thread
    Eigen3::Eigen
    fmt::fmt
    GTest::gtest
    GTest::gtest_main
)

# 设置输出目录
setup_project_output_dirs(my_large_app)

# 添加测试
enable_testing()
add_test(NAME MyTests COMMAND my_app --tests)