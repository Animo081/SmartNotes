#include "gui.h"
#include "network.h"
#include "logininterface.h"
#include "registerinterface.h"
#include "maininterface.h"

Gui::Gui(QWidget* parent): QWidget(parent), tools_(std::make_shared<Tools>()),
	backgoundImagesDefaultDir_("images/Background Images") {}

Gui::~Gui() {}

void Gui::startInitialization(std::shared_ptr<Gui>& gui,
	std::shared_ptr<Network>& network) {

    eventHandlers_.reset(new EventHandlers(gui,network));
	setWindowSettings();	
	createLogInInterface();	
//	createMainInterface();
	
	this->show();
    //startMainProgram();
}

void Gui::setWindowSettings() {

	this->setUpdatesEnabled(true);
	this->setWindowIcon(QIcon(":/images/images/icon.png"));
	this->setWindowTitle("Smart Notes");
	this->setMinimumSize(this->width(), this->height());

	this->setBackgroundImage(backgoundImagesDefaultDir_, 
		tools_->getRandomImage(tools_->getImagesFromDir(backgoundImagesDefaultDir_)));
}

void Gui::setBackgroundImage(const QString& imageDir, const QString& imageName) {

	backgroundImagePixmap_.load(imageDir + "/" + imageName);
	QPalette palette;
	palette.setBrush(this->backgroundRole(),
		QBrush(backgroundImagePixmap_.scaled(this->width(), this->height())));
	this->setAutoFillBackground(true);
	this->setPalette(palette);
}

void Gui::createLogInInterface(){
	//destroyCurrentInterface();
    logInInterface_.reset(new LogInInterface(tools_, this));
	currentInterface_ = logInInterface_;

	logInInterface_->createInterface(eventHandlers_.get());
	logInInterface_->resize(this->width(), this->height());
	logInInterface_->show();
}

void Gui::createRegisterInterface() {
	//destroyCurrentInterface();
	registerInterface_.reset(new RegisterInterface(tools_,this));
	currentInterface_ = registerInterface_;

	registerInterface_->createInterface(eventHandlers_.get());
	registerInterface_->resize(this->width(), this->height());
	registerInterface_->show();
}

void Gui::createMainInterface(){
	//destroyCurrentInterface();
	mainInterface_.reset(new MainInterface(tools_,this));
	currentInterface_ = mainInterface_;

	mainInterface_->createInterface(eventHandlers_.get());
	mainInterface_->resize(this->width(), this->height());
	mainInterface_->show();
}

void Gui::destroyInterface(Interface* destroyedInterface) {

	if (typeid(LogInInterface) == typeid(*destroyedInterface))
		if (logInInterface_.get() != nullptr)
			logInInterface_.reset();
			else tools_->showMessage("Invalid Interface");
	else if (typeid(RegisterInterface) == typeid(*destroyedInterface))
			if (registerInterface_.get() != nullptr)
				registerInterface_.reset();
			else tools_->showMessage("Invalid Interface");
	else if (typeid(MainInterface) == typeid(*destroyedInterface))
			if (mainInterface_.get() != nullptr)
				mainInterface_.reset();
			else tools_->showMessage("Invalid Interface");
	else tools_->showMessage("Can`t destroy interface");
}

void Gui::destroyCurrentInterface(){

	if (currentInterface_.get() != nullptr) {
		if (currentInterface_.get() == logInInterface_.get()) {
			logInInterface_.reset();
			currentInterface_.reset();
		}
		else if (currentInterface_.get() == registerInterface_.get()) {
			registerInterface_.reset();
			currentInterface_.reset();
		}
		else if (currentInterface_.get() == mainInterface_.get()) {
			mainInterface_.reset();
			currentInterface_.reset();
		}
		else tools_->showMessage("No interface in use");
	} 
	else tools_->showMessage("No interface in use");
}

void Gui::startMainProgram(){

    createMainInterface();
}

void Gui::finishMainProgram(){

}


void Gui::resizeEvent(QResizeEvent* event) {

	QPalette palette;
	palette.setBrush(this->backgroundRole(),
		QBrush(backgroundImagePixmap_.scaled(this->width(), this->height())));
	this->setPalette(palette);
	if (currentInterface_.get() != nullptr)
		currentInterface_->resize(this->width(), this->height());

	QWidget::resizeEvent(event);
}

Tools* Gui::getTools() { return tools_.get(); }

//Tools 

Tools::Tools(): message_(new QErrorMessage), 
	defaultUsernameAndPassRegex_("(?!^[0-9]*$)(?!^[a-zA-Z]*$)^([a-zA-Z0-9]{6,15})$"),
	defaultEmailRegex_("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$")
{}

void Tools::setAttributeToQWidgets(const Qt::WidgetAttribute&& attribute,
	std::initializer_list<QWidget*> list) {

	for (auto&& widget : list) 
		widget->setAttribute(attribute);
}

void Tools::setSizePolicyToQWidgets(const QSizePolicy::Policy&& horizontal, 
	const QSizePolicy::Policy&& vertical, std::initializer_list<QWidget*> list) {

	for (auto&& widget : list)
		widget->setSizePolicy(QSizePolicy(horizontal,vertical));
}

void Tools::showMessage(const QString& message) {

	message_->showMessage(message);
}

void Tools::showMessage(const QString&& message) {

	message_->showMessage(message);
}

QStringList Tools::getImagesFromDir(const QString& path) {

	QDir directory(path);
	if (!directory.isEmpty())
		return directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.png" << "*.PNG", QDir::Files);
	else return QStringList();
}

QString Tools::getRandomImage(const QStringList& images) {

	QRandomGenerator generator;
	return images[generator.bounded(images.size())];
}

QString Tools::getDefaultUsernameAndPassRegex() { return defaultUsernameAndPassRegex_; }
QString Tools::getDefaultEmailRegex() { return defaultEmailRegex_; }