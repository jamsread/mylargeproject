#include <iostream>
#include <Qt5/QtWidgets/QApplication>
#include <Qt5/QtWidgets/QWidget>
#include <Qt5/QtWidgets/QVBoxLayout>
#include <Qt5/QtWidgets/QLabel>
#include <Qt5/QtWidgets/QPushButton>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <eigen3/Eigen/Dense>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#ifdef ENABLE_TESTS
#include <gtest/gtest.h>
#endif

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void onButtonClicked() {
        // 演示各种库的使用
        
        // Boost filesystem
        boost::filesystem::path currentPath = boost::filesystem::current_path();
        spdlog::info("当前路径: {}", currentPath.string());
        
        // Eigen 矩阵运算
        Eigen::Matrix3d matrix;
        matrix << 1, 2, 3,
                  4, 5, 6,
                  7, 8, 9;
        
        // fmt 格式化
        std::string message = fmt::format("矩阵行列式: {:.2f}", matrix.determinant());
        spdlog::info(message);
        
        // OpenCV 创建一个简单图像
        cv::Mat image = cv::Mat::zeros(300, 300, CV_8UC3);
        cv::circle(image, cv::Point(150, 150), 50, cv::Scalar(0, 255, 0), -1);
        cv::imshow("OpenCV Demo", image);
        
        // JSON 处理
        nlohmann::json config;
        config["name"] = "MyLargeProject";
        config["version"] = "1.0.0";
        config["libraries"] = {"Qt", "OpenCV", "Boost", "Eigen", "fmt", "spdlog"};
        
        std::cout << "项目配置: " << config.dump(2) << std::endl;
        
        label->setText(QString::fromStdString(message));
    }

private:
    void setupUI() {
        setWindowTitle("My Large Project Demo");
        setFixedSize(400, 300);
        
        auto *layout = new QVBoxLayout(this);
        
        label = new QLabel("点击按钮运行演示", this);
        label->setAlignment(Qt::AlignCenter);
        
        auto *button = new QPushButton("运行演示", this);
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        
        layout->addWidget(label);
        layout->addWidget(button);
    }
    
    QLabel *label;
};

#ifdef ENABLE_TESTS
TEST(BasicTest, SampleTest) {
    EXPECT_EQ(2 + 2, 4);
}
#endif

int main(int argc, char *argv[]) {
#ifdef ENABLE_TESTS
    if (argc > 1 && std::string(argv[1]) == "--tests") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#endif
    
    QApplication app(argc, argv);
    
    // 设置日志
    spdlog::set_level(spdlog::level::info);
    spdlog::info("应用程序启动");
    
    MainWindow window;
    window.show();
    
    spdlog::info("主窗口已显示");
    
    return app.exec();
}

#include "main.moc"
