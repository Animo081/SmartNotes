
#include "eventhandlers.h"
#include "gui.h"
#include "maininterface.h"

EventHandlers::EventHandlers(GUI* gui, Network* network): QObject(nullptr){

    this->network = network;
    this->gui = gui;

}

EventHandlers::~EventHandlers(){}

void EventHandlers::bindDefaultRegisterInterface(QPushButton* okButton, QLineEdit* usernameEdit, QLineEdit* passwordEdit, QLineEdit* passwordRepeatEdit, QLineEdit* emailEdit, QPushButton* cancelButton, Interface* register_interface){

    QMainWindow::connect(cancelButton, &QPushButton::clicked, [=] { cancelRegisterInterface(register_interface); });
    QMainWindow::connect(okButton, &QPushButton::clicked, [=] { registrationProcessInit(usernameEdit,passwordEdit,passwordRepeatEdit,emailEdit,register_interface); });

}

void EventHandlers::cancelRegisterInterface(Interface* register_interface){

    gui->finishRegistration();

}

void EventHandlers::registrationProcessInit(QLineEdit* usernameEdit, QLineEdit* passwordEdit, QLineEdit* passwordRepeatEdit, QLineEdit* emailEdit, Interface* register_interface){
    if (passwordEdit->text() == passwordRepeatEdit->text())
        network->registration(usernameEdit->text(),passwordEdit->text(),emailEdit->text(),register_interface);
}

void EventHandlers::bindDefaultLogInInterface(QPushButton* signInButton, QLineEdit* usernameEdit,QLineEdit* passwordEdit,QPushButton* registerButton, Interface* log_in_interface){

    QMainWindow::connect(signInButton, &QPushButton::clicked, [=] { signInButtonBind(usernameEdit,passwordEdit,log_in_interface); });
    QMainWindow::connect(registerButton, &QPushButton::clicked, [=] { registerButtonBind(); });

}

void EventHandlers::signInButtonBind(QLineEdit* usernameEdit,QLineEdit* passwordEdit,Interface* log_in_interface){

    network->signIn(usernameEdit->text(),passwordEdit->text(),log_in_interface);
}

void EventHandlers::registerButtonBind(){

    gui->createRegisterInterface();

}

