#include "model/UserModel.h"
#include <QRegularExpression>

namespace mvvm {

UserModel::UserModel(QObject* parent) 
    : QObject(parent), name_(""), email_(""), age_(0), isValid_(false) {
}

void UserModel::setName(const QString& name) {
    if (name_ != name) {
        name_ = name;
        emit nameChanged();
        validateData();
        emit dataChanged();
    }
}

void UserModel::setEmail(const QString& email) {
    if (email_ != email) {
        email_ = email;
        emit emailChanged();
        validateData();
        emit dataChanged();
    }
}

void UserModel::setAge(int age) {
    if (age_ != age) {
        age_ = age;
        emit ageChanged();
        validateData();
        emit dataChanged();
    }
}

void UserModel::validateData() {
    bool oldValid = isValid_;
    isValid_ = !name_.isEmpty() && 
               isValidEmail(email_) && 
               age_ >= 0 && age_ <= 150;
    
    if (oldValid != isValid_) {
        emit validationChanged();
    }
}

QString UserModel::getUserInfo() const {
    return QString("用户信息:\n"
                  "  姓名: %1\n"
                  "  邮箱: %2\n"
                  "  年龄: %3\n"
                  "  状态: %4")
           .arg(name_)
           .arg(email_)
           .arg(age_)
           .arg(isValid_ ? "有效" : "无效");
}

bool UserModel::isValidEmail(const QString& email) const {
    QRegularExpression regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex.match(email).hasMatch();
}

} // namespace mvvm

#include "UserModel.moc"
