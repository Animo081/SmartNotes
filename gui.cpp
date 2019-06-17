#include "gui.h"
#include "network.h"

GUI::GUI(){

    this->log_in_interface = nullptr;
    this->register_interface = nullptr;

}

GUI::~GUI(){
    delete event_handlers;
}

void GUI::initInitialization(Network* network){

    this->event_handlers = new EventHandlers(this,network);
    this->createLogInInterface();

    //startMainProgram();

}

void GUI::createLogInInterface(){
    this->log_in_interface = new LogInInterface(new QWidget(),this->event_handlers);
}

void GUI::finishLoginIn(){

    if (log_in_interface != nullptr){
        log_in_interface->getWindow()->close();
        delete log_in_interface;
        log_in_interface = nullptr;
    }

}

void GUI::createRegisterInterface() {
    this->register_interface = new RegisterInterface(new QWidget(),this->event_handlers);
}

void GUI::finishRegistration(){

    if (register_interface != nullptr){
        register_interface->getWindow()->close();
        delete register_interface;
        register_interface = nullptr;
    }

}

void GUI::createMainInterface(){
    main_interface = new MainInterface(new QWidget(),this->event_handlers);
}

void GUI::finishMainInterface(){
    if (main_interface != nullptr){
        main_interface->getWindow()->close();
        delete main_interface;
        main_interface = nullptr;
    }
}

void GUI::startMainProgram(){

    finishRegistration();
    finishLoginIn();
    createMainInterface();

}

void GUI::finishMainProgram(){
    finishRegistration();
    finishLoginIn();
    finishMainInterface();
}
