#ifndef SMARTNOTES_H
#define SMARTNOTES_H

#include "gui.h"
#include <QApplication>

class SmartNotes
{
public:
    SmartNotes(QApplication* app);
    void startApplication();
private:
    std::unique_ptr<QApplication> application_;
    std::shared_ptr<Network> network_;
    std::shared_ptr<Gui> gui_;
};

#endif // SMARTNOTES_H
