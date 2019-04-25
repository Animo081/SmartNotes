#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "eventhandlers.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>


class LogInInterface{
public:
    LogInInterface(QWidget*,EventHandlers*);
    ~LogInInterface();
    void setDefaultWindowSettings();
    void createDefaultLogInInterface();
    void setAutoDeleteAttr();
    void showEveryhing();
    void bindDefaultLogInInterface(EventHandlers*);
    QWidget* getWindow();
private:
    QWidget* window;

    QGridLayout* loginLayout;

    QLabel* usernameLabel;
    QLabel* passwordLabel;

    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;

    QCheckBox* savePass;

    QDialogButtonBox* loginButtonBox;
    QPushButton* signInButton;
    QPushButton* registerButton;
};

#endif // LOGININTERFACE_H
