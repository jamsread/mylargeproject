#include "viewmodel/UserViewModel.h"
#include <QDebug>

namespace mvvm {

UserViewModel::UserViewModel(std::shared_ptr<UserModel> model, QObject* parent)
    : ViewModelBase(parent), userModel_(model), canSave_(false) {
    
    if (userModel_) {
        // 连接模型信号
        connect(userModel_.get(), &UserModel::dataChanged, 
                this, &UserViewModel::onModelDataChanged);
        connect(userModel_.get(), &UserModel::validationChanged, 
                this, &UserViewModel::canSaveChanged);
        
        // 创建命令
        saveCommand_ = new DelegateCommand(
            [this]() { saveUser(); },
            [this]() { return canSave_; },
            this
        );
        
        resetCommand_ = new DelegateCommand(
            [this]() { resetUser(); },
            nullptr,
            this
        );
        
        // 初始化显示属性
        updateDisplayProperties();
    }
}

void UserViewModel::onModelDataChanged() {
    updateDisplayProperties();
}

void UserViewModel::updateName(const QString& name) {
    if (userModel_) {
        userModel_->setName(name);
    }
}

void UserViewModel::updateEmail(const QString& email) {
    if (userModel_) {
        userModel_->setEmail(email);
    }
}

void UserViewModel::updateAge(const QString& ageStr) {
    if (userModel_) {
        int age = parseAge(ageStr);
        userModel_->setAge(age);
    }
}

void UserViewModel::saveUser() {
    if (userModel_ && userModel_->isValid()) {
        qDebug() << "=== 保存用户信息 ===";
        qDebug() << userModel_->getUserInfo();
        qDebug() << "用户信息已成功保存!";
        emit userSaved();
    }
}

void UserViewModel::resetUser() {
    if (userModel_) {
        userModel_->setName("");
        userModel_->setEmail("");
        userModel_->setAge(0);
        qDebug() << "用户信息已重置!";
        emit userReset();
    }
}

QString UserViewModel::getUserDisplayInfo() const {
    if (userModel_) {
        return userModel_->getUserInfo();
    }
    return "无用户数据";
}

void UserViewModel::updateDisplayProperties() {
    if (userModel_) {
        setProperty(displayName_, userModel_->name(), "displayName");
        setProperty(displayEmail_, userModel_->email(), "displayEmail");
        setProperty(displayAge_, QString::number(userModel_->age()), "displayAge");
        setProperty(canSave_, userModel_->isValid(), "canSave");
        updateStatusMessage();
        
        // 通知命令状态可能已更改
        saveCommand_->updateCanExecute();
    }
}

void UserViewModel::updateStatusMessage() {
    if (!userModel_) {
        setProperty(statusMessage_, QString("错误: 无数据模型"), "statusMessage");
        return;
    }

    QString newStatusMessage;
    if (userModel_->isValid()) {
        newStatusMessage = "✅ 数据有效，可以保存";
    } else {
        QStringList errors;
        if (userModel_->name().isEmpty()) {
            errors << "姓名不能为空";
        }
        if (userModel_->email().isEmpty() || !userModel_->email().contains('@')) {
            errors << "邮箱格式无效";
        }
        if (userModel_->age() < 0 || userModel_->age() > 150) {
            errors << "年龄无效";
        }
        
        newStatusMessage = QString("❌ 数据无效: %1").arg(errors.join(", "));
    }
    
    setProperty(statusMessage_, newStatusMessage, "statusMessage");
}

int UserViewModel::parseAge(const QString& ageStr) const {
    bool ok;
    int age = ageStr.toInt(&ok);
    return ok ? age : 0;
}

} // namespace mvvm

#include "UserViewModel.moc"
