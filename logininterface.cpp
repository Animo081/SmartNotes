#include "logininterface.h"

LogInInterface::LogInInterface(QWidget* window, EventHandlers* event_handlers){

    this->window = window;
    setDefaultWindowSettings();
    createDefaultInterface();
    bindDefaultInterface(event_handlers);
    showWindow();
}

LogInInterface::~LogInInterface(){

    delete usernameLabel;
    delete passwordLabel;
    delete usernameEdit;
    delete passwordEdit;
    delete savePass;
    delete signInButton;
    delete registerButton;
    delete loginButtonBox;

    delete window;

}

void LogInInterface::setDefaultWindowSettings(){

    //window->resize(840,620);
    window->setWindowTitle("Welcome");

}

void LogInInterface::createDefaultInterface(){

    loginLayout = new QGridLayout(window);

    usernameLabel = new QLabel (QLabel::tr("Username:"));
    passwordLabel = new QLabel (QLabel::tr("Password:"));
    usernameEdit = new QLineEdit();
    passwordEdit = new QLineEdit();
    savePass = new QCheckBox(QCheckBox::tr("Save password"));

    loginButtonBox = new QDialogButtonBox();
    signInButton = new QPushButton(QPushButton::tr("Sign in"));
    registerButton = new QPushButton(QPushButton::tr("Have no account?"));
    loginButtonBox->addButton(signInButton,QDialogButtonBox::ActionRole);
    loginButtonBox->addButton(registerButton,QDialogButtonBox::ActionRole);

    loginLayout->addWidget(usernameLabel,0,0);
    loginLayout->addWidget(passwordLabel,1,0);
    loginLayout->addWidget(usernameEdit,0,1);
    loginLayout->addWidget(passwordEdit,1,1);
    loginLayout->addWidget(savePass,2,0);
    loginLayout->addWidget(loginButtonBox,2,1);

    setAutoDeleteAttr();

}

void LogInInterface::setAutoDeleteAttr(){

    usernameLabel->setAttribute(Qt::WA_DeleteOnClose);
    passwordLabel->setAttribute(Qt::WA_DeleteOnClose);
    usernameEdit->setAttribute(Qt::WA_DeleteOnClose);
    passwordEdit->setAttribute(Qt::WA_DeleteOnClose);
    savePass->setAttribute(Qt::WA_DeleteOnClose);
    loginButtonBox->setAttribute(Qt::WA_DeleteOnClose);
    signInButton->setAttribute(Qt::WA_DeleteOnClose);
    registerButton->setAttribute(Qt::WA_DeleteOnClose);

    window->setAttribute(Qt::WA_DeleteOnClose);

}

void LogInInterface::showEveryhing(){

    usernameLabel->show();
    passwordLabel->show();
    usernameEdit->show();
    passwordEdit->show();
    savePass->show();
    loginButtonBox->show();

}

void LogInInterface::showWindow(){
    window->show();
}

void LogInInterface::bindDefaultInterface(EventHandlers* event_handlers){
    warningMessage = new QErrorMessage();
    event_handlers->bindDefaultLogInInterface(signInButton,usernameEdit,passwordEdit,registerButton,this);
}

void LogInInterface::showMessage(QString message){
    warningMessage->showMessage(message);
}

QWidget* LogInInterface::getWindow(){
    return this->window;
}

QWidget* LogInInterface::getWidget(QString widget){
    return new QWidget();
}

QListWidget* LogInInterface::getNotesList(){
    return nullptr;
}
