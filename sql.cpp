#include "sql.h"

SQL::SQL():QMainWindow(nullptr){

}

void SQL::signUp(const QString& usernameEditText,const QString& passwordEditText){

    if (!usernameEditText.contains(" ") && !passwordEditText.contains(" ")){
        QNetworkRequest request(QUrl("http://localhost:8080/signUp/?username="+usernameEditText+"&password="+passwordEditText+""));
        manager = new QNetworkAccessManager();
        reply = manager->get(request);
        connect(reply, SIGNAL(finished()),this,SLOT(getReplyFinished()));
    }

}

void SQL::registration(const QString& usernameEditText, const QString& passwordEditText, const QString& emailEditText){

    if (!usernameEditText.contains(" ") && !passwordEditText.contains(" ") && !emailEditText.contains(" ")){
        QNetworkRequest request(QUrl("http://localhost:8080/registration/?username="+usernameEditText+"&password="+passwordEditText+"&email="+emailEditText+""));
        manager = new QNetworkAccessManager();
        reply = manager->get(request);
        connect(reply, SIGNAL(finished()),this,SLOT(getReplyFinished()));
    }

}

void SQL::getReplyFinished(){

    QErrorMessage* warningMessage = new QErrorMessage();
    warningMessage->showMessage(reply->readAll());
    warningMessage->setAttribute(Qt::WA_DeleteOnClose);
    if(reply->error() != QNetworkReply::NoError)
    {
        warningMessage->showMessage(reply->errorString());
        reply->deleteLater();
        return;
    }
    reply->deleteLater();
}
