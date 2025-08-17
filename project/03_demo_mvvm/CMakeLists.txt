cmake_minimum_required(VERSION 3.18)

# 设置 Qt 相关变量
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找 Qt5 组件 - 只需要 Core 和 Widgets
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# 创建可执行文件
add_executable(demo_mvvm
    main.cpp
    src/mvvm_core.cpp
    src/model/UserModel.cpp
    src/viewmodel/UserViewModel.cpp
    src/view/MainWindow.cpp
    include/mvvm_core.h
    include/model/UserModel.h
    include/viewmodel/UserViewModel.h
    include/view/MainWindow.h
    resources.qrc
)

# 链接 Qt 库 - 只链接需要的组件
target_link_libraries(demo_mvvm
    Qt5::Core
    Qt5::Widgets
)

# 设置包含目录
target_include_directories(demo_mvvm PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 使用父项目的输出目录设置函数
setup_project_output_dirs(demo_mvvm)

# 设置项目属性
set_target_properties(demo_mvvm PROPERTIES
    OUTPUT_NAME "demo_mvvm"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# 设置编译器选项以处理 UTF-8 编码
if(MSVC)
    target_compile_options(demo_mvvm PRIVATE /utf-8)
endif()
