#include "logininterface.h"
#include "gui.h"

LogInInterface::LogInInterface(std::shared_ptr<Tools> tools, QWidget* parent):
	tools_(std::move(tools)), QWidget(parent) {}

LogInInterface::~LogInInterface() {

	signInButton_->disconnect();
	signUpButton_->disconnect();
}

void LogInInterface::createInterface(const EventHandlers* eventHandlers) {

	createInterfaceElements();
	placeInterfaceElements();

	setAttributeToAllWidgets(Qt::WA_DeleteOnClose);
	tools_->setSizePolicyToQWidgets(QSizePolicy::Fixed, QSizePolicy::Fixed, {
		buttonBox_.get(),
		usernameEdit_.get(),
		passwordEdit_.get()
	});

	eventHandlers->bindDefaultLogInInterface(this);
}

void LogInInterface::createInterfaceElements() {

    loginInterfaceLayout_.reset(new QGridLayout(this));

	mainPartLayout_.reset(new QGridLayout());

	usernameLabelEffect_.reset(new QGraphicsDropShadowEffect());
	usernameLabelEffect_->setBlurRadius(12);
	usernameLabelEffect_->setXOffset(4);
	usernameLabelEffect_->setYOffset(4);
	usernameLabelEffect_->setColor(Qt::black);

	passwordLabelEffect_.reset(new QGraphicsDropShadowEffect());
	passwordLabelEffect_->setBlurRadius(12);
	passwordLabelEffect_->setXOffset(4);
	passwordLabelEffect_->setYOffset(4);
	passwordLabelEffect_->setColor(Qt::black);

    usernameLabel_.reset(new QLabel (QLabel::tr("Username:")));
	usernameLabel_->setGraphicsEffect(usernameLabelEffect_.get());
	passwordLabel_.reset(new QLabel(QLabel::tr("Password:")));
	passwordLabel_->setGraphicsEffect(passwordLabelEffect_.get());

    usernameEdit_.reset(new QLineEdit());
    passwordEdit_.reset(new QLineEdit());
	passwordEdit_->setEchoMode(QLineEdit::Password);

    savePasswordCheckBox_.reset(new QCheckBox(QCheckBox::tr("Save pass?")));

    buttonBox_.reset(new QDialogButtonBox());

	signInButton_.reset(new QPushButton(QPushButton::tr("Sign in")));
	signUpButton_.reset(new QPushButton(QPushButton::tr("Sign up")));
}

void LogInInterface::placeInterfaceElements() const {

	buttonBox_->addButton(signInButton_.get(), QDialogButtonBox::ActionRole);
	buttonBox_->addButton(signUpButton_.get(), QDialogButtonBox::ActionRole);

	mainPartLayout_->addWidget(usernameLabel_.get(), 0, 0);
	mainPartLayout_->addWidget(passwordLabel_.get(), 1, 0);
	mainPartLayout_->addWidget(usernameEdit_.get(), 0, 1);
	mainPartLayout_->addWidget(passwordEdit_.get(), 1, 1);
	mainPartLayout_->addWidget(savePasswordCheckBox_.get(), 2, 0);
	mainPartLayout_->addWidget(buttonBox_.get(), 2, 1);

	loginInterfaceLayout_->addLayout(mainPartLayout_.get(), 0, 0, Qt::AlignCenter);
}

void LogInInterface::setAttributeToAllWidgets(const Qt::WidgetAttribute&& attribute) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setAttribute(attribute);
	}
}

void LogInInterface::setSizePolicyToAllWidgets(const QSizePolicy::Policy&& horizontal,
	const QSizePolicy::Policy&& vertical) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setSizePolicy(QSizePolicy(horizontal,vertical));
	}
}

void LogInInterface::show() { if (this->isHidden()) QWidget::show(); }
void LogInInterface::hide() { if (!this->isHidden()) QWidget::hide(); }
void LogInInterface::resize(const int& width, const int& height) { QWidget::resize(width, height); }
void LogInInterface::resize(const int&& width, const int&& height) { QWidget::resize(width, height); }

void LogInInterface::paintEvent(QPaintEvent*){

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString LogInInterface::getUsernameEditText() const { return usernameEdit_->text(); }
QString LogInInterface::getPasswordEditText() const { return passwordEdit_->text(); }
const QPushButton* LogInInterface::getSignInButton() const { return signInButton_.get(); }
const QPushButton* LogInInterface::getSignUpButton() const { return signUpButton_.get(); }