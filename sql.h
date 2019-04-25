#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QMessageBox>
#include <QErrorMessage>


class SQL: public QMainWindow{
    Q_OBJECT
public:
    SQL();
    void signUp(const QString&,const QString&);
    void registration(const QString&,const QString&,const QString&);
public slots:
    void getReplyFinished();
private:
    QNetworkReply* reply;
    QNetworkAccessManager* manager;
};

#endif // SQL_H
