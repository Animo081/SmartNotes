#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QApplication>
#include "logininterface.h"
#include "registerinterface.h"
#include "eventhandlers.h"

class GUI
{
public:
    GUI(QApplication* app);
    ~GUI();
    QApplication* getQApplication();
    void init();
    void createLogInInterface();
    void createRegisterInterface();
    void start();
private:
    QApplication* app;
    LogInInterface* log_in_interface;
    RegisterInterface* register_interface;
    EventHandlers* event_handlers;
};

#endif // GUI_H
