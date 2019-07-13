#ifndef GUI_H
#define GUI_H

#include <variant>
#include <QWidget>
#include <QMainWindow>
#include "logininterface.h"
#include "registerinterface.h"
#include "maininterface.h"
#include "eventhandlers.h"

class Network;

class Tools {
public:
	Tools();
	void setAttributeToQWidgets(const Qt::WidgetAttribute&& attribute,
		std::initializer_list<QWidget*> list);
	void setSizePolicyToQWidgets(const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical, 
		std::initializer_list<QWidget*> list);
	void showMessage(const QString&& message);
private:
	QScopedPointer<QErrorMessage> message_;
};

class Gui: public QMainWindow{
public:
    Gui();
    void startInitialization(std::shared_ptr<Gui>& gui, 
		std::shared_ptr<Network>& network);
    void createLogInInterface();
	void createRegisterInterface();
    void createMainInterface();
	virtual void destroyInterface(Interface*);
	virtual void destroyCurrentInterface();
    void startMainProgram();
    void finishMainProgram();
private:
	std::unique_ptr<EventHandlers> eventHandlers_;

	std::shared_ptr<Tools> tools_;

    std::unique_ptr<Interface> logInInterface_;
    std::unique_ptr<Interface> registerInterface_;
    std::unique_ptr<Interface> mainInterface_;
};

#endif // GUI_H
