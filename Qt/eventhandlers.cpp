
#include "eventhandlers.h"
#include "gui.h"
#include "maininterface.h"

EventHandlers::EventHandlers(std::shared_ptr<Gui> gui,std::shared_ptr<Network> network):
	QObject(nullptr), network_(std::move(network)), gui_(std::move(gui)){ }

EventHandlers::~EventHandlers(){}

void EventHandlers::bindDefaultRegisterInterface(Interface* register_mainInterface){
/*
    QMainWindow::connect(cancelButton, &QPushButton::clicked, [=] { cancelRegisterInterface(register_mainInterface); });
    QMainWindow::connect(okButton, &QPushButton::clicked, [=] { registrationProcessInit(usernameEdit,passwordEdit,passwordRepeatEdit,emailEdit,register_mainInterface); });
*/
}

void EventHandlers::cancelRegisterInterface(Interface* register_mainInterface){
/*
    gui->finishRegistration();
*/
}

void EventHandlers::registrationProcessInit(QLineEdit* usernameEdit, QLineEdit* passwordEdit, QLineEdit* passwordRepeatEdit, QLineEdit* emailEdit, Interface* register_mainInterface){
/*	 if (passwordEdit->text() == passwordRepeatEdit->text())
        network->registration(usernameEdit->text(),passwordEdit->text(),emailEdit->text(),register_mainInterface);
*/
}

void EventHandlers::bindDefaultLogInInterface(Interface* log_in_mainInterface){
	/*
    QMainWindow::connect(signInButton, &QPushButton::clicked, [=] { signInButtonBind(usernameEdit,passwordEdit,log_in_mainInterface); });
    QMainWindow::connect(registerButton, &QPushButton::clicked, [=] { registerButtonBind(); });
	*/
}

void EventHandlers::signInButtonBind(QLineEdit* usernameEdit,QLineEdit* passwordEdit,Interface* log_in_mainInterface){
	/*
    network->signIn(usernameEdit->text(),passwordEdit->text(),log_in_mainInterface);
	*/
}

void EventHandlers::registerButtonBind(){
	/*
    gui->createRegisterInterface();
	*/
}

void EventHandlers::bindDefaultMainInterface(MainInterface* main_mainInterface){
	/*
    this->mainInterface = main_mainInterface;

    connect(mainInterface->getNotesList(), SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListMailItemClicked(QListWidgetItem*)));
    connect(mainInterface->getNotesList(), SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));

    connect(mainInterface->getVersionsBox(), SIGNAL(activated(int)), this, SLOT(versionClickedAction()));

    connect(mainInterface->getSubmitButton(), &QPushButton::clicked, [=]{sendCurrentNoteData(main_mainInterface);});

    mainInterface->getWidget("sign_out_label")->installEventFilter(this);
    mainInterface->getWidget("app_settings_label")->installEventFilter(this);
    mainInterface->getWidget("group_manager_label")->installEventFilter(this);
    mainInterface->getWidget("categories_settings_label")->installEventFilter(this);
    mainInterface->getWidget("personal_settings_label")->installEventFilter(this);
    mainInterface->getWidget("choose_current_note_category_label")->installEventFilter(this);
    mainInterface->getWidget("current_note_versions_label")->installEventFilter(this);
    mainInterface->getWidget("delete_current_note_label")->installEventFilter(this);
    mainInterface->getWidget("hideCurrentNoteSection")->installEventFilter(this);
    connect(this, &EventHandlers::mouseButtonEvent,[&](QWidget* widget, QMouseEvent * event){
        if (event->type() == QEvent::MouseButtonPress){
            if (widget->objectName() == "sign_out_label") initSignOut();
            if (widget->objectName() == "choose_current_note_category_label") { mainInterface->getVersionsBox()->hide(); mainInterface->getCategoryBox()->show(); }
            if (widget->objectName() == "current_note_versions_label") { mainInterface->getCategoryBox()->hide(); mainInterface->getVersionsBox()->show(); network->getVersions(mainInterface); }
            if (widget->objectName() == "hideCurrentNoteSection") {
                mainInterface->hideDefaultCurrentNoteSection();
                widget->hide();
            }
            if (widget->objectName() == "delete_current_note_label") deleteCurrentNoteData(mainInterface);
            if (widget->objectName() == "personal_settings_label") { mainInterface->createDefaultPersonalInfo(this); }
            if (widget->objectName() == "categories_settings_label") { mainInterface->createDefaultCustomization(this); }
            if (widget->objectName() == "group_manager_label") { mainInterface->createDefaultGroup(this); }
            if (widget->objectName() == "user_photo_label") {
                QString imagePath = QFileDialog::getOpenFileName(mainInterface->getWindow(), tr("Open File"), "", tr("PNG (*.png)"));
                QImage imageObject(imagePath);
                QPixmap image = QPixmap::fromImage(imageObject);
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "PNG");
                if (buffer.size() <= 0)
                    mainInterface->showMessage("Cannot open PNG");
                else{
                    mainInterface->getPersonalInterface()->user_photo_label->setPixmap(image.scaled(QSize(100,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                }
            }
            if (widget->objectName() == "text_color_show_label"){
                mainInterface->getCustomizationInterface()->color_dialog->setWhatsThis("1");
                mainInterface->getCustomizationInterface()->color_dialog->show();
            }
            if (widget->objectName() == "background_color_show_label"){
                mainInterface->getCustomizationInterface()->color_dialog->setWhatsThis("0");
                mainInterface->getCustomizationInterface()->color_dialog->show();
            }
            if (widget->objectName() == "note_back_image"){
                QString imagePath = QFileDialog::getOpenFileName(mainInterface->getWindow(), tr("Open File"), "", tr("JPEG (*.jpg *.jpeg)"));
                QImage imageObject(imagePath);
                QPixmap image = QPixmap::fromImage(imageObject);
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                image.save(&buffer, "JPG");
                if (buffer.size() <= 0)
                    mainInterface->showMessage("Cannot open JPG");
                else{
                    mainInterface->getCustomizationInterface()->note_back_image->setPixmap(image.scaled(QSize(155,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                    mainInterface->getCustomizationInterface()->note_back_image->setWhatsThis(imagePath);
                }
            }
        }
    });

    network->getPersonalImage(mainInterface);
    network->getCategoryListForMainInterface(mainInterface);

    fillAllNotesSection(mainInterface);
	*/
}

