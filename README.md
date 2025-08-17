# MyLargeProject

一个使用现代 C++ 和多个流行库的大型项目演示。

## 项目状态

✅ **项目已完成基础设置**

- [x] vcpkg 包管理器已配置
- [x] 基础 C++ 代码结构已创建
- [x] 跨平台构建脚本已完成
- [x] 简单测试程序可正常运行
- [x] 项目状态检查工具已就绪

### 立即可用的功能

**基础测试程序:**
```bash
python tools/simple_build.py  # 构建并运行简单测试
```

**项目状态检查:**
```bash
python tools/status.py        # 检查项目组件状态
```

### 计划中的高级功能

完整依赖库集成（需要运行完整构建）:

- **Qt5**: GUI 框架
- **OpenCV**: 计算机视觉库
- **Boost**: C++ 实用库集合
- **Eigen3**: 线性代数库
- **fmt**: 现代 C++ 格式化库
- **spdlog**: 快速 C++ 日志库
- **nlohmann-json**: JSON 处理库
- **GoogleTest**: C++ 测试框架

## 环境要求

- CMake 3.18+
- C++17 兼容的编译器
- Python 3.6+ (用于设置脚本)
- Git (用于子模块管理)

### Windows
- Visual Studio 2022 (推荐)
- 或者 MinGW-w64

### Linux
- GCC 9+ 或 Clang 10+
- 构建工具 (make, ninja)

## 快速开始

### 1. 克隆项目

```bash
git clone <repository-url>
cd mylargeproject
```

### 2. 项目设置

#### 使用 Python 脚本 (推荐，跨平台)

**Windows:**
```cmd
python tools\setup.py
# 或者双击运行
tools\setup.bat
```

**Linux/macOS:**
```bash
python3 tools/setup.py
# 或者
chmod +x tools/setup.sh && ./tools/setup.sh
```

#### 使用传统脚本

**Windows PowerShell:**
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
.\tools\setup.ps1
```

### 3. 构建项目

#### Windows (Visual Studio)
```cmd
# 配置
cmake --preset windows

# 构建 Debug 版本
cmake --build build --config Debug

# 构建 Release 版本
cmake --build build --config Release
```

#### Linux
```bash
# 配置
cmake --preset linux

# 构建
cmake --build build
```

### 4. 运行应用程序

#### Windows
```cmd
# Debug 版本
.\build\Debug\my_app.exe

# Release 版本
.\build\Release\my_app.exe
```

#### Linux
```bash
./build/my_app
```

### 5. 运行测试

#### Windows
```cmd
.\build\Debug\my_app.exe --tests
```

#### Linux
```bash
./build/my_app --tests
```

## 项目结构

```
mylargeproject/
├── CMakeLists.txt          # 主 CMake 配置文件
├── CMakePresets.json       # CMake 预设配置
├── vcpkg.json             # vcpkg 清单文件
├── .gitignore             # Git 忽略文件
├── .gitmodules            # Git 子模块配置
├── README.md              # 项目说明文档
├── src/                   # 源代码目录
│   └── main.cpp          # 主程序文件
├── tools/                 # 工具脚本目录
│   ├── setup.py          # Python 设置脚本 (推荐)
│   ├── setup.bat         # Windows 批处理脚本
│   ├── setup.sh          # Linux/macOS shell 脚本
│   └── setup.ps1         # PowerShell 脚本 (备份)
├── vcpkg/                 # vcpkg 包管理器 (子模块)
└── build/                 # 构建输出目录 (自动创建)
```

## 开发说明

### 添加新的依赖

1. 在 `vcpkg.json` 中添加新的依赖包
2. 在 `CMakeLists.txt` 中添加 `find_package()` 和 `target_link_libraries()`
3. 重新运行 CMake 配置

### 调试

- 使用 Visual Studio Code 配合 C++ 扩展
- 使用 Visual Studio 2022
- 使用 GDB (Linux) 或 LLDB (macOS)

## 故障排除

### vcpkg 相关问题

1. **子模块未初始化**: 运行 `git submodule update --init --recursive`
2. **vcpkg 引导失败**: 检查网络连接和权限
3. **包安装失败**: 清理 vcpkg 缓存 `vcpkg\vcpkg remove --outdated`

### 构建问题

1. **CMake 配置失败**: 检查 CMake 版本和编译器
2. **链接错误**: 确保所有依赖都正确安装
3. **权限问题**: 以管理员身份运行 (Windows)

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！
