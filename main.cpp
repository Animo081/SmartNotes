#include "smartnotes.h"
#include "network.h"
#include "eventhandlers.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QApplication>



int main(int argc, char **argv){

    std::unique_ptr<SmartNotes> smart_notes(new SmartNotes(new QApplication(argc,argv)));

    smart_notes->startProgramm();

    return 0;
}