void EventHandlers::bindDefaultMainInterface(QLabel* sign_out_label,MainInterface* main_interface){

    this->interface = main_interface;

    connect(interface->getNotesList(), SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListMailItemClicked(QListWidgetItem*)));
    connect(interface->getNotesList(), SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    connect(interface->getVersionsBox(), SIGNAL(activated(int)), this, SLOT(versionClickedAction()));

    connect(interface->getSubmitButton(), &QPushButton::clicked, [=]{sendCurrentNoteData(main_interface);});

    interface->getWidget("sign_out_label")->installEventFilter(this);
    interface->getWidget("app_settings_label")->installEventFilter(this);
    interface->getWidget("group_manager_label")->installEventFilter(this);
    interface->getWidget("categories_settings_label")->installEventFilter(this);
    interface->getWidget("personal_settings_label")->installEventFilter(this);
    interface->getWidget("choose_current_note_category_label")->installEventFilter(this);
    interface->getWidget("current_note_versions_label")->installEventFilter(this);
    interface->getWidget("delete_current_note_label")->installEventFilter(this);
    interface->getWidget("hideCurrentNoteSection")->installEventFilter(this);
    connect(this, &EventHandlers::mouseButtonEvent,[&](QWidget* widget, QMouseEvent * event){
        if (event->type() == QEvent::MouseButtonPress){
            if (widget->objectName() == "sign_out_label") initSignOut();
            if (widget->objectName() == "choose_current_note_category_label") { interface->getVersionsBox()->hide(); interface->getCategoryBox()->show(); }
            if (widget->objectName() == "current_note_versions_label") { interface->getCategoryBox()->hide(); interface->getVersionsBox()->show(); network->getVersions(interface); }
            if (widget->objectName() == "hideCurrentNoteSection") {
                interface->hideDefaultCurrentNoteSection();
                widget->hide();
            }
            if (widget->objectName() == "delete_current_note_label") deleteCurrentNoteData(interface);
            if (widget->objectName() == "personal_settings_label") { interface->createDefaultPersonalInfo(this); }
            if (widget->objectName() == "categories_settings_label") { interface->createDefaultCustomization(this); }
            if (widget->objectName() == "group_manager_label") { interface->createDefaultGroup(this); }
            if (widget->objectName() == "user_photo_label") {
                QString imagePath = QFileDialog::getOpenFileName(interface->getWindow(), tr("Open File"), "", tr("PNG (*.png)"));
                QImage imageObject(imagePath);
                QPixmap image = QPixmap::fromImage(imageObject);
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "PNG");
                if (buffer.size() <= 0)
                    interface->showMessage("Cannot open PNG");
                else{
                    interface->getPersonalInterface()->user_photo_label->setPixmap(image.scaled(QSize(100,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                }
            }
            if (widget->objectName() == "text_color_show_label"){
                interface->getCustomizationInterface()->color_dialog->setWhatsThis("1");
                interface->getCustomizationInterface()->color_dialog->show();
            }
            if (widget->objectName() == "background_color_show_label"){
                interface->getCustomizationInterface()->color_dialog->setWhatsThis("0");
                interface->getCustomizationInterface()->color_dialog->show();
            }
            if (widget->objectName() == "note_back_image"){
                QString imagePath = QFileDialog::getOpenFileName(interface->getWindow(), tr("Open File"), "", tr("JPEG (*.jpg *.jpeg)"));
                QImage imageObject(imagePath);
                QPixmap image = QPixmap::fromImage(imageObject);
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "JPG");
                if (buffer.size() <= 0)
                    interface->showMessage("Cannot open JPG");
                else{
                    interface->getCustomizationInterface()->note_back_image->setPixmap(image.scaled(QSize(155,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                    interface->getCustomizationInterface()->note_back_image->setWhatsThis(imagePath);
                }
            }
        }
    });

    network->getPersonalImage(interface);
    network->getCategoryListForMainInterface(interface);

    fillAllNotesSection(interface);

}

void EventHandlers::fillAllNotesSection(MainInterface* interface){
    //network->getCategories(interface);
    network->getAllNoteRows(interface);
}

void EventHandlers::sendCurrentNoteData(MainInterface* interface){

    interface->getWebPage()->page()->runJavaScript("send();",[=] (const QVariant &v){
        QString note_id = interface->getNotesList()->item(row_counter)->whatsThis();
        QString html;
        html = v.toString();
        QString name = interface->getNameEdit()->text();
        if (name == "") name = "New Note";
        QString category = interface->getCategoryBox()->currentData().toString();
        network->sendCurrentNoteData(html,name,category,note_id,interface);
        return;
    });

}

void EventHandlers::deleteCurrentNoteData(MainInterface* interface){
    network->deleteCurrentNoteData(interface);
}

void EventHandlers::initSignOut(){
    gui->finishMainProgram();
}

void EventHandlers::onListMailItemClicked(QListWidgetItem* item){

    row_counter = 0;
    for (row_counter; row_counter < interface->getNotesList()->count(); row_counter++)
        if (interface->getNotesList()->item(row_counter) == item) {
            break;
        }
    if (interface->getNotesList()->item(row_counter)->whatsThis() == "add_new_row_item"){
        interface->addNewRowInNotesList(row_counter,"New Note", "", "#FFFFFF", "#000000");
        network->createNewNote(row_counter, interface);
    }
}

void EventHandlers::selectionChanged(){

    if(interface->getNotesList()->currentItem()->whatsThis() != "add_new_row_item"){
        interface->getWidget("hideCurrentNoteSection")->show();
        interface->showDefaultCurrentNoteSection();
        network->getCurrentNote(this->interface);
    }

}

void EventHandlers::versionClickedAction(){

    network->setVersion(interface);

}

void EventHandlers::bindDefaultPersonalInterface(MainInterface* interface){

    interface->getPersonalInterface()->user_photo_label->installEventFilter(this);
    connect(interface->getPersonalInterface()->ok_button,&QPushButton::clicked,[=]{ preparePersonalData(interface); });
    connect(interface->getPersonalInterface()->cancel_button,&QPushButton::clicked,[=]{
        interface->getPersonalInterface()->personal_info_window->close();
        delete interface->getPersonalInterface();
    });

    network->getPersonalData(interface);

}

void EventHandlers::preparePersonalData(MainInterface* interface){

    QPixmap image = interface->getPersonalInterface()->user_photo_label->pixmap()->copy();
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QByteArray encoded = buffer.data().toBase64();

    QString firstname = interface->getPersonalInterface()->first_name_edit->text();
    QString lastname = interface->getPersonalInterface()->last_name_edit->text();
    QString phone = interface->getPersonalInterface()->phone_number_edit->text();
    QString email = interface->getPersonalInterface()->email_edit->text();
    QString aboutme = interface->getPersonalInterface()->description_edit->toPlainText();

    network->sendPersonalData(QLatin1String(encoded),firstname,lastname,phone,email,aboutme,interface);
}

void EventHandlers::bindDefaultCustomizationInterface(MainInterface* interface){

    interface->getCustomizationInterface()->text_color_show_label->installEventFilter(this);
    interface->getCustomizationInterface()->background_color_show_label->installEventFilter(this);
    interface->getCustomizationInterface()->note_back_image->installEventFilter(this);
    connect( interface->getCustomizationInterface()->color_dialog, &QColorDialog::colorSelected, [=]( const QColor& color ) {
        if (interface->getCustomizationInterface()->color_dialog->whatsThis() == "1"){
            interface->getCustomizationInterface()->text_color_show_label->setStyleSheet("QLabel {"
                                                                                         "border-style: solid;"
                                                                                         "border-width: 1px;"
                                                                                         "border-color: black; "
                                                                                         "background-color: "+color.name()+";"
                                                                                         "}");
            interface->getCustomizationInterface()->text_color_show_label->setWhatsThis(color.name());
        }
        else{
            interface->getCustomizationInterface()->background_color_show_label->setStyleSheet("QLabel {"
                                                                                               "border-style: solid;"
                                                                                               "border-width: 1px;"
                                                                                               "border-color: black; "
                                                                                               "background-color: "+color.name()+";"
                                                                                               "}");
            interface->getCustomizationInterface()->background_color_show_label->setWhatsThis(color.name());
        }
        interface->getCustomizationInterface()->item_customization_label->setStyleSheet("QLabel {"
                                                                                        "border-style: solid;"
                                                                                        "border-width: 1px;"
                                                                                        "border-color: black;"
                                                                                        "background-color: "+interface->getCustomizationInterface()->background_color_show_label->whatsThis()+";"
                                                                                        "color: "+interface->getCustomizationInterface()->text_color_show_label->whatsThis()+";"
                                                                                        "}");
    });
    connect(interface->getCustomizationInterface()->save_button,&QPushButton::clicked,[=]{ prepareCategoryData(interface); });
    connect(interface->getCustomizationInterface()->delete_button,&QPushButton::clicked,[=]{ });
    connect(interface->getCustomizationInterface()->cancel_button,&QPushButton::clicked,[=]{
        interface->getCustomizationInterface()->customization_window->close();
        delete interface->getCustomizationInterface();
    });
    connect(interface->getCustomizationInterface()->choose_category_box, SIGNAL(activated(int)), this, SLOT(categoryClickedAction()));

    network->getCategoryList(interface);

}

void EventHandlers::prepareCategoryData(MainInterface* interface){

    QImage imageObject(interface->getCustomizationInterface()->note_back_image->whatsThis());
    QPixmap image = QPixmap::fromImage(imageObject);
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");
    QByteArray encoded = buffer.data().toBase64();

    QString category = interface->getCustomizationInterface()->choose_category_box->currentData().toString();
    QString name = interface->getCustomizationInterface()->category_name_edit->text();
    QString text_color = interface->getCustomizationInterface()->text_color_show_label->whatsThis();
    QString back_color = interface->getCustomizationInterface()->background_color_show_label->whatsThis();
    QString description = interface->getCustomizationInterface()->description_edit->toPlainText();

    network->createCategory(QLatin1String(encoded), category, name, text_color, back_color,description, interface);

}

void EventHandlers::categoryClickedAction(){

    network->getCurrentCategoryData(interface);

}

void EventHandlers::bindDefaultGroupInterface(MainInterface* interface){

    //connect(interface->getGroupInterface()->create_group_button,&QPushButton::clicked,[=]{ network->createGroup(interface->getGroupInterface()->new_group_edit->text(), interface); });

}
