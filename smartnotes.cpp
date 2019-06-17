#include "smartnotes.h"

SmartNotes::SmartNotes(QApplication* app){

    this->app = app;
    this->gui = new GUI();
    this->network = new Network();

}

SmartNotes::~SmartNotes(){
    delete gui;
}

void SmartNotes::startProgramm(){

    network->setGui(this->gui);
    gui->initInitialization(this->network);

    app->exec();

}
