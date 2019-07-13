#include "gui.h"
#include "network.h"

Gui::Gui(): QMainWindow(), tools_(std::make_shared<Tools>()) {}

void Gui::startInitialization(std::shared_ptr<Gui>& gui,
	std::shared_ptr<Network>& network) {

    eventHandlers_.reset(new EventHandlers(gui,network));
	createLogInInterface();
    //startMainProgram();
}

void Gui::createLogInInterface(){
	destroyCurrentInterface();
    logInInterface_.reset(new LogInInterface(tools_));
	logInInterface_->createInterface(eventHandlers_.get());
	eventHandlers_->bindDefaultLogInInterface(logInInterface_.get());
}

void Gui::createRegisterInterface() {
	destroyCurrentInterface();
	registerInterface_.reset(new LogInInterface(tools_));
	registerInterface_->createInterface(eventHandlers_.get());
	eventHandlers_->bindDefaultLogInInterface(registerInterface_.get());
}

void Gui::createMainInterface(){
	destroyCurrentInterface();
	mainInterface_.reset(new LogInInterface(tools_));
	mainInterface_->createInterface(eventHandlers_.get());
	eventHandlers_->bindDefaultLogInInterface(mainInterface_.get());
}

void Gui::destroyInterface(Interface* destroyedInterface) {

	if (typeid(LogInInterface) == typeid(*destroyedInterface))
		if (logInInterface_.get() != nullptr)
			logInInterface_.reset();
		else tools_->showMessage("There is nothing to delete");
	else if (typeid(RegisterInterface) == typeid(*destroyedInterface))
			if (registerInterface_.get() != nullptr)
				registerInterface_.reset();
	else if (typeid(MainInterface) == typeid(*destroyedInterface))
			if (mainInterface_.get() != nullptr)
				mainInterface_.reset();
	else tools_->showMessage("Can`t destroy interface");
}

void Gui::destroyCurrentInterface(){

	if (logInInterface_.get() != nullptr)
		logInInterface_.reset();
	else if (registerInterface_.get() != nullptr)
		registerInterface_.reset();
	else if (mainInterface_.get() != nullptr)
		mainInterface_.reset();
	else tools_->showMessage("No interface in use");
}

void Gui::startMainProgram(){

    createMainInterface();
}

void Gui::finishMainProgram(){

}


//Tools 

Tools::Tools(): message_(new QErrorMessage) {}

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

void Tools::showMessage(const QString&& message) {

	message_->showMessage(message);
}