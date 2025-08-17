#pragma once
#include <QObject>
#include <QVariant>
#include <QQmlEngine>
#include <functional>
#include <memory>

namespace mvvm {

/**
 * Qt MVVM 框架基础类
 * 提供属性绑定和通知机制
 */
class ViewModelBase : public QObject {
    Q_OBJECT

public:
    explicit ViewModelBase(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~ViewModelBase() = default;

protected:
    /**
     * 设置属性并发出通知信号
     */
    template<typename T>
    bool setProperty(T& field, const T& value, const char* propertyName) {
        if (field != value) {
            field = value;
            emit propertyChanged(propertyName);
            return true;
        }
        return false;
    }

signals:
    void propertyChanged(const QString& propertyName);
};

/**
 * 命令基类 - 使用 Qt 的 QObject 系统
 */
class Command : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool canExecute READ canExecute NOTIFY canExecuteChanged)

public:
    explicit Command(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Command() = default;

    Q_INVOKABLE virtual void execute() = 0;
    virtual bool canExecute() const { return true; }

public slots:
    void updateCanExecute() {
        emit canExecuteChanged();
    }

signals:
    void canExecuteChanged();
};

/**
 * 委托命令实现
 */
class DelegateCommand : public Command {
    Q_OBJECT

private:
    std::function<void()> executeFunc_;
    std::function<bool()> canExecuteFunc_;

public:
    explicit DelegateCommand(
        std::function<void()> executeFunc,
        std::function<bool()> canExecuteFunc = nullptr,
        QObject* parent = nullptr)
        : Command(parent), executeFunc_(executeFunc), canExecuteFunc_(canExecuteFunc) {}

    void execute() override {
        if (executeFunc_ && canExecute()) {
            executeFunc_();
        }
    }

    bool canExecute() const override {
        return canExecuteFunc_ ? canExecuteFunc_() : true;
    }
};

} // namespace mvvm
