#include "registerinterface.h"

RegisterInterface::RegisterInterface(QWidget* window, EventHandlers* event_handlers){

    this->window = window;

}

RegisterInterface::~RegisterInterface(){

    delete usernameLabel;
    delete passwordLabel;
    delete passwordRepeatLabel;
    delete emailLabel;
    delete usernameEdit;
    delete passwordEdit;
    delete passwordRepeatEdit;
    delete emailEdit;
    delete okButton;
    delete cancelButton;
    delete registerButtonBox;

    delete window;
}

void RegisterInterface::createInterface(EventHandlers* eventHandlers) {

}

void RegisterInterface::createInterfaceElements() {

	registerLayout = new QGridLayout(window);

	usernameLabel = new QLabel(QLabel::tr("Username"));
	passwordLabel = new QLabel(QLabel::tr("Password"));
	passwordRepeatLabel = new QLabel(QLabel::tr("Repeat password"));
	emailLabel = new QLabel(QLabel::tr("E-mail"));

	usernameEdit = new QLineEdit();
	passwordEdit = new QLineEdit();
	passwordRepeatEdit = new QLineEdit();
	emailEdit = new QLineEdit();

	registerButtonBox = new QDialogButtonBox();
	okButton = new QPushButton(QPushButton::tr("Ok"));
	cancelButton = new QPushButton(QPushButton::tr("Cancel"));
	registerButtonBox->addButton(okButton, QDialogButtonBox::AcceptRole);
	registerButtonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

	registerLayout->addWidget(usernameLabel, 0, 0);
	registerLayout->addWidget(passwordLabel, 1, 0);
	registerLayout->addWidget(passwordRepeatLabel, 2, 0);
	registerLayout->addWidget(emailLabel, 3, 0);
	registerLayout->addWidget(usernameEdit, 0, 1);
	registerLayout->addWidget(passwordEdit, 1, 1);
	registerLayout->addWidget(passwordRepeatEdit, 2, 1);
	registerLayout->addWidget(emailEdit, 3, 1);
	registerLayout->addWidget(registerButtonBox, 4, 1);

}

void RegisterInterface::placeInterfaceElements() {

}

void RegisterInterface::setAttributeToAllWidgets(const Qt::WidgetAttribute&&) {

}

void RegisterInterface::setSizePolicyToAllWidgets(const QSizePolicy::Policy&&,
	const QSizePolicy::Policy&&) {

}