#include "gui.h"
#include "sql.h"
#include "eventhandlers.h"
#include <iostream>
#include <QtGui>
#include <QWidget>
#include <QApplication>



int main(int argc, char **argv){

    std::unique_ptr<GUI> gui(new GUI(new QApplication(argc,argv)));

    gui->init();
    gui->start();

    return 0;
}

