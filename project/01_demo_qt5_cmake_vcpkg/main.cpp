#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QProgressBar>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <cxxopts.hpp>
#include <vector>
#include <string>
#include <random>

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUI();
        connectSignals();
    }

private slots:
    void calculateSum()
    {
        try {
            auto text = m_numberInput->text();
            auto numbers = parseNumbers(text.toStdString());
            
            // 使用 range-v3 计算统计信息
            if (!numbers.empty()) {
                int sum = ranges::accumulate(numbers, 0);
                int product = ranges::accumulate(numbers, 1, std::multiplies<int>());
                double average = static_cast<double>(sum) / numbers.size();
                auto [min_it, max_it] = ranges::minmax_element(numbers);
                
                QString result = QString(
                    "Numbers: %1\n"
                    "Count: %2\n"
                    "Sum: %3\n"
                    "Product: %4\n"
                    "Average: %5\n"
                    "Min: %6\n"
                    "Max: %7"
                ).arg(text)
                 .arg(numbers.size())
                 .arg(sum)
                 .arg(product)
                 .arg(average, 0, 'f', 2)
                 .arg(*min_it)
                 .arg(*max_it);
                
                m_resultText->setText(result);
                
                // 使用 fmt 在控制台输出
                fmt::print("Calculated: sum={}, count={}, avg={:.2f}\n", 
                          sum, numbers.size(), average);
            }
        } catch (const std::exception& e) {
            m_resultText->setText(QString("Error: %1").arg(e.what()));
        }
    }
    
    void addRandomNumbers()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        
        QStringList numbers;
        for (int i = 0; i < 5; ++i) {
            numbers << QString::number(dis(gen));
        }
        
        m_numberInput->setText(numbers.join(", "));
        calculateSum();
    }
    
    void clearResults()
    {
        m_numberInput->clear();
        m_resultText->clear();
        m_historyList->clear();
    }

private:
    void setupUI()
    {
        auto *layout = new QVBoxLayout(this);
        
        // 输入区域
        auto *inputGroup = new QGroupBox("Number Input", this);
        auto *inputLayout = new QHBoxLayout(inputGroup);
        
        m_numberInput = new QLineEdit(this);
        m_numberInput->setPlaceholderText("Enter numbers separated by commas (e.g., 1,2,3,4,5)");
        
        m_calculateBtn = new QPushButton("Calculate", this);
        m_randomBtn = new QPushButton("Random Numbers", this);
        
        inputLayout->addWidget(m_numberInput);
        inputLayout->addWidget(m_calculateBtn);
        inputLayout->addWidget(m_randomBtn);
        
        // 结果区域
        auto *resultGroup = new QGroupBox("Results", this);
        auto *resultLayout = new QVBoxLayout(resultGroup);
        
        m_resultText = new QTextEdit(this);
        m_resultText->setMaximumHeight(150);
        m_resultText->setReadOnly(true);
        
        resultLayout->addWidget(m_resultText);
        
        // 历史记录
        auto *historyGroup = new QGroupBox("History", this);
        auto *historyLayout = new QVBoxLayout(historyGroup);
        
        m_historyList = new QListWidget(this);
        m_historyList->setMaximumHeight(100);
        
        auto *clearBtn = new QPushButton("Clear History", this);
        
        historyLayout->addWidget(m_historyList);
        historyLayout->addWidget(clearBtn);
        
        layout->addWidget(inputGroup);
        layout->addWidget(resultGroup);
        layout->addWidget(historyGroup);
        
        connect(clearBtn, &QPushButton::clicked, this, &CalculatorWidget::clearResults);
    }
    
    void connectSignals()
    {
        connect(m_calculateBtn, &QPushButton::clicked, this, &CalculatorWidget::calculateSum);
        connect(m_randomBtn, &QPushButton::clicked, this, &CalculatorWidget::addRandomNumbers);
        connect(m_numberInput, &QLineEdit::returnPressed, this, &CalculatorWidget::calculateSum);
    }
    
    std::vector<int> parseNumbers(const std::string& input)
    {
        std::vector<int> numbers;
        std::string current;
        
        for (char c : input) {
            if (c == ',' || c == ' ') {
                if (!current.empty()) {
                    numbers.push_back(std::stoi(current));
                    current.clear();
                }
            } else if (std::isdigit(c) || c == '-') {
                current += c;
            }
        }
        
        if (!current.empty()) {
            numbers.push_back(std::stoi(current));
        }
        
        return numbers;
    }
    
    QLineEdit *m_numberInput;
    QPushButton *m_calculateBtn;
    QPushButton *m_randomBtn;
    QTextEdit *m_resultText;
    QListWidget *m_historyList;
};

class ProgressWidget : public QWidget
{
    Q_OBJECT

public:
    ProgressWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUI();
        connectSignals();
        
        // 定时器用于模拟进度
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &ProgressWidget::updateProgress);
    }

