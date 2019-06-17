#ifndef INTEFRACE_H
#define INTEFRACE_H

#include "eventhandlers.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QErrorMessage>


class Interface{
public:
    virtual void setDefaultWindowSettings() = 0;
    virtual void createDefaultInterface() = 0;
    virtual void setAutoDeleteAttr() = 0;
    virtual void showEveryhing() = 0;
    virtual void showWindow() = 0;
    virtual void bindDefaultInterface(EventHandlers*) = 0;
    virtual void showMessage(QString) = 0;
    virtual QWidget* getWindow() = 0;
    virtual QWidget* getWidget(QString) = 0;
    virtual QListWidget* getNotesList() = 0;
};

#endif // INTEFRACE_H
