#ifndef SMARTNOTES_H
#define SMARTNOTES_H

#include "gui.h"
#include <QApplication>

class SmartNotes
{
public:
    SmartNotes(QApplication* app);
    ~SmartNotes();
    void startProgramm();
private:
    QApplication* app;
    Network* network;
    GUI* gui;
};

#endif // SMARTNOTES_H
