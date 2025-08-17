#include "view/ConsoleView.h"
#include <iostream>
#include <limits>
#include <sstream>

#ifdef _WIN32
#include <cstdlib>
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

namespace mvvm {

ConsoleView::ConsoleView(std::shared_ptr<UserViewModel> viewModel)
    : viewModel_(viewModel) {
    
    if (viewModel_) {
        viewModel_->addObserver(std::shared_ptr<IObserver>(this, [](IObserver*){}));
        saveCommand_ = std::make_shared<SaveUserCommand>(viewModel_.get());
        resetCommand_ = std::make_shared<ResetUserCommand>(viewModel_.get());
    }
}

void ConsoleView::update() {
    // 在 ViewModel 数据变化时，可以在这里更新UI
    // 对于控制台应用，这里暂时不需要特殊处理
}

void ConsoleView::show() {
    clearScreen();
    std::cout << "===============================================\n";
    std::cout << "           MVVM 框架演示程序\n";
    std::cout << "===============================================\n\n";
}

void ConsoleView::run() {
    bool running = true;
    
    while (running) {
        show();
        displayUserInfo();
        displayMenu();
        
        std::cout << "请选择操作 (1-6): ";
        std::string choice;
        std::getline(std::cin, choice);
        
        if (choice == "1") {
            handleNameInput();
        } else if (choice == "2") {
            handleEmailInput();
        } else if (choice == "3") {
            handleAgeInput();
        } else if (choice == "4") {
            handleSaveCommand();
        } else if (choice == "5") {
            handleResetCommand();
        } else if (choice == "6") {
            handleDisplayInfo();
        } else if (choice == "0" || choice == "q" || choice == "Q") {
            running = false;
            std::cout << "\n感谢使用 MVVM 演示程序！再见！\n" << std::endl;
        } else {
            std::cout << "\n❌ 无效选择，请重新输入！" << std::endl;
            pauseForUser();
        }
    }
}

void ConsoleView::displayMenu() {
    std::cout << "操作菜单:\n";
    std::cout << "  1. 设置姓名\n";
    std::cout << "  2. 设置邮箱\n";
    std::cout << "  3. 设置年龄\n";
    std::cout << "  4. 保存用户信息\n";
    std::cout << "  5. 重置用户信息\n";
    std::cout << "  6. 显示完整信息\n";
    std::cout << "  0. 退出程序\n\n";
}

void ConsoleView::displayUserInfo() {
    if (!viewModel_) return;
    
    std::cout << "当前用户信息:\n";
    std::cout << "  姓名: " << (viewModel_->getDisplayName().empty() ? "[未设置]" : viewModel_->getDisplayName()) << "\n";
    std::cout << "  邮箱: " << (viewModel_->getDisplayEmail().empty() ? "[未设置]" : viewModel_->getDisplayEmail()) << "\n";
    std::cout << "  年龄: " << (viewModel_->getDisplayAge() == "0" ? "[未设置]" : viewModel_->getDisplayAge()) << "\n";
    std::cout << "  状态: " << viewModel_->getStatusMessage() << "\n\n";
}

void ConsoleView::handleUserInput() {
    // 在实际应用中，这里可以处理更复杂的用户交互
}

void ConsoleView::clearScreen() {
    std::system(CLEAR_COMMAND);
}

void ConsoleView::pauseForUser() {
    std::cout << "\n按 Enter 键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleView::handleNameInput() {
    std::string name = getInputLine("请输入姓名: ");
    if (viewModel_) {
        viewModel_->updateName(name);
    }
}

void ConsoleView::handleEmailInput() {
    std::string email = getInputLine("请输入邮箱: ");
    if (viewModel_) {
        viewModel_->updateEmail(email);
    }
}

void ConsoleView::handleAgeInput() {
    std::string age = getInputLine("请输入年龄: ");
    if (viewModel_) {
        viewModel_->updateAge(age);
    }
}

void ConsoleView::handleSaveCommand() {
    if (saveCommand_ && saveCommand_->canExecute()) {
        saveCommand_->execute();
    } else {
        std::cout << "\n❌ 无法保存：数据验证失败！" << std::endl;
    }
    pauseForUser();
}

void ConsoleView::handleResetCommand() {
    if (resetCommand_) {
        resetCommand_->execute();
    }
    pauseForUser();
}

void ConsoleView::handleDisplayInfo() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    if (viewModel_) {
        std::cout << viewModel_->getUserDisplayInfo() << std::endl;
    }
    std::cout << std::string(50, '=') << std::endl;
    pauseForUser();
}

std::string ConsoleView::getInputLine(const std::string& prompt) {
    std::cout << "\n" << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

} // namespace mvvm
