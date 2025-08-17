#pragma once
#include "../mvvm_core.h"
#include "viewmodel/UserViewModel.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QStatusBar>
#include <memory>

namespace mvvm {

/**
 * Qt Widgets 主窗口
 * 使用 MVVM 模式的 Qt GUI 界面
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    std::shared_ptr<UserViewModel> viewModel_;

    // UI 控件
    QLineEdit* nameEdit_;
    QLineEdit* emailEdit_;
    QSpinBox* ageSpinBox_;
    QLabel* statusLabel_;
    QPushButton* saveButton_;
    QPushButton* resetButton_;
    QPushButton* showInfoButton_;
    QTextEdit* infoDisplay_;

public:
    explicit MainWindow(std::shared_ptr<UserViewModel> viewModel, QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onNameChanged();
    void onEmailChanged();
    void onAgeChanged();
    void onSaveClicked();
    void onResetClicked();
    void onShowInfoClicked();
    void onViewModelPropertyChanged(const QString& propertyName);
    void onUserSaved();
    void onUserReset();

private:
    void setupUI();
    void connectSignals();
    void updateUI();
    void updateButtonStates();
};

} // namespace mvvm
