#include "network.h"
#include "gui.h"
#include "maininterface.h"

Network::Network():QMainWindow(nullptr){
    category_name = "";
}

void Network::setGui(GUI* gui){
    this->gui = gui;
}

void Network::signIn(const QString& usernameEditText,const QString& passwordEditText,Interface* log_in_interface){

    if (!usernameEditText.contains(" ") && !passwordEditText.contains(" ")){
        this->interface = log_in_interface;
        QNetworkRequest request(QUrl("http://localhost:8080/signIn/?username="+usernameEditText+"&password="+passwordEditText+""));
        manager = new QNetworkAccessManager();
        reply = manager->get(request);
        connect(reply, SIGNAL(finished()),this,SLOT(getReplyFinished()));
    }

}

void Network::registration(const QString& usernameEditText, const QString& passwordEditText, const QString& emailEditText,Interface* register_interface){

    if (!usernameEditText.contains(" ") && !passwordEditText.contains(" ") && !emailEditText.contains(" ")){
        this->interface = register_interface;
        QNetworkRequest request(QUrl("http://localhost:8080/registration/?username="+usernameEditText+"&password="+passwordEditText+"&email="+emailEditText+""));
        manager = new QNetworkAccessManager();
        reply = manager->get(request);
        connect(reply, SIGNAL(finished()),this,SLOT(getReplyFinished()));
    }

}

/*void Network::getCategories(MainInterface* main_interface){

    this->interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getusercategories");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id",user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(syncRequestFinished(QNetworkReply*)));

    manager->post(request, jsonData);

}*/

void Network::getAllNoteRows(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getusernotes");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id",user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(syncRequestFinished_allNotes(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getCurrentNote(MainInterface* main_interface){

    this->main_interface = main_interface;
    main_interface->getNameEdit()->setText("");
    main_interface->getWebPage()->page()->runJavaScript("function setContent(){return $('#content').froalaEditor('html.set','');} setContent();",[=] (const QVariant &v){

        QUrl serviceUrl = QUrl("http://localhost:8080/getcurrentnote");
        QNetworkRequest request(serviceUrl);

        QJsonObject json;
        json.insert("note_id",main_interface->getNotesList()->currentItem()->whatsThis());
        QJsonDocument jsonDoc(json);
        QByteArray jsonData= jsonDoc.toJson();

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

        manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(syncRequestFinished_currentNote(QNetworkReply*)));

        manager->post(request, jsonData);


    });

}

void Network::createNewNote(const int& row_counter, MainInterface* main_interface){

    this->row_counter = row_counter;
    this->interface = main_interface;
    QNetworkRequest request(QUrl("http://localhost:8080/newnote/?user_id="+user_id));
    manager = new QNetworkAccessManager();
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()),this,SLOT(getReplyFinished()));

}

