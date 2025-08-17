# Qt MVVM Framework Demo (C++)

这是一个完整的基于 Qt 的 C++ MVVM (Model-View-ViewModel) 框架演示项目。

## 项目结构

```
03_demo_mvvm/
├── CMakeLists.txt                 # CMake 构建文件
├── main.cpp                       # 主程序入口
├── README.md                      # 项目说明文档
├── resources.qrc                  # Qt 资源文件
├── include/                       # 头文件目录
│   ├── mvvm_core.h               # Qt MVVM 框架核心组件
│   ├── model/
│   │   └── UserModel.h           # 用户数据模型
│   ├── viewmodel/
│   │   └── UserViewModel.h       # 用户视图模型
│   └── view/
│       └── MainWindow.h          # Qt Widgets 主窗口
└── src/                          # 源文件目录
    ├── model/
    │   └── UserModel.cpp
    ├── viewmodel/
    │   └── UserViewModel.cpp
    └── view/
        └── MainWindow.cpp
```

## 架构组件

### 1. Model (数据模型)
- **UserModel**: 负责用户数据管理和业务逻辑
  - 存储用户信息（姓名、邮箱、年龄）
  - 实现数据验证（邮箱格式、年龄范围等）
  - 继承 QObject，使用 Qt 属性系统和信号槽
  - 支持 QML 绑定

### 2. ViewModel (视图模型)
- **UserViewModel**: Model 和 View 之间的桥梁
  - 将 Model 数据转换为 View 友好的格式
  - 处理用户操作命令（保存、重置等）
  - 实现数据绑定和状态管理
  - 使用 Qt 的信号槽进行响应式更新
  - 提供 Qt Command 对象

### 3. View (视图)
- **MainWindow**: Qt Widgets 用户界面
  - 现代化的 GUI 界面设计
  - 响应式布局和用户交互
  - 实时数据验证和状态显示
  - 通过信号槽与 ViewModel 通信

### 4. Core (核心框架)
- **mvvm_core.h**: 提供 Qt MVVM 框架基础设施
  - ViewModelBase: 基于 QObject 的 ViewModel 基类
  - Command 系统: 支持可执行状态的命令模式
  - DelegateCommand: 委托命令实现
  - 完全集成 Qt 的信号槽系统

## Qt MVVM 特性

- ✅ **原生 Qt 集成**: 使用 Qt 的信号槽和属性系统
- ✅ **QML 兼容**: 可以轻松替换为 QML 界面
- ✅ **响应式 UI**: 实时数据绑定和状态更新
- ✅ **命令模式**: 支持可执行状态的用户操作
- ✅ **数据验证**: 实时输入验证和错误提示
- ✅ **现代 GUI**: 使用 Qt Widgets 和自定义样式
- ✅ **跨平台**: 支持 Windows、Linux、macOS
- ✅ **可扩展**: 易于添加新功能和界面

## 技术栈

- **C++17**: 现代 C++ 语法和特性
- **Qt5**: 图形界面框架（Core, Widgets, Qml, Quick）
- **CMake**: 跨平台构建系统
- **vcpkg**: 包管理器
- **智能指针**: 现代内存管理

## 编译依赖

项目依赖以下 Qt 组件（已在 vcpkg.json 中配置）：
- qt5-base
- qt5-declarative
- qt5-quickcontrols2

## 编译和运行

### 前置条件
- CMake 3.18+
- C++17 兼容编译器
- Qt5 开发库（通过 vcpkg 自动安装）
- Git（用于 vcpkg 子模块）

### 构建步骤

1. **初始化项目**（如果还未执行）：
   ```bash
   # Windows
   python tools/setup.py
   
   # Linux/macOS
   python3 tools/setup.py
   ```

2. **配置项目**：
   ```bash
   # Windows
   cmake --preset windows
   
   # Linux/macOS
   cmake --preset linux
   ```

3. **编译项目**：
   ```bash
   cmake --build build --target demo_mvvm
   ```

4. **运行程序**：
   ```bash
   # Windows
   ./build/demo_mvvm/bin/Debug/demo_mvvm.exe
   # 或者
   ./build/demo_mvvm/bin/Release/demo_mvvm.exe
   
   # Linux/macOS
   ./build/demo_mvvm/bin/demo_mvvm
   ```

## 功能特性

### 主界面功能
- **左侧输入面板**:
  - 姓名输入框
  - 邮箱输入框（带格式验证）
  - 年龄选择器（0-150岁）
  - 实时状态显示
  - 操作按钮（保存、重置、显示信息）

- **右侧显示面板**:
  - 用户信息详细显示
  - 格式化的文本输出

### 数据验证
- 姓名：不能为空
- 邮箱：必须包含有效的邮箱格式
- 年龄：必须在 0-150 之间
- 实时验证反馈和状态显示

### 用户交互
- 实时输入验证
- 按钮状态管理（保存按钮仅在数据有效时启用）
- 操作成功/失败的消息提示
- 状态栏信息显示

## Qt MVVM 设计模式

### 数据绑定流程
1. **User Input** → **View** (MainWindow)
2. **View** → **ViewModel** (UserViewModel) 通过槽函数
3. **ViewModel** → **Model** (UserModel) 更新数据
4. **Model** → **ViewModel** 通过信号通知数据变化
5. **ViewModel** → **View** 通过属性变化信号更新UI

### 命令模式
- **SaveCommand**: 保存用户数据，支持可执行状态检查
- **ResetCommand**: 重置用户数据
- 命令与按钮状态自动同步

### 信号槽架构
- Model 层：数据变化信号
- ViewModel 层：属性变化和命令执行
- View 层：用户交互和界面更新

## 扩展指南

### 添加新的数据字段
1. 在 `UserModel` 中添加新的 Q_PROPERTY 和对应的 getter/setter
2. 在 `UserViewModel` 中添加显示属性和更新逻辑
3. 在 `MainWindow` 中添加相应的 UI 控件和信号连接

### 添加新的命令
1. 在 `UserViewModel` 中创建新的 DelegateCommand
2. 实现命令逻辑和可执行状态检查
3. 在 `MainWindow` 中添加按钮和信号连接

### 替换为 QML 界面
1. 创建 QML 文件定义界面
2. 在 main.cpp 中使用 QQmlApplicationEngine
3. 通过 qmlRegisterType 注册 C++ 类型
4. Model 和 ViewModel 层无需修改

### 国际化支持
1. 使用 Qt 的 tr() 函数包装所有显示文本
2. 创建翻译文件 (.ts)
3. 在 CMake 中添加翻译支持

## 许可证

此项目仅供学习和演示用途。
