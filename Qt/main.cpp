#include "smartnotes.h"
#include "network.h"
#include "eventhandlers.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QApplication>

std::unique_ptr<SmartNotes> smartNotes;

int main(int argc, char **argv){

    smartNotes = std::make_unique<SmartNotes>(new QApplication(argc,argv));

    smartNotes->startProgramm();

    return 0;
}

