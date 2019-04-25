#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include "eventhandlers.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>

class RegisterInterface
{
public:
    RegisterInterface(QWidget*,EventHandlers*);
    ~RegisterInterface();
    void setDefaultWindowSettings();
    void createDefaultRegisterInterface();
    void setAutoDeleteAttr();
    void showEveryhing();
    void bindDefaultRegisterInterface(EventHandlers*);
    QWidget* getWindow();
private:
    QWidget* window;

    QGridLayout* registerLayout;

    QLabel* usernameLabel;
    QLabel* passwordLabel;
    QLabel* passwordRepeatLabel;
    QLabel* emailLabel;

    QLineEdit* passwordEdit;
    QLineEdit* passwordRepeatEdit;
    QLineEdit* usernameEdit;
    QLineEdit* emailEdit;

    QDialogButtonBox* registerButtonBox;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // REGISTERINTERFACE_H
