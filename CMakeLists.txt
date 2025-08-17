cmake_minimum_required(VERSION 3.18)

# 设置 vcpkg 工具链（必须在 project() 之前）
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

set(VCPKG_MANIFEST_MODE ON)
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")

# 设置主项目
project(MyLargeProject LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录为各自的子目录
function(setup_project_output_dirs project_name)
    # 设置运行时输出目录（可执行文件）
    set_target_properties(${project_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${project_name}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${project_name}/bin/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${project_name}/bin/Release"
    )
    
    # 设置库输出目录
    set_target_properties(${project_name} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${project_name}/lib"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${project_name}/lib/Debug"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${project_name}/lib/Release"
    )
    
    # 设置归档文件输出目录
    set_target_properties(${project_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${project_name}/lib"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/${project_name}/lib/Debug"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/${project_name}/lib/Release"
    )
endfunction()

# 添加子项目
add_subdirectory(project/01_demo_qt5_cmake_vcpkg)
add_subdirectory(project/02_demo_my_large_project)