void EventHandlers::fillAllNotesSection(MainInterface* mainInterface){
	/*
    //network->getCategories(mainInterface);
    network->getAllNoteRows(mainInterface);
	*/
}

void EventHandlers::sendCurrentNoteData(MainInterface* mainInterface){
	/*
    mainInterface->getWebPage()->page()->runJavaScript("send();",[=] (const QVariant &v){
        QString note_id = mainInterface->getNotesList()->item(row_counter)->whatsThis();
        QString html;
        html = v.toString();
        QString name = mainInterface->getNameEdit()->text();
        if (name == "") name = "New Note";
        QString category = mainInterface->getCategoryBox()->currentData().toString();
        network->sendCurrentNoteData(html,name,category,note_id,mainInterface);
        return;
    });
	*/
}

void EventHandlers::deleteCurrentNoteData(MainInterface* mainInterface){
    //network->deleteCurrentNoteData(mainInterface);
}

void EventHandlers::initSignOut(){
    //gui->finishMainProgram();
}

void EventHandlers::onListMailItemClicked(QListWidgetItem* item){
	/*
    row_counter = 0;
    for (row_counter; row_counter < mainInterface->getNotesList()->count(); row_counter++)
        if (mainInterface->getNotesList()->item(row_counter) == item) {
            break;
        }
    if (mainInterface->getNotesList()->item(row_counter)->whatsThis() == "add_new_row_item"){
        mainInterface->addNewRowInNotesList(row_counter,"New Note", "", "#FFFFFF", "#000000");
        network->createNewNote(row_counter, mainInterface);
    }
	*/
}

void EventHandlers::selectionChanged(){
	/*
    if(mainInterface->getNotesList()->currentItem()->whatsThis() != "add_new_row_item"){
        mainInterface->getWidget("hideCurrentNoteSection")->show();
        mainInterface->showDefaultCurrentNoteSection();
        network->getCurrentNote(this->mainInterface);
    }
	*/
}

void EventHandlers::versionClickedAction(){

   // network->setVersion(mainInterface);

}

void EventHandlers::bindDefaultPersonalInterface(MainInterface* mainInterface){
	/*
    mainInterface->getPersonalInterface()->user_photo_label->installEventFilter(this);
    connect(mainInterface->getPersonalInterface()->ok_button,&QPushButton::clicked,[=]{ preparePersonalData(mainInterface); });
    connect(mainInterface->getPersonalInterface()->cancel_button,&QPushButton::clicked,[=]{
        mainInterface->getPersonalInterface()->personal_info_window->close();
        delete mainInterface->getPersonalInterface();
    });

    network->getPersonalData(mainInterface);
	*/
}

