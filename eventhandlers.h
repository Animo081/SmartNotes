#ifndef EVENTHANDLERS_H
#define EVENTHANDLERS_H

#include <iostream>
#include <QtGui>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "sql.h"

class GUI;

class RegisterInterface;

class EventHandlers: public QMainWindow{
    Q_OBJECT
public:
    EventHandlers(GUI*);
    virtual ~EventHandlers();
    void bindDefaultRegisterInterface(QPushButton*,QLineEdit*,QLineEdit*,QLineEdit*,QLineEdit*,QPushButton*,RegisterInterface*);
    void cancelRegisterInterface(RegisterInterface*);
    void registrationProcessInit(QLineEdit*,QLineEdit*,QLineEdit*,QLineEdit*);
    void bindDefaultLogInInterface(QPushButton*,QLineEdit*,QLineEdit*,QPushButton*);
    void signUpButtonBind(QLineEdit*,QLineEdit*);
    void registerButtonBind();
private:
    std::shared_ptr<SQL> sql;
    GUI* gui;
};

#endif // EVENTHANDLERS_H
