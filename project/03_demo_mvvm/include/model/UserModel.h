#pragma once
#include <QObject>
#include <QString>
#include <QRegularExpression>

namespace mvvm {

/**
 * 用户数据模型 - 使用 Qt 的信号槽机制
 * 负责管理用户数据和业务逻辑
 */
class UserModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(bool isValid READ isValid NOTIFY validationChanged)

private:
    QString name_;
    QString email_;
    int age_;
    bool isValid_;

public:
    explicit UserModel(QObject* parent = nullptr);
    ~UserModel() = default;

    // Getter 方法
    const QString& name() const { return name_; }
    const QString& email() const { return email_; }
    int age() const { return age_; }
    bool isValid() const { return isValid_; }

    // Setter 方法
    void setName(const QString& name);
    void setEmail(const QString& email);
    void setAge(int age);

    // 业务逻辑
    Q_INVOKABLE void validateData();
    Q_INVOKABLE QString getUserInfo() const;

signals:
    void nameChanged();
    void emailChanged();
    void ageChanged();
    void validationChanged();
    void dataChanged();

private:
    bool isValidEmail(const QString& email) const;
};

} // namespace mvvm
