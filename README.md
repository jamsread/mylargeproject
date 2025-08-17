# MyLargeProject

一个使用现代 C++ 和 vcpkg 包管理的大型项目演示。

## 环境要求

- CMake 3.18+
- C++17 兼容的编译器
- Visual Studio 2019(Windows)
- Git

## 快速开始

1. 克隆项目并初始化子模块

```bash
git clone https://github.com/jamsread/mylargeproject.git
python tools\setup.py
```

2. 手动安装 vcpkg 依赖

```cmd
.\vcpkg\vcpkg.exe install
```

## 构建项目

### Windows

```cmd
cmake --preset windows
cmake --build build --config Debug
```

### Linux

```bash
cmake --preset linux
cmake --build build --config Debug
```

### macOS

```bash
cmake --preset macos
cmake --build build --config Debug
```

## 运行测试

运行测试程序：

```cmd
.\build\project\02_demo_my_large_project\Debug\02_demo_my_large_project.exe
```

运行简单测试：

```cmd
.\build\project\02_demo_my_large_project\Debug\simple_test.exe
```

## 项目结构

```
mylargeproject/
├── CMakeLists.txt              # 主 CMake 配置文件
├── CMakePresets.json           # CMake 预设配置
├── vcpkg.json                  # vcpkg 清单文件
├── README.md                   # 项目说明文档
├── project/                    # 项目源代码
│   ├── 01_demo_qt5_cmake_vcpkg/    # Qt5 演示项目
│   └── 02_demo_my_large_project/   # 主项目
│       ├── main.cpp            # 主程序文件
│       └── simple_test.cpp     # 简单测试程序
├── tools/                      # 工具脚本目录
├── vcpkg/                      # vcpkg 包管理器 (子模块)
└── build/                      # 构建输出目录
```
