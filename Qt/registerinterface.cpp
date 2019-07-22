#include "registerinterface.h"
#include "gui.h"

RegisterInterface::RegisterInterface(std::shared_ptr<Tools> tools, QWidget* parent):
	tools_(std::move(tools)), QWidget(parent) {}

RegisterInterface::~RegisterInterface() {

	submitRegistrationButton_->disconnect();
	cancelRegistrationButton_->disconnect();
}

void RegisterInterface::createInterface(const EventHandlers* eventHandlers) {

	createInterfaceElements();
	placeInterfaceElements();

	setAttributeToAllWidgets(Qt::WA_DeleteOnClose);
	tools_->setSizePolicyToQWidgets(QSizePolicy::Fixed, QSizePolicy::Fixed, {
		usernameEdit_.get(),
		passwordEdit_.get(),
		repeatPasswordEdit_.get(),
		emailEdit_.get(),
		submitRegistrationButton_.get(),
		cancelRegistrationButton_.get()
	});

	setUsernameRegex(tools_->getDefaultUsernameAndPassRegex());
	setPasswordRegex(tools_->getDefaultUsernameAndPassRegex());
	setEmailRegex(tools_->getDefaultEmailRegex());

	eventHandlers->bindDefaultRegisterInterface(this);
}

void RegisterInterface::createInterfaceElements() {

	registerInterfaceLayout_.reset(new QGridLayout(this));

	mainPartLayout_.reset(new QGridLayout());

	informationPartLayout_.reset(new QGridLayout());

	//Labels block

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

	repeatPasswordLabelEffect_.reset(new QGraphicsDropShadowEffect());
	repeatPasswordLabelEffect_->setBlurRadius(12);
	repeatPasswordLabelEffect_->setXOffset(4);
	repeatPasswordLabelEffect_->setYOffset(4);
	repeatPasswordLabelEffect_->setColor(Qt::black);

	emailLabelEffect_.reset(new QGraphicsDropShadowEffect());
	emailLabelEffect_->setBlurRadius(12);
	emailLabelEffect_->setXOffset(4);
	emailLabelEffect_->setYOffset(4);
	emailLabelEffect_->setColor(Qt::black);

	usernameLabel_.reset(new QLabel(QLabel::tr("Username")));
	usernameLabel_->setGraphicsEffect(usernameLabelEffect_.get());

	passwordLabel_.reset(new QLabel(QLabel::tr("Password")));
	passwordLabel_->setGraphicsEffect(passwordLabelEffect_.get());

	repeatPasswordLabel_.reset(new QLabel(QLabel::tr("Repeat password")));
	repeatPasswordLabel_->setGraphicsEffect(repeatPasswordLabelEffect_.get());

	emailLabel_.reset(new QLabel(QLabel::tr("E-mail")));
	emailLabel_->setGraphicsEffect(emailLabelEffect_.get());

	//
	//LineEdits block

	usernameEdit_.reset(new QLineEdit());

	passwordEdit_.reset(new QLineEdit());
	passwordEdit_->setEchoMode(QLineEdit::Password);

	repeatPasswordEdit_.reset(new QLineEdit());
	repeatPasswordEdit_->setEchoMode(QLineEdit::Password);

	emailEdit_.reset(new QLineEdit());

	//
	//Buttons block

	submitRegistrationButton_.reset(new QPushButton(QPushButton::tr("Submit")));
	submitRegistrationButton_->setObjectName("submitRegistrationButton");

	cancelRegistrationButton_.reset(new QPushButton());
	cancelRegistrationButton_->setToolTip("Close");
	cancelRegistrationButton_->setIcon(QIcon(":/images/images/close_interface.png"));
	cancelRegistrationButton_->setIconSize(QSize(40, 40));
	cancelRegistrationButton_->setObjectName("cancelRegistrationButton");
}

void RegisterInterface::placeInterfaceElements() const {

	informationPartLayout_->addWidget(cancelRegistrationButton_.get(), 0, 2);
	informationPartLayout_->addWidget(usernameLabel_.get(), 1, 0);
	informationPartLayout_->addWidget(usernameEdit_.get(), 1, 1);
	informationPartLayout_->addWidget(passwordLabel_.get(), 2, 0);
	informationPartLayout_->addWidget(passwordEdit_.get(), 2, 1);
	informationPartLayout_->addWidget(repeatPasswordLabel_.get(), 3, 0);
	informationPartLayout_->addWidget(repeatPasswordEdit_.get(), 3, 1);
	informationPartLayout_->addWidget(emailLabel_.get(), 4, 0);
	informationPartLayout_->addWidget(emailEdit_.get(), 4, 1);

	mainPartLayout_->addLayout(informationPartLayout_.get(), 0, 0);
	mainPartLayout_->addWidget(submitRegistrationButton_.get(), 1, 0, Qt::AlignCenter);

	registerInterfaceLayout_->addLayout(mainPartLayout_.get(), 1, 0, Qt::AlignCenter);
}

void RegisterInterface::setAttributeToAllWidgets(const Qt::WidgetAttribute&& attribute) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setAttribute(attribute);
	}
}

void RegisterInterface::setSizePolicyToAllWidgets(const QSizePolicy::Policy&& horizontal,
	const QSizePolicy::Policy&& vertical) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setSizePolicy(QSizePolicy(horizontal, vertical));
	}
}

void RegisterInterface::show() { if (this->isHidden()) QWidget::show(); }
void RegisterInterface::hide() { if (!this->isHidden()) QWidget::hide(); }
void RegisterInterface::resize(const int& width, const int& height) { QWidget::resize(width, height); }
void RegisterInterface::resize(const int&& width, const int&& height) { QWidget::resize(width, height); }

void RegisterInterface::paintEvent(QPaintEvent*) {

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void RegisterInterface::setUsernameRegex(const QString&& regex) { usernameRegex_.setPattern(regex); }
void RegisterInterface::setUsernameRegex(const QRegExp& regex) { usernameRegex_ = regex; }
void RegisterInterface::setPasswordRegex(const QString&& regex) { passwordRegex_.setPattern(regex); }
void RegisterInterface::setPasswordRegex(const QRegExp& regex) { passwordRegex_ = regex; }
void RegisterInterface::setEmailRegex(const QString&& regex) { emailRegex_.setPattern(regex); }
void RegisterInterface::setEmailRegex(const QRegExp& regex) { emailRegex_ = regex; }

QString RegisterInterface::getUsernameEditText() const { return usernameEdit_->text(); }
QString RegisterInterface::getPasswordEditText() const { return passwordEdit_->text(); }
QString RegisterInterface::getRepeatPasswordEditText() const { return repeatPasswordEdit_->text(); }
QString RegisterInterface::getEmailEditText() const { return emailEdit_->text(); }
const QPushButton* RegisterInterface::getSubmitRegistrationButton() const { return submitRegistrationButton_.get(); }
const QPushButton* RegisterInterface::getCancelButton() const { return cancelRegistrationButton_.get(); }
const QRegExp& RegisterInterface::getUsernameRegex() const { return usernameRegex_; }
const QRegExp& RegisterInterface::getPasswordRegex() const { return passwordRegex_; }
const QRegExp& RegisterInterface::getEmailRegex() const { return emailRegex_; }