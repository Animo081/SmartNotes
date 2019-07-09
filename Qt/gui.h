#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include "logininterface.h"
#include "registerinterface.h"
#include "maininterface.h"
#include "eventhandlers.h"

class Network;

class GUI
{
public:
    GUI();
    ~GUI();
    void initInitialization(Network*);
    void createLogInInterface();
    void finishLoginIn();
    void createRegisterInterface();
    void finishRegistration();
    void createMainInterface();
    void finishMainInterface();
    void startMainProgram();
    void finishMainProgram();
private:
    Interface* log_in_interface;
    Interface* register_interface;
    Interface* main_interface;
    EventHandlers* event_handlers;
};

#endif // GUI_H