void EventHandlers::preparePersonalData(MainInterface* mainInterface){
	/*
    QPixmap image = mainInterface->getPersonalInterface()->user_photo_label->pixmap()->copy();
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QByteArray encoded = buffer.data().toBase64();

    QString firstname = mainInterface->getPersonalInterface()->first_name_edit->text();
    QString lastname = mainInterface->getPersonalInterface()->last_name_edit->text();
    QString phone = mainInterface->getPersonalInterface()->phone_number_edit->text();
    QString email = mainInterface->getPersonalInterface()->email_edit->text();
    QString aboutme = mainInterface->getPersonalInterface()->description_edit->toPlainText();

    network->sendPersonalData(QLatin1String(encoded),firstname,lastname,phone,email,aboutme,mainInterface);
	*/
}

void EventHandlers::bindDefaultCustomizationInterface(MainInterface* mainInterface){
	/*
    mainInterface->getCustomizationInterface()->text_color_show_label->installEventFilter(this);
    mainInterface->getCustomizationInterface()->background_color_show_label->installEventFilter(this);
    mainInterface->getCustomizationInterface()->note_back_image->installEventFilter(this);
    connect( mainInterface->getCustomizationInterface()->color_dialog, &QColorDialog::colorSelected, [=]( const QColor& color ) {
        if (mainInterface->getCustomizationInterface()->color_dialog->whatsThis() == "1"){
            mainInterface->getCustomizationInterface()->text_color_show_label->setStyleSheet("QLabel {"
                                                                                         "border-style: solid;"
                                                                                         "border-width: 1px;"
                                                                                         "border-color: black; "
                                                                                         "background-color: "+color.name()+";"
                                                                                         "}");
            mainInterface->getCustomizationInterface()->text_color_show_label->setWhatsThis(color.name());
        }
        else{
            mainInterface->getCustomizationInterface()->background_color_show_label->setStyleSheet("QLabel {"
                                                                                               "border-style: solid;"
                                                                                               "border-width: 1px;"
                                                                                               "border-color: black; "
                                                                                               "background-color: "+color.name()+";"
                                                                                               "}");
            mainInterface->getCustomizationInterface()->background_color_show_label->setWhatsThis(color.name());
        }
        mainInterface->getCustomizationInterface()->item_customization_label->setStyleSheet("QLabel {"
                                                                                        "border-style: solid;"
                                                                                        "border-width: 1px;"
                                                                                        "border-color: black;"
                                                                                        "background-color: "+mainInterface->getCustomizationInterface()->background_color_show_label->whatsThis()+";"
                                                                                        "color: "+mainInterface->getCustomizationInterface()->text_color_show_label->whatsThis()+";"
                                                                                        "}");
    });
    connect(mainInterface->getCustomizationInterface()->save_button,&QPushButton::clicked,[=]{ prepareCategoryData(mainInterface); });
    connect(mainInterface->getCustomizationInterface()->delete_button,&QPushButton::clicked,[=]{ });
    connect(mainInterface->getCustomizationInterface()->cancel_button,&QPushButton::clicked,[=]{
        mainInterface->getCustomizationInterface()->customization_window->close();
        delete mainInterface->getCustomizationInterface();
    });
    connect(mainInterface->getCustomizationInterface()->choose_category_box, SIGNAL(activated(int)), this, SLOT(categoryClickedAction()));

    network->getCategoryList(mainInterface);
	*/
}

void EventHandlers::prepareCategoryData(MainInterface* mainInterface){
	/*
    QImage imageObject(mainInterface->getCustomizationInterface()->note_back_image->whatsThis());
    QPixmap image = QPixmap::fromImage(imageObject);
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");
    QByteArray encoded = buffer.data().toBase64();

    QString category = mainInterface->getCustomizationInterface()->choose_category_box->currentData().toString();
    QString name = mainInterface->getCustomizationInterface()->category_name_edit->text();
    QString text_color = mainInterface->getCustomizationInterface()->text_color_show_label->whatsThis();
    QString back_color = mainInterface->getCustomizationInterface()->background_color_show_label->whatsThis();
    QString description = mainInterface->getCustomizationInterface()->description_edit->toPlainText();

    network->createCategory(QLatin1String(encoded), category, name, text_color, back_color,description, mainInterface);
	*/
}

void EventHandlers::categoryClickedAction(){

    //network->getCurrentCategoryData(mainInterface);

}

void EventHandlers::bindDefaultGroupInterface(MainInterface* mainInterface){

    //connect(mainInterface->getGroupInterface()->create_group_button,&QPushButton::clicked,[=]{ network->createGroup(mainInterface->getGroupInterface()->new_group_edit->text(), mainInterface); });

}
