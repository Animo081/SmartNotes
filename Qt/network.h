#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QSignalMapper>

class Interface;

class MainInterface;

class Gui;

class Network: public QMainWindow{
    Q_OBJECT
public:
    Network();
    void setGui(std::shared_ptr<Gui> gui);
    void signIn(const QString&,const QString&,Interface*);
    void registration(const QString&,const QString&,const QString&,Interface*);
    //void getCategories(MainInterface*);
    void getAllNoteRows(MainInterface*);
    void getCurrentNote(MainInterface*);
    void createNewNote(const int&, MainInterface*);
    void sendCurrentNoteData(const QString&,const QString&,const QString&,const QString&, MainInterface*);
    void deleteCurrentNoteData(MainInterface*);
    void sendPersonalData(QJsonValue,QString,QString,QString,QString,QString,MainInterface*);
    void getPersonalData(MainInterface*);
    void getPersonalImage(MainInterface*);
    void setVersion(MainInterface*);
    void getVersions(MainInterface*);
    void createCategory(QJsonValue,QString,QString,QString,QString,QString,MainInterface*);
    void getCategoryList(MainInterface*);
    void getCategoryListForMainInterface(MainInterface*);
    void getCurrentCategoryData(MainInterface*);
    void customizeByCurrentCategory(MainInterface*);
    void createGroup(QString, MainInterface*);
public slots:
    void getReplyFinished();
    void syncRequestFinished(QNetworkReply*);
    void syncRequestFinished_allNotes(QNetworkReply*);
    void syncRequestFinished_currentNote(QNetworkReply*);
    void syncRequestFinished_currentNoteDelete(QNetworkReply*);
    void syncRequestFinished_sendPersonalData(QNetworkReply*);
    void syncRequestFinished_getPersonalData(QNetworkReply*);
    void syncRequestFinished_getPersonalImage(QNetworkReply*);
    void syncRequestFinished_setVersions(QNetworkReply*);
    void syncRequestFinished_getVersions(QNetworkReply*);
    void syncRequestFinished_createCategory(QNetworkReply*);
    void syncRequestFinished_getCategoryList(QNetworkReply*);
    void syncRequestFinished_getCategoryListForMainInterface(QNetworkReply*);
    void syncRequestFinished_getCategoryData(QNetworkReply*);
    void syncRequestFinished_customizeByCurrentCategory(QNetworkReply*);
    void syncRequestFinished_createGroup(QNetworkReply*);
private:
    int row_counter;
    QString category_name;
    //Interface* interface;
    MainInterface* main_interface;
    std::shared_ptr<Gui> gui_;
    QString message;
    QString user_id;
    QNetworkReply* reply;
    QNetworkAccessManager* manager;
};

#endif // SQL_H
