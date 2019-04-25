#include "gui.h"

GUI::GUI(QApplication* app){ this->app = app; }

GUI::~GUI(){

    delete app;
    delete event_handlers;

}

QApplication* GUI::getQApplication(){
    return this->app;
}


void GUI::init(){


    this->event_handlers = new EventHandlers(this);
    this->createLogInInterface();

}

void GUI::createLogInInterface(){
    this->log_in_interface = new LogInInterface(new QWidget(),this->event_handlers);
}

void GUI::createRegisterInterface() {
    this->register_interface = new RegisterInterface(new QWidget(),this->event_handlers);
}

void GUI::start(){
    app->exec();
}
