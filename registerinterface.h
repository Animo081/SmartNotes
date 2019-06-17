#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include "interface.h"

class RegisterInterface: public Interface{
public:
    RegisterInterface(QWidget*,EventHandlers*);
    virtual ~RegisterInterface();
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

    QErrorMessage* warningMessage;
};

#endif // REGISTERINTERFACE_H
