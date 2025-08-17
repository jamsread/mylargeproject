#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QDebug>
#include <memory>

#include "mvvm_core.h"
#include "model/UserModel.h"
#include "viewmodel/UserViewModel.h"
#include "view/MainWindow.h"

/**
 * Qt MVVM 框架演示程序
 * 
 * 此程序演示了一个完整的 Qt MVVM (Model-View-ViewModel) 架构实现：
 * 
 * 1. Model (UserModel): 负责数据管理和业务逻辑
 *    - 存储用户数据（姓名、邮箱、年龄）
 *    - 实现数据验证逻辑
 *    - 使用 Qt 的信号槽机制进行数据变化通知
 *    - 支持 Qt 属性系统，可直接绑定到 QML
 * 
 * 2. ViewModel (UserViewModel): 作为 Model 和 View 的桥梁
 *    - 将 Model 数据转换为 View 可用的格式
 *    - 处理用户操作命令（使用 Qt 的 Command 模式）
 *    - 实现双向数据绑定
 *    - 支持 Qt 属性系统和信号槽
 * 
 * 3. View (MainWindow): 负责用户界面和交互
 *    - 使用 Qt Widgets 显示用户界面
 *    - 处理用户输入
 *    - 通过信号槽观察 ViewModel 变化并更新界面
 *    - 也可以轻松替换为 QML 界面
 * 
 * 4. 核心组件 (mvvm_core.h):
 *    - 基于 Qt 的 QObject 系统
 *    - ViewModelBase 提供属性通知机制
 *    - Command 系统支持可执行状态管理
 *    - 完全集成 Qt 的信号槽系统
 * 
 * Qt MVVM 的优势：
 * - 原生支持属性绑定和通知
 * - 强大的信号槽机制
 * - 可以与 QML 无缝集成
 * - 支持国际化和主题
 * - 跨平台 GUI 支持
 */

using namespace mvvm;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("Qt MVVM Demo");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("MyLargeProject");
    
    // 设置应用程序样式
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // 设置应用程序图标和样式表
    app.setStyleSheet(
        "QMainWindow {"
        "    background-color: #f0f0f0;"
        "}"
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"
        "QPushButton {"
        "    background-color: #0078d4;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #106ebe;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #005a9e;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #cccccc;"
        "    color: #666666;"
        "}"
        "QLineEdit, QSpinBox {"
        "    padding: 5px;"
        "    border: 1px solid #cccccc;"
        "    border-radius: 3px;"
        "}"
        "QLineEdit:focus, QSpinBox:focus {"
        "    border: 2px solid #0078d4;"
        "}"
    );
    
    try {
        qDebug() << "正在初始化 Qt MVVM 演示程序...";
        
        // 1. 创建 Model - 数据层
        auto userModel = std::make_shared<UserModel>();
        qDebug() << "✅ UserModel 已创建";
        
        // 2. 创建 ViewModel - 业务逻辑层
        auto userViewModel = std::make_shared<UserViewModel>(userModel);
        qDebug() << "✅ UserViewModel 已创建";
        
        // 3. 创建 View - 用户界面层
        auto mainWindow = std::make_shared<MainWindow>(userViewModel);
        qDebug() << "✅ MainWindow 已创建";
        
        qDebug() << "🚀 Qt MVVM 架构初始化完成！";
        qDebug() << "正在显示主窗口...";
        
        // 显示主窗口
        mainWindow->show();
        
        // 启动应用程序事件循环
        return app.exec();
        
    } catch (const std::exception& e) {
        qCritical() << "❌ 程序运行出错:" << e.what();
        return 1;
    } catch (...) {
        qCritical() << "❌ 程序运行出现未知错误!";
        return 1;
    }
}
