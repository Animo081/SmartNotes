#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "interface.h"

class LogInInterface: public Interface {
public:
    LogInInterface(QWidget*,EventHandlers*);
    virtual ~LogInInterface();
    void setDefaultWindowSettings() override;
    void createDefaultInterface() override;
    void setAutoDeleteAttr() override;
    void showEveryhing() override;
    void showWindow() override;
    void bindDefaultInterface(EventHandlers*) override;
    void showMessage(QString) override;
    QWidget* getWindow() override;
    QWidget* getWidget(QString) override;
    QListWidget * getNotesList() override;
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

    QErrorMessage* warningMessage;
};

#endif // LOGININTERFACE_H
