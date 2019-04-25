#include "logininterface.h"

LogInInterface::LogInInterface(QWidget* window, EventHandlers* event_handlers){

    this->window = window;
    setDefaultWindowSettings();
    createDefaultLogInInterface();
    bindDefaultLogInInterface(event_handlers);
}

LogInInterface::~LogInInterface(){

    delete loginLayout;
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

}

void LogInInterface::createDefaultLogInInterface(){

    loginLayout = new QGridLayout(window);

    usernameLabel = new QLabel (QLabel::tr("Username:"),window);
    passwordLabel = new QLabel (QLabel::tr("Password:"),window);
    usernameEdit = new QLineEdit(window);
    passwordEdit = new QLineEdit(window);
    savePass = new QCheckBox(QCheckBox::tr("Save password"),window);

    loginButtonBox = new QDialogButtonBox(window);
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

    window->show();

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

void LogInInterface::bindDefaultLogInInterface(EventHandlers* event_handlers){
    event_handlers->bindDefaultLogInInterface(signInButton,usernameEdit,passwordEdit,registerButton);
}

QWidget* LogInInterface::getWindow(){
    return this->window;
}
