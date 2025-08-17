#pragma once
#include "../mvvm_core.h"
#include "viewmodel/UserViewModel.h"
#include <memory>
#include <string>

namespace mvvm {

/**
 * 控制台视图
 * 负责用户界面显示和用户交互
 */
class ConsoleView : public IObserver {
private:
    std::shared_ptr<UserViewModel> viewModel_;
    std::shared_ptr<SaveUserCommand> saveCommand_;
    std::shared_ptr<ResetUserCommand> resetCommand_;

public:
    explicit ConsoleView(std::shared_ptr<UserViewModel> viewModel);
    ~ConsoleView() = default;

    // IObserver 接口实现
    void update() override;

    // 视图方法
    void show();
    void run();

private:
    void displayMenu();
    void displayUserInfo();
    void handleUserInput();
    void clearScreen();
    void pauseForUser();
    
    // 输入处理方法
    void handleNameInput();
    void handleEmailInput();
    void handleAgeInput();
    void handleSaveCommand();
    void handleResetCommand();
    void handleDisplayInfo();
    
    std::string getInputLine(const std::string& prompt);
};

} // namespace mvvm
