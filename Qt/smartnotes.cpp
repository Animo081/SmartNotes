#include "smartnotes.h"

SmartNotes::SmartNotes(QApplication* application): application_(application), 
	network_(std::make_shared<Network>()), gui_(std::make_shared<Gui>()) {}

void SmartNotes::startApplication(){

    network_->setGui(gui_);
    gui_->startInitialization(gui_,network_);

    application_->exec();

}
