#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include "interface.h"

class RegisterInterface: public Interface{
public:
    RegisterInterface(QWidget*,EventHandlers*);
    virtual ~RegisterInterface();
	virtual void createInterface(EventHandlers* eventHandlers) override;
	virtual void createInterfaceElements() override;
	virtual void placeInterfaceElements() override;
	virtual void setAttributeToAllWidgets(const Qt::WidgetAttribute&&) override;
	virtual void setSizePolicyToAllWidgets(const QSizePolicy::Policy&&,
		const QSizePolicy::Policy&&) override;
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
