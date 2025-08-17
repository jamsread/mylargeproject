#pragma once
#include "../mvvm_core.h"
#include "model/UserModel.h"
#include <QObject>
#include <QString>
#include <memory>

namespace mvvm {

/**
 * 用户视图模型 - 使用 Qt 的属性系统和信号槽
 * 作为 Model 和 View 之间的桥梁
 */
class UserViewModel : public ViewModelBase {
    Q_OBJECT
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString displayEmail READ displayEmail NOTIFY displayEmailChanged)
    Q_PROPERTY(QString displayAge READ displayAge NOTIFY displayAgeChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged)
    Q_PROPERTY(bool canSave READ canSave NOTIFY canSaveChanged)
    Q_PROPERTY(Command* saveCommand READ saveCommand CONSTANT)
    Q_PROPERTY(Command* resetCommand READ resetCommand CONSTANT)

private:
    std::shared_ptr<UserModel> userModel_;
    
    // UI 绑定属性
    QString displayName_;
    QString displayEmail_;
    QString displayAge_;
    QString statusMessage_;
    bool canSave_;

    // 命令对象
    DelegateCommand* saveCommand_;
    DelegateCommand* resetCommand_;

public:
    explicit UserViewModel(std::shared_ptr<UserModel> model, QObject* parent = nullptr);
    ~UserViewModel() = default;

    // 属性访问器
    const QString& displayName() const { return displayName_; }
    const QString& displayEmail() const { return displayEmail_; }
    const QString& displayAge() const { return displayAge_; }
    const QString& statusMessage() const { return statusMessage_; }
    bool canSave() const { return canSave_; }

    // 命令访问器
    Command* saveCommand() const { return saveCommand_; }
    Command* resetCommand() const { return resetCommand_; }

    // 可从 QML 调用的方法
    Q_INVOKABLE void updateName(const QString& name);
    Q_INVOKABLE void updateEmail(const QString& email);
    Q_INVOKABLE void updateAge(const QString& ageStr);
    Q_INVOKABLE QString getUserDisplayInfo() const;

signals:
    void displayNameChanged();
    void displayEmailChanged();
    void displayAgeChanged();
    void statusMessageChanged();
    void canSaveChanged();
    void userSaved();
    void userReset();

private slots:
    void onModelDataChanged();

private:
    void updateDisplayProperties();
    void updateStatusMessage();
    void saveUser();
    void resetUser();
    int parseAge(const QString& ageStr) const;
};

} // namespace mvvm
