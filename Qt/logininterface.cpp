#include "logininterface.h"
#include "Gui.h"

LogInInterface::LogInInterface(std::shared_ptr<Tools> tools, QWidget* parent):
	backgroundImagePixmap_(""), tools_(std::move(tools)), QWidget(parent) {}

LogInInterface::~LogInInterface() {}

void LogInInterface::createInterface(EventHandlers* eventHandlers) {

	createInterfaceElements();
	placeInterfaceElements();

	setAttributeToAllWidgets(Qt::WA_DeleteOnClose);
	tools_->setSizePolicyToQWidgets(QSizePolicy::Fixed, QSizePolicy::Fixed, {
		buttonBox_.get(),
		usernameEdit_.get(),
		passwordEdit_.get()
	});

	//eventHandlers->bindDefaultLogInInterface();
	this->show();
}

void LogInInterface::createInterfaceElements(){

    loginInterfaceLayout_.reset(new QGridLayout(this));

	mainPartLayout_.reset(new QGridLayout());

    usernameLabel_.reset(new QLabel (QLabel::tr("Username:")));
    passwordLabel_.reset(new QLabel (QLabel::tr("Password:")));

    usernameEdit_.reset(new QLineEdit());
    passwordEdit_.reset(new QLineEdit());

    savePasswordCheckBox_.reset(new QCheckBox(QCheckBox::tr("Save password")));

    buttonBox_.reset(new QDialogButtonBox());

	signInButton_.reset(new QPushButton(QPushButton::tr("Sign in")));
	signUpButton_.reset(new QPushButton(QPushButton::tr("Have no account?")));
}

void LogInInterface::placeInterfaceElements() {

	buttonBox_->addButton(signInButton_.get(), QDialogButtonBox::ActionRole);
	buttonBox_->addButton(signUpButton_.get(), QDialogButtonBox::ActionRole);

	mainPartLayout_->addWidget(usernameLabel_.get(), 0, 0);
	mainPartLayout_->addWidget(passwordLabel_.get(), 1, 0);
	mainPartLayout_->addWidget(usernameEdit_.get(), 0, 1);
	mainPartLayout_->addWidget(passwordEdit_.get(), 1, 1);
	mainPartLayout_->addWidget(savePasswordCheckBox_.get(), 2, 0);
	mainPartLayout_->addWidget(buttonBox_.get(), 2, 1);

	loginInterfaceLayout_->addLayout(mainPartLayout_.get(),0,0,Qt::AlignCenter);
}

void LogInInterface::setAttributeToAllWidgets(const Qt::WidgetAttribute&& attribute) {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setAttribute(attribute);
	}
}

void LogInInterface::setSizePolicyToAllWidgets(const QSizePolicy::Policy&& horizontal,
	const QSizePolicy::Policy&& vertical) {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setSizePolicy(QSizePolicy(horizontal,vertical));
	}
}

QString LogInInterface::getUsernameEditText() { return usernameEdit_->text(); }
QString LogInInterface::getPasswordEditText() { return passwordEdit_->text(); }
QPushButton* LogInInterface::getSignInButton() { return signInButton_.get(); }
QPushButton* LogInInterface::getSignUpButton() { return signUpButton_.get(); }