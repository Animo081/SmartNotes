#ifndef EVENTHANDLERS_H
#define EVENTHANDLERS_H
#define emit

#include <iostream>
#include <QtGui>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QListWidgetItem>
#include <QListWidget>
#include <QWebEngineView>
#include <QFileDialog>
#include "network.h"

class GUI;

class Interface;

class MainInterface;

class EventHandlers: public QObject{
    Q_OBJECT
    bool eventFilter(QObject * obj, QEvent * ev) Q_DECL_OVERRIDE {
        if ((ev->type() == QEvent::MouseButtonPress
            || ev->type() == QEvent::MouseButtonRelease
            || ev->type() == QEvent::MouseButtonDblClick)
            && obj->isWidgetType())
          emit mouseButtonEvent(static_cast<QWidget*>(obj),
                                static_cast<QMouseEvent*>(ev));
        return false;
      }
public:
    Q_SIGNAL void mouseButtonEvent(QWidget *, QMouseEvent *);
    Q_SIGNAL void notifyRanJavaScript();
    void installOn(QWidget * widget) {
        widget->installEventFilter(this);
    }


    EventHandlers(GUI*,Network*);
    virtual ~EventHandlers();
    void bindDefaultRegisterInterface(QPushButton*,QLineEdit*,QLineEdit*,QLineEdit*,QLineEdit*,QPushButton*,Interface*);
    void cancelRegisterInterface(Interface*);
    void registrationProcessInit(QLineEdit*,QLineEdit*,QLineEdit*,QLineEdit*,Interface*);
    void bindDefaultLogInInterface(QPushButton*,QLineEdit*,QLineEdit*,QPushButton*,Interface*);
    void signInButtonBind(QLineEdit*,QLineEdit*,Interface*);
    void registerButtonBind();
    void bindDefaultMainInterface(QLabel*,MainInterface*);
    void fillAllNotesSection(MainInterface*);
    void sendCurrentNoteData(MainInterface*);
    void deleteCurrentNoteData(MainInterface*);
    void initSignOut();

    void bindDefaultPersonalInterface(MainInterface*);
    void preparePersonalData(MainInterface*);

    void bindDefaultCustomizationInterface(MainInterface*);
    void prepareCategoryData(MainInterface*);

    void bindDefaultGroupInterface(MainInterface*);
public slots:
    void onListMailItemClicked(QListWidgetItem* item);
    void selectionChanged();
    void versionClickedAction();
    void categoryClickedAction();
private:
    MainInterface* interface;
    Network* network;
    GUI* gui;
    int row_counter;
};

#endif // EVENTHANDLERS_H