void Network::sendCurrentNoteData(const QString& html,const QString& name,const QString& category,const QString& note_id, MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/sendcurrentnote");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("html",html);
    json.insert("name",name);
    json.insert("category",category);
    json.insert("note_id",note_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(syncRequestFinished(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::deleteCurrentNoteData(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/deletecurrentnote");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("note_id",main_interface->getNotesList()->currentItem()->whatsThis());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_currentNoteDelete(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::sendPersonalData(QJsonValue image, QString firstname, QString lastname, QString phone_number, QString email, QString about_me, MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/setpersonalinfo");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id",user_id);
    json.insert("image",image);
    json.insert("firstname",firstname);
    json.insert("lastname",lastname);
    json.insert("phone_number",phone_number);
    json.insert("email",email);
    json.insert("about_me",about_me);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_sendPersonalData(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getPersonalData(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getpersonalinfo");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id",user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getPersonalData(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getPersonalImage(MainInterface * main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getpersonalimage");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id",user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getPersonalImage(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::setVersion(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/setversion");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("note_id",main_interface->getNotesList()->currentItem()->whatsThis());
    json.insert("version", main_interface->getVersionsBox()->currentData().toString());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_setVersions(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getVersions(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getversions");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("note_id",main_interface->getNotesList()->currentItem()->whatsThis());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getVersions(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::createCategory(QJsonValue encoded, QString category, QString name, QString text_color, QString back_color, QString description, MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/createcategory");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    json.insert("image", encoded);
    json.insert("category", category);
    json.insert("name", name);
    json.insert("text_color", text_color);
    json.insert("back_color", back_color);
    json.insert("description", description);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    category_name = name;

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_createCategory(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getCategoryList(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getcategorylist");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getCategoryList(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getCategoryListForMainInterface(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getcategorylist");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getCategoryListForMainInterface(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::getCurrentCategoryData(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getcategorydata");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    json.insert("category",main_interface->getCustomizationInterface()->choose_category_box->currentData().toString());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_getCategoryData(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::customizeByCurrentCategory(MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/getcategorydata");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    json.insert("category",main_interface->getCategoryBox()->currentData().toString());
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_customizeByCurrentCategory(QNetworkReply*)));

    manager->post(request, jsonData);

}

void Network::createGroup(QString group_name, MainInterface* main_interface){

    this->main_interface = main_interface;

    QUrl serviceUrl = QUrl("http://localhost:8080/creategroup");
    QNetworkRequest request(serviceUrl);

    QJsonObject json;
    json.insert("user_id", user_id);
    json.insert("group_name",group_name);
    QJsonDocument jsonDoc(json);
    QByteArray jsonData= jsonDoc.toJson();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(jsonData.size()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(syncRequestFinished_createGroup(QNetworkReply*)));

    manager->post(request, jsonData);
}

void Network::getReplyFinished(){

    if(reply->error() != QNetworkReply::NoError)
    {
        interface->showMessage(reply->errorString());
        reply->deleteLater();
        return;
    }
    message = reply->readAll();
    QRegExp re("[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");
    if (re.exactMatch(message) && message != ""){
        interface->getNotesList()->item(row_counter)->setWhatsThis(message);
        interface->getNotesList()->setCurrentRow(row_counter);
    } else {
        if (!message.contains("Welcome"))
            interface->showMessage(message);
        if (message.contains("Welcome")){
            user_id = message.mid(QString("Welcome, ").size());
            this->gui->startMainProgram();
        }
        if (message == "Registration completed")
            this->gui->finishRegistration();
    }
    reply->deleteLater();

}

void Network::syncRequestFinished(QNetworkReply*){
    if (main_interface->getCategoryBox()->isHidden()) main_interface->getVersionsBox()->show();
    getVersions(main_interface);
    customizeByCurrentCategory(main_interface);
}

void Network::syncRequestFinished_allNotes(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.array();
    //main_interface->addNewRowInNotesList(0,"New Note","");
    foreach (const QJsonValue & v, array){//QString::number(v.toObject().value("note_id").toInt()
        main_interface->addNewRowInNotesList(main_interface->getNotesList()->count()-1,v.toObject().value("name").toString(),v.toObject().value("note_id").toString(),v.toObject().value("category_color").toString(),v.toObject().value("text_color").toString());
        QCoreApplication::processEvents();
    }

}

void Network::syncRequestFinished_currentNote(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.array();
    foreach (const QJsonValue & v, array){
        main_interface->getNameEdit()->setText(v.toObject().value("name").toString());
        QString html = v.toObject().value("content").toString();
        QString back = v.toObject().value("image").toString();
        main_interface->getWebPage()->page()->runJavaScript("function setBackground(){$('body').css('background-image', 'none');} setBackground();",[=](const QVariant &v){
        });
        if (v.toObject().value("image").toString() != "")
            main_interface->getWebPage()->page()->runJavaScript("function setBackground(){$('body').css('background', 'url(data:image/png;base64," + back + ") no-repeat center center fixed');$('body').css('background-size', 'cover');} setBackground();",[=](const QVariant &v){
            });
        main_interface->getWebPage()->page()->runJavaScript("function setContent(){return $('#content').froalaEditor('html.set','"+html+"');} setContent();",[=] (const QVariant &v){
        });

        QCoreApplication::processEvents();
    }

}

void Network::syncRequestFinished_currentNoteDelete(QNetworkReply*){

    main_interface->getWebPage()->page()->runJavaScript("function setContent(){return $('#content').froalaEditor('html.set','');} setContent();",[=] (const QVariant &v){
        main_interface->getNotesList()->takeItem(main_interface->getNotesList()->currentRow());
        main_interface->hideDefaultCurrentNoteSection();
        main_interface->getWidget("hideCurrentNoteSection")->hide();
    });

}

void Network::syncRequestFinished_sendPersonalData(QNetworkReply* reply){
    main_interface->showMessage(reply->readAll());
    getPersonalImage(main_interface);
}

void Network::syncRequestFinished_getPersonalData(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    main_interface->getPersonalInterface()->first_name_edit->setText(object["firstname"].toString());
    main_interface->getPersonalInterface()->last_name_edit->setText(object["lastname"].toString());
    main_interface->getPersonalInterface()->phone_number_edit->setText(object["phone_number"].toString());
    main_interface->getPersonalInterface()->email_edit->setText(object["email"].toString());
    main_interface->getPersonalInterface()->description_edit->setText(object["about_me"].toString());
    if (object["image"].toString().length() >= 1){
        auto const encoded = object["image"].toString().toLatin1();
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
        main_interface->getPersonalInterface()->user_photo_label->setPixmap(p.scaled(QSize(100,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

}

void Network::syncRequestFinished_getPersonalImage(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    if (object["image"].toString().length() >= 1){
        auto const encoded = object["image"].toString().toLatin1();
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
        main_interface->getPersonalSettingsLabel()->setPixmap(p.scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

}

void Network::syncRequestFinished_setVersions(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QString html = document.object().value("content").toString();
    main_interface->getWebPage()->page()->runJavaScript("function setContent(){return $('#content').froalaEditor('html.set','"+html+"');} setContent();",[=] (const QVariant &v){
    });

}

void Network::syncRequestFinished_getVersions(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.array();
    while (main_interface->getVersionsBox()->count() > 1)
        main_interface->getVersionsBox()->removeItem(main_interface->getVersionsBox()->count() - 1);
    foreach (const QJsonValue & v, array){
        main_interface->getVersionsBox()->addItem(v.toObject().value("version").toString().mid(2,10)+ ":" + v.toObject().value("version").toString().mid(11,8),v.toObject().value("version").toString());
        QCoreApplication::processEvents();
    }

}

void Network::syncRequestFinished_createCategory(QNetworkReply* reply){
    main_interface->showMessage(reply->readAll());
    getCategoryList(main_interface);
    getCategoryListForMainInterface(main_interface);
}

void Network::syncRequestFinished_getCategoryList(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.array();
    while (main_interface->getCustomizationInterface()->choose_category_box->count() > 1)
        main_interface->getCustomizationInterface()->choose_category_box->removeItem(main_interface->getCustomizationInterface()->choose_category_box->count() - 1);
    foreach (const QJsonValue & v, array){
        main_interface->getCustomizationInterface()->choose_category_box->addItem(v.toObject().value("category").toString(),v.toObject().value("category").toString());
        QCoreApplication::processEvents();
    }
    if (category_name != ""){
        main_interface->getCustomizationInterface()->choose_category_box->setCurrentIndex(main_interface->getCustomizationInterface()->choose_category_box->findData(category_name));
        category_name = "";
    }

}

void Network::syncRequestFinished_getCategoryListForMainInterface(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonArray array = document.array();
    while (main_interface->getCategoryBox()->count() > 1)
        main_interface->getCategoryBox()->removeItem(main_interface->getCategoryBox()->count() - 1);
    for (int i = 0; i < main_interface->getAllCategoriesBox()->count();i++)
        if (main_interface->getAllCategoriesBox()->itemData(i).toString() != "Показать все заметки" && main_interface->getAllCategoriesBox()->itemData(i).toString() != "Показать только свои заметки")
            main_interface->getAllCategoriesBox()->removeItem(i);
    foreach (const QJsonValue & v, array){
        main_interface->getCategoryBox()->addItem(v.toObject().value("category").toString(),v.toObject().value("category").toString());
        main_interface->getAllCategoriesBox()->addItem(v.toObject().value("category").toString(),v.toObject().value("category").toString());
        QCoreApplication::processEvents();
    }
    main_interface->getAllCategoriesBox()->addItem("Групповые",QVariant("Показать только групповые заметки"));


}

void Network::syncRequestFinished_getCategoryData(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    main_interface->getCustomizationInterface()->category_name_edit->setText(object["category"].toString());
    main_interface->getCustomizationInterface()->text_color_show_label->setStyleSheet("QLabel {"
                                                                                      "border-style: solid;"
                                                                                      "border-width: 1px;"
                                                                                      "border-color: black; "
                                                                                      "background-color: "+object["text_color"].toString()+";"
                                                                                      "}");
    main_interface->getCustomizationInterface()->text_color_show_label->setWhatsThis(object["text_color"].toString());
    main_interface->getCustomizationInterface()->background_color_show_label->setStyleSheet("QLabel {"
                                                                                            "border-style: solid;"
                                                                                            "border-width: 1px;"
                                                                                            "border-color: black; "
                                                                                            "background-color: "+object["category_color"].toString()+";"
                                                                                            "}");
    main_interface->getCustomizationInterface()->background_color_show_label->setWhatsThis(object["category_color"].toString());
    main_interface->getCustomizationInterface()->item_customization_label->setStyleSheet("QLabel {"
                                                                                         "border-style: solid;"
                                                                                         "border-width: 1px;"
                                                                                         "border-color: black;"
                                                                                         "background-color: "+main_interface->getCustomizationInterface()->background_color_show_label->whatsThis()+";"
                                                                                         "color: "+main_interface->getCustomizationInterface()->text_color_show_label->whatsThis()+";"
                                                                                         "}");
    main_interface->getCustomizationInterface()->description_edit->setText(object["description"].toString());
    if (object["image"].toString().length() >= 1){
        auto const encoded = object["image"].toString().toLatin1();
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(encoded), "JPG");
        main_interface->getCustomizationInterface()->note_back_image->setPixmap(p.scaled(QSize(155,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

}

void Network::syncRequestFinished_customizeByCurrentCategory(QNetworkReply* reply){

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();
    QString color;
    if (object["category_color"].toString() == "") color = "#000000";
    else color = object["category_color"].toString();
    main_interface->getNotesList()->currentItem()->setBackgroundColor(color);
    if (object["text_color"].toString() == "") color = "#FFFFFF";
    else color = object["text_color"].toString();
    main_interface->getNotesList()->currentItem()->setTextColor(color);
    main_interface->getWebPage()->page()->runJavaScript("function setBackground(){$('body').css('background-image', 'none');} setBackground();",[=](const QVariant &v){
    });
    QString back = object["image"].toString();
    if (object["image"].toString() != "")
        main_interface->getWebPage()->page()->runJavaScript("function setBackground(){$('body').css('background', 'url(data:image/png;base64," + back + ") no-repeat center center fixed');$('body').css('background-size', 'cover');} setBackground();",[=](const QVariant &v){
        });

}

void Network::syncRequestFinished_createGroup(QNetworkReply* reply){



}
