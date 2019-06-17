#include "registerinterface.h"

RegisterInterface::RegisterInterface(QWidget* window, EventHandlers* event_handlers){

    this->window = window;
    setDefaultWindowSettings();
    createDefaultInterface();
    bindDefaultInterface(event_handlers);
    showWindow();

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

void RegisterInterface::setDefaultWindowSettings(){
    window->setWindowTitle("Registration");
}

void RegisterInterface::createDefaultInterface(){

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
    registerButtonBox->addButton(okButton,QDialogButtonBox::AcceptRole);
    registerButtonBox->addButton(cancelButton,QDialogButtonBox::RejectRole);

    registerLayout->addWidget(usernameLabel,0,0);
    registerLayout->addWidget(passwordLabel,1,0);
    registerLayout->addWidget(passwordRepeatLabel,2,0);
    registerLayout->addWidget(emailLabel,3,0);
    registerLayout->addWidget(usernameEdit,0,1);
    registerLayout->addWidget(passwordEdit,1,1);
    registerLayout->addWidget(passwordRepeatEdit,2,1);
    registerLayout->addWidget(emailEdit,3,1);
    registerLayout->addWidget(registerButtonBox,4,1);

    setAutoDeleteAttr();

}

void RegisterInterface::setAutoDeleteAttr(){

    usernameLabel->setAttribute(Qt::WA_DeleteOnClose);
    passwordLabel->setAttribute(Qt::WA_DeleteOnClose);
    passwordRepeatLabel->setAttribute(Qt::WA_DeleteOnClose);
    emailLabel->setAttribute(Qt::WA_DeleteOnClose);
    usernameEdit->setAttribute(Qt::WA_DeleteOnClose);
    passwordEdit->setAttribute(Qt::WA_DeleteOnClose);
    passwordRepeatEdit->setAttribute(Qt::WA_DeleteOnClose); 
    emailEdit->setAttribute(Qt::WA_DeleteOnClose);
    okButton->setAttribute(Qt::WA_DeleteOnClose);
    cancelButton->setAttribute(Qt::WA_DeleteOnClose);
    registerButtonBox->setAttribute(Qt::WA_DeleteOnClose);

    window->setAttribute(Qt::WA_DeleteOnClose);

}

void RegisterInterface::showEveryhing(){

    usernameLabel->show();
    passwordLabel->show();
    passwordRepeatLabel->show();
    emailLabel->show();
    usernameEdit->show();
    passwordEdit->show();
    passwordRepeatEdit->show();
    emailEdit->show();
    registerButtonBox->show();

}

void RegisterInterface::showWindow(){
    window->show();
}

void RegisterInterface::bindDefaultInterface(EventHandlers* event_handlers){
    warningMessage = new QErrorMessage();
    event_handlers->bindDefaultRegisterInterface(okButton, usernameEdit, passwordEdit, passwordRepeatEdit, emailEdit, cancelButton, this);
}

void RegisterInterface::showMessage(QString message){
    warningMessage->showMessage(message);
}

QWidget* RegisterInterface::getWindow(){
    return this->window;
}

QWidget* RegisterInterface::getWidget(QString widget){
    return new QWidget();
}

QListWidget* RegisterInterface::getNotesList(){
    return nullptr;
}