private slots:
    void startProgress()
    {
        m_progress = 0;
        m_progressBar->setValue(0);
        m_startBtn->setEnabled(false);
        m_stopBtn->setEnabled(true);
        m_timer->start(100); // 每100ms更新一次
    }
    
    void stopProgress()
    {
        m_timer->stop();
        m_startBtn->setEnabled(true);
        m_stopBtn->setEnabled(false);
    }
    
    void updateProgress()
    {
        m_progress += m_speedSlider->value();
        m_progressBar->setValue(m_progress);
        
        if (m_progress >= 100) {
            stopProgress();
            QMessageBox::information(this, "Complete", "Progress completed!");
        }
    }
    
    void onSpeedChanged(int value)
    {
        m_speedLabel->setText(QString("Speed: %1").arg(value));
    }

private:
    void setupUI()
    {
        auto *layout = new QVBoxLayout(this);
        
        auto *group = new QGroupBox("Progress Simulation", this);
        auto *groupLayout = new QVBoxLayout(group);
        
        // 进度条
        m_progressBar = new QProgressBar(this);
        m_progressBar->setRange(0, 100);
        
        // 速度控制
        auto *speedLayout = new QHBoxLayout;
        m_speedLabel = new QLabel("Speed: 1", this);
        m_speedSlider = new QSlider(Qt::Horizontal, this);
        m_speedSlider->setRange(1, 10);
        m_speedSlider->setValue(1);
        
        speedLayout->addWidget(m_speedLabel);
        speedLayout->addWidget(m_speedSlider);
        
        // 控制按钮
        auto *buttonLayout = new QHBoxLayout;
        m_startBtn = new QPushButton("Start", this);
        m_stopBtn = new QPushButton("Stop", this);
        m_stopBtn->setEnabled(false);
        
        buttonLayout->addWidget(m_startBtn);
        buttonLayout->addWidget(m_stopBtn);
        
        groupLayout->addWidget(m_progressBar);
        groupLayout->addLayout(speedLayout);
        groupLayout->addLayout(buttonLayout);
        
        layout->addWidget(group);
        layout->addStretch();
    }
    
    void connectSignals()
    {
        connect(m_startBtn, &QPushButton::clicked, this, &ProgressWidget::startProgress);
        connect(m_stopBtn, &QPushButton::clicked, this, &ProgressWidget::stopProgress);
        connect(m_speedSlider, &QSlider::valueChanged, this, &ProgressWidget::onSpeedChanged);
    }
    
    QProgressBar *m_progressBar;
    QSlider *m_speedSlider;
    QLabel *m_speedLabel;
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QTimer *m_timer;
    int m_progress = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        setupUI();
        setupMenus();
        setupStatusBar();
    }

private slots:
    void showAbout()
    {
        QMessageBox::about(this, "About", 
            "Complex Qt Demo\n\n"
            "Features:\n"
            "• Number calculator with statistics\n"
            "• Progress simulation\n"
            "• Uses fmt, range-v3, and cxxopts libraries\n\n"
            "Built with Qt5 and modern C++");
    }

private:
    void setupUI()
    {
        auto *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        auto *layout = new QHBoxLayout(centralWidget);
        
        // 左侧：计算器
        m_calculator = new CalculatorWidget(this);
        
        // 右侧：进度控制
        m_progress = new ProgressWidget(this);
        
        layout->addWidget(m_calculator, 2);
        layout->addWidget(m_progress, 1);
        
        setWindowTitle("Complex Qt Demo with fmt, range-v3, cxxopts");
        resize(800, 600);
    }
    
    void setupMenus()
    {
        auto *fileMenu = menuBar()->addMenu("&File");
        auto *exitAction = fileMenu->addAction("&Exit");
        connect(exitAction, &QAction::triggered, this, &QWidget::close);
        
        auto *helpMenu = menuBar()->addMenu("&Help");
        auto *aboutAction = helpMenu->addAction("&About");
        connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    }
    
    void setupStatusBar()
    {
        statusBar()->showMessage("Ready");
    }
    
    CalculatorWidget *m_calculator;
    ProgressWidget *m_progress;
};

int main(int argc, char *argv[])
{
    // 使用 cxxopts 解析命令行参数
    cxxopts::Options options("QtComplexDemo", "Complex Qt Demo with multiple libraries");
    options.add_options()
        ("fullscreen", "Start in fullscreen mode")
        ("h,help", "Print usage");
    
    auto result = options.parse(argc, argv);
    
    if (result.count("help")) {
        fmt::print("{}\n", options.help());
        return 0;
    }
    
    QApplication app(argc, argv);
    
    MainWindow window;
    
    if (result.count("fullscreen")) {
        window.showFullScreen();
        fmt::print("Starting in fullscreen mode\n");
    } else {
        window.show();
    }
    
    fmt::print("Qt Complex Demo started successfully!\n");
    
    return app.exec();
}

#include "main.moc"
