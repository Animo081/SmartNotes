#include "eventhandlers.h"
#include "gui.h"
#include "registerinterface.h"

EventHandlers::EventHandlers(GUI* gui): QMainWindow(nullptr){

    this->sql = std::make_shared<SQL>();
    this->gui = gui;

}

EventHandlers::~EventHandlers(){}

void EventHandlers::bindDefaultRegisterInterface(QPushButton* okButton, QLineEdit* usernameEdit, QLineEdit* passwordEdit, QLineEdit* passwordRepeatEdit, QLineEdit* emailEdit, QPushButton* cancelButton, RegisterInterface* register_interface){

    connect(cancelButton, &QPushButton::clicked, [=] { cancelRegisterInterface(register_interface); });
    connect(okButton, &QPushButton::clicked, [=] { registrationProcessInit(usernameEdit,passwordEdit,passwordRepeatEdit,emailEdit); });

}

void EventHandlers::cancelRegisterInterface(RegisterInterface* register_interface){

    register_interface->getWindow()->close();
    delete register_interface;

}

void EventHandlers::registrationProcessInit(QLineEdit* usernameEdit, QLineEdit* passwordEdit, QLineEdit* passwordRepeatEdit, QLineEdit* emailEdit){
    if (passwordEdit->text() == passwordRepeatEdit->text())
        sql->registration(usernameEdit->text(),passwordEdit->text(),emailEdit->text());
}

void EventHandlers::bindDefaultLogInInterface(QPushButton* signUpButton, QLineEdit* usernameEdit,QLineEdit* passwordEdit,QPushButton* registerButton){

    connect(signUpButton, &QPushButton::clicked, [=] { signUpButtonBind(usernameEdit,passwordEdit); });
    connect(registerButton, &QPushButton::clicked, [=] { registerButtonBind(); });

}

void EventHandlers::signUpButtonBind(QLineEdit* usernameEdit,QLineEdit* passwordEdit){

    sql->signUp(usernameEdit->text(),passwordEdit->text());

}

void EventHandlers::registerButtonBind(){

    gui->createRegisterInterface();

}
