#include "view/MainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSplitter>

namespace mvvm {

MainWindow::MainWindow(std::shared_ptr<UserViewModel> viewModel, QWidget* parent)
    : QMainWindow(parent), viewModel_(viewModel) {
    
    setWindowTitle("Qt MVVM 框架演示程序");
    setMinimumSize(600, 400);
    
    setupUI();
    connectSignals();
    updateUI();
}

void MainWindow::setupUI() {
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    auto mainLayout = new QVBoxLayout(centralWidget);
    
    // 创建分割器
    auto splitter = new QSplitter(Qt::Horizontal, this);
    mainLayout->addWidget(splitter);
    
    // 左侧：输入表单
    auto leftGroup = new QGroupBox("用户信息输入", this);
    auto leftLayout = new QVBoxLayout(leftGroup);
    
    auto formLayout = new QFormLayout();
    
    nameEdit_ = new QLineEdit(this);
    nameEdit_->setPlaceholderText("请输入姓名");
    formLayout->addRow("姓名:", nameEdit_);
    
    emailEdit_ = new QLineEdit(this);
    emailEdit_->setPlaceholderText("请输入邮箱地址");
    formLayout->addRow("邮箱:", emailEdit_);
    
    ageSpinBox_ = new QSpinBox(this);
    ageSpinBox_->setRange(0, 150);
    ageSpinBox_->setSuffix(" 岁");
    formLayout->addRow("年龄:", ageSpinBox_);
    
    leftLayout->addLayout(formLayout);
    
    // 状态标签
    statusLabel_ = new QLabel("准备就绪", this);
    statusLabel_->setWordWrap(true);
    statusLabel_->setStyleSheet("QLabel { color: blue; font-weight: bold; }");
    leftLayout->addWidget(statusLabel_);
    
    // 按钮布局
    auto buttonLayout = new QHBoxLayout();
    
    saveButton_ = new QPushButton("保存用户", this);
    saveButton_->setEnabled(false);
    buttonLayout->addWidget(saveButton_);
    
    resetButton_ = new QPushButton("重置", this);
    buttonLayout->addWidget(resetButton_);
    
    showInfoButton_ = new QPushButton("显示信息", this);
    buttonLayout->addWidget(showInfoButton_);
    
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();
    
    splitter->addWidget(leftGroup);
    
    // 右侧：信息显示
    auto rightGroup = new QGroupBox("用户信息显示", this);
    auto rightLayout = new QVBoxLayout(rightGroup);
    
    infoDisplay_ = new QTextEdit(this);
    infoDisplay_->setReadOnly(true);
    infoDisplay_->setFont(QFont("Consolas", 10));
    rightLayout->addWidget(infoDisplay_);
    
    splitter->addWidget(rightGroup);
    splitter->setSizes({300, 300});
    
    // 状态栏
    statusBar()->showMessage("Qt MVVM 框架演示程序已准备就绪");
}

void MainWindow::connectSignals() {
    if (!viewModel_) return;
    
    // 连接 UI 控件信号
    connect(nameEdit_, &QLineEdit::textChanged, this, &MainWindow::onNameChanged);
    connect(emailEdit_, &QLineEdit::textChanged, this, &MainWindow::onEmailChanged);
    connect(ageSpinBox_, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onAgeChanged);
    
    connect(saveButton_, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
    connect(resetButton_, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(showInfoButton_, &QPushButton::clicked, this, &MainWindow::onShowInfoClicked);
    
    // 连接 ViewModel 信号
    connect(viewModel_.get(), &ViewModelBase::propertyChanged, 
            this, &MainWindow::onViewModelPropertyChanged);
    connect(viewModel_.get(), &UserViewModel::userSaved, 
            this, &MainWindow::onUserSaved);
    connect(viewModel_.get(), &UserViewModel::userReset, 
            this, &MainWindow::onUserReset);
}

void MainWindow::onNameChanged() {
    if (viewModel_) {
        viewModel_->updateName(nameEdit_->text());
    }
}

void MainWindow::onEmailChanged() {
    if (viewModel_) {
        viewModel_->updateEmail(emailEdit_->text());
    }
}

void MainWindow::onAgeChanged() {
    if (viewModel_) {
        viewModel_->updateAge(QString::number(ageSpinBox_->value()));
    }
}

void MainWindow::onSaveClicked() {
    if (viewModel_ && viewModel_->saveCommand()) {
        viewModel_->saveCommand()->execute();
    }
}

void MainWindow::onResetClicked() {
    if (viewModel_ && viewModel_->resetCommand()) {
        viewModel_->resetCommand()->execute();
    }
}

void MainWindow::onShowInfoClicked() {
    if (viewModel_) {
        QString info = viewModel_->getUserDisplayInfo();
        infoDisplay_->setPlainText(info);
    }
}

void MainWindow::onViewModelPropertyChanged(const QString& propertyName) {
    if (propertyName == "displayName") {
        if (nameEdit_->text() != viewModel_->displayName()) {
            nameEdit_->setText(viewModel_->displayName());
        }
    } else if (propertyName == "displayEmail") {
        if (emailEdit_->text() != viewModel_->displayEmail()) {
            emailEdit_->setText(viewModel_->displayEmail());
        }
    } else if (propertyName == "displayAge") {
        int age = viewModel_->displayAge().toInt();
        if (ageSpinBox_->value() != age) {
            ageSpinBox_->setValue(age);
        }
    } else if (propertyName == "statusMessage") {
        statusLabel_->setText(viewModel_->statusMessage());
        
        // 根据状态设置颜色
        if (viewModel_->statusMessage().contains("✅")) {
            statusLabel_->setStyleSheet("QLabel { color: green; font-weight: bold; }");
        } else if (viewModel_->statusMessage().contains("❌")) {
            statusLabel_->setStyleSheet("QLabel { color: red; font-weight: bold; }");
        } else {
            statusLabel_->setStyleSheet("QLabel { color: blue; font-weight: bold; }");
        }
    } else if (propertyName == "canSave") {
        updateButtonStates();
    }
}

void MainWindow::onUserSaved() {
    QMessageBox::information(this, "成功", "用户信息已成功保存！");
    statusBar()->showMessage("用户信息已保存", 3000);
    onShowInfoClicked(); // 自动显示保存的信息
}

void MainWindow::onUserReset() {
    QMessageBox::information(this, "重置", "用户信息已重置！");
    statusBar()->showMessage("用户信息已重置", 3000);
    infoDisplay_->clear();
}

void MainWindow::updateUI() {
    if (!viewModel_) return;
    
    nameEdit_->setText(viewModel_->displayName());
    emailEdit_->setText(viewModel_->displayEmail());
    ageSpinBox_->setValue(viewModel_->displayAge().toInt());
    statusLabel_->setText(viewModel_->statusMessage());
    updateButtonStates();
}

void MainWindow::updateButtonStates() {
    if (!viewModel_) return;
    
    saveButton_->setEnabled(viewModel_->canSave());
}

} // namespace mvvm

#include "MainWindow.moc"
