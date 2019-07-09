#include "maininterface.h"

MainInterface::MainInterface(QWidget* window, EventHandlers* event_handlers): QMainWindow(nullptr){

    this->window = window;
    setDefaultWindowSettings();
    createDefaultInterface();
    bindDefaultInterface(event_handlers);
    showWindow();
    window_size = window->size();

}

MainInterface::~MainInterface(){

    delete personal_settings_label;
    delete categories_settings_label;
    delete group_manager_label;
    delete app_settings_label;
    delete sign_out_label;
    delete user_facilities_layout;
    delete user_section_layout;

    delete new_note_row_item;
    delete all_notes_list;
    delete notes_sort_box;
    delete note_categories_box;
    delete notes_sort_layout;
    delete all_notes_section_layout;

    delete current_note_name_edit;
    delete choose_current_note_category_box;
    delete choose_current_note_version_box;
    delete choose_current_note_category_label;
    delete current_note_versions_label;
    delete delete_current_note_label;
    delete note_field;
    delete submit_current_note_button;
    delete current_note_options_layout;
    delete current_note_panel_layout;
    delete current_note_section_layout;

    delete window;
}

void MainInterface::setDefaultWindowSettings(){
    window->setWindowTitle("Smart Notes");
}

void MainInterface::createDefaultInterface(){

    main_layout = new QGridLayout(window);

    hideCurrentNoteSection = new QPushButton(tr("<"));
    hideCurrentNoteSection->setMaximumWidth(20);
    hideCurrentNoteSection->setObjectName("hideCurrentNoteSection");
    hideCurrentNoteSection->hide();

    main_layout->addLayout(createDefaultUserSection(),0,0);
    main_layout->addLayout(createDefaultAllNotesSection(),0,1);
    main_layout->addWidget(hideCurrentNoteSection,0,2);
    main_layout->addLayout(createDefaultCurrentNoteSection(),0,3);

    setAutoDeleteAttr();

}

QGridLayout* MainInterface::createDefaultUserSection(){

    user_section_layout = new QGridLayout();
    user_section_layout->setMargin(0);
    user_section_layout->setSpacing(20);

    personal_settings_label = new QLabel();
    personal_settings_label->setPixmap(QPixmap(":/images/images/default.png").scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    personal_settings_label->setToolTip("Аккаунт");
    personal_settings_label->setObjectName("personal_settings_label");
    personal_settings_label->setMaximumWidth(85);
    personal_settings_label->setMaximumHeight(85);

    user_facilities_layout = new QVBoxLayout();

    categories_settings_label = new QLabel();
    group_manager_label = new QLabel();
    app_settings_label = new QLabel();
    sign_out_label = new QLabel();

    categories_settings_label->setPixmap(QPixmap(":/images/images/category.png").scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    group_manager_label->setPixmap(QPixmap(":/images/images/group.png").scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    app_settings_label->setPixmap(QPixmap(":/images/images/settings.png").scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    sign_out_label->setPixmap(QPixmap(":/images/images/logout.png").scaled(QSize(85,85),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    categories_settings_label->setToolTip("Категории");
    group_manager_label->setToolTip("Группы");
    app_settings_label->setToolTip("Настройки");
    sign_out_label->setToolTip("Выход");

    categories_settings_label->setObjectName("categories_settings_label");
    group_manager_label->setObjectName("group_manager_label");
    app_settings_label->setObjectName("app_settings_label");
    sign_out_label->setObjectName("sign_out_label");

    categories_settings_label->setMaximumWidth(85);
    group_manager_label->setMaximumWidth(85);
    app_settings_label->setMaximumWidth(85);
    sign_out_label->setMaximumWidth(85);

    categories_settings_label->setMaximumHeight(85);
    group_manager_label->setMaximumHeight(85);
    app_settings_label->setMaximumHeight(85);
    sign_out_label->setMaximumHeight(85);

    user_facilities_layout->addWidget(categories_settings_label,0,Qt::AlignBottom);
    user_facilities_layout->addWidget(group_manager_label,0,Qt::AlignBottom);
    user_facilities_layout->addWidget(app_settings_label,0,Qt::AlignBottom);
    user_facilities_layout->addWidget(sign_out_label,0,Qt::AlignBottom);

    user_section_layout->addWidget(personal_settings_label,0,0,Qt::AlignTop);
    user_section_layout->addLayout(user_facilities_layout,1,0,Qt::AlignBottom);

    return user_section_layout;

}

QGridLayout* MainInterface::createDefaultAllNotesSection(){

    all_notes_section_layout = new QGridLayout();

    all_notes_list = new QListWidget();
    all_notes_list->setObjectName("all_notes_list");
    all_notes_list->setMaximumWidth(300);
    all_notes_list->setMinimumWidth(100);
    all_notes_list->setFont(QFont("Helvetica"));

    new_note_row_item = new QListWidgetItem(tr("+"), all_notes_list);
    new_note_row_item->setSizeHint(QSize(100,50));
    new_note_row_item->setTextAlignment(Qt::AlignCenter);
    new_note_row_item->setFont(QFont("Times",15));
    new_note_row_item->setWhatsThis("add_new_row_item");

    notes_sort_box = new QComboBox();
    notes_sort_box->addItem("По дате (сн. новые)", QVariant("По дате добавление (от новых к старым)"));
    notes_sort_box->addItem("По дате (сн. старые)", QVariant("По дате добавление (от старых к новым)"));
    notes_sort_box->addItem("Сначала свои", QVariant("По принадлежности (сначала свои)"));
    notes_sort_box->addItem("Сначала групповые", QVariant("По принадлежности (сначала записки групп)"));
    notes_sort_box->addItem("По алфавиту", QVariant("По алфавиту"));
    notes_sort_box->setCurrentIndex(0);

    note_categories_box = new QComboBox();
    note_categories_box->setMaxVisibleItems(5);
    note_categories_box->addItem("Все",QVariant("Показать все заметки"));
    note_categories_box->addItem("Свои",QVariant("Показать только свои заметки"));
    note_categories_box->addItem("Групповые",QVariant("Показать только групповые заметки"));
    note_categories_box->setCurrentIndex(0);

    notes_sort_layout = new QHBoxLayout();
    notes_sort_layout->addWidget(notes_sort_box);
    notes_sort_layout->addWidget(note_categories_box);

    all_notes_section_layout->addLayout(notes_sort_layout,0,0);
    all_notes_section_layout->addWidget(all_notes_list,1,0);

    return all_notes_section_layout;

}

QGridLayout* MainInterface::createDefaultCurrentNoteSection(){

    current_note_section_layout = new QGridLayout();

    current_note_panel_layout = new QGridLayout();

    current_note_name_edit = new QLineEdit();
    current_note_name_edit->setPlaceholderText("Set name");
    current_note_name_edit->setMaximumWidth(200);

    current_note_options_layout = new QHBoxLayout();
    current_note_options_layout->setMargin(0);
    current_note_options_layout->setSpacing(40);

    choose_current_note_category_box = new QComboBox();
    choose_current_note_category_box->hide();
    choose_current_note_category_box->addItem("Без категории",QVariant("Нет категории"));
    choose_current_note_category_box->setCurrentIndex(0);

    choose_current_note_version_box = new QComboBox();
    choose_current_note_version_box->hide();
    choose_current_note_version_box->addItem("Текущая версия",QVariant("Current"));
    choose_current_note_version_box->setCurrentIndex(0);

    choose_current_note_category_label = new QLabel();
    current_note_versions_label = new QLabel();
    delete_current_note_label = new QLabel();

    choose_current_note_category_label->setPixmap(QPixmap(":/images/images/select_category.png").scaled(QSize(38,38),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    current_note_versions_label->setPixmap(QPixmap(":/images/images/version.png").scaled(QSize(38,38),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    delete_current_note_label->setPixmap(QPixmap(":/images/images/delete.png").scaled(QSize(38,38),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    choose_current_note_category_label->setToolTip("Присвоить текущей заметки определённую категорию");
    current_note_versions_label->setToolTip("Просмотреть предыдущие версии текущей заметки");
    delete_current_note_label->setToolTip("Удалить текущую заметку");

    choose_current_note_category_label->setObjectName("choose_current_note_category_label");
    current_note_versions_label->setObjectName("current_note_versions_label");
    delete_current_note_label->setObjectName("delete_current_note_label");

    current_note_options_layout->addWidget(choose_current_note_category_box,0,Qt::AlignLeft);
    current_note_options_layout->addWidget(choose_current_note_version_box,0,Qt::AlignLeft);
    current_note_options_layout->addWidget(choose_current_note_category_label,0,Qt::AlignRight);
    current_note_options_layout->addWidget(current_note_versions_label,0,Qt::AlignRight);
    current_note_options_layout->addWidget(delete_current_note_label,0,Qt::AlignRight);

    note_field = new QWebEngineView();
    //note_field->page()->profile()->clearHttpCache();
    note_field->load(QUrl("http://localhost:8080/"));
    note_field->setMinimumWidth(600);

    submit_current_note_button = new QPushButton(QPushButton::tr("Submit"));

    current_note_panel_layout->addWidget(current_note_name_edit,0,0,Qt::AlignLeft);
    current_note_panel_layout->addLayout(current_note_options_layout,0,1,Qt::AlignRight);

    current_note_section_layout->addLayout(current_note_panel_layout,0,0);
    current_note_section_layout->addWidget(note_field,1,0);
    current_note_section_layout->addWidget(submit_current_note_button,2,0,Qt::AlignRight);

    hideDefaultCurrentNoteSection();

    return current_note_section_layout;

}

void MainInterface::showDefaultCurrentNoteSection(){

    current_note_name_edit->show();
    choose_current_note_category_label->show();
    current_note_versions_label->show();
    delete_current_note_label->show();
    note_field->show();
    submit_current_note_button->show();

}

void MainInterface::hideDefaultCurrentNoteSection(){

    current_note_name_edit->hide();
    choose_current_note_category_box->hide();
    choose_current_note_version_box->hide();
    choose_current_note_category_label->hide();
    current_note_versions_label->hide();
    delete_current_note_label->hide();
    note_field->hide();
    submit_current_note_button->hide();

    window->adjustSize();
    window->adjustSize();

}

void MainInterface::setAutoDeleteAttr(){

    personal_settings_label->setAttribute(Qt::WA_DeleteOnClose);
    categories_settings_label->setAttribute(Qt::WA_DeleteOnClose);
    group_manager_label->setAttribute(Qt::WA_DeleteOnClose);
    app_settings_label->setAttribute(Qt::WA_DeleteOnClose);
    sign_out_label->setAttribute(Qt::WA_DeleteOnClose);

    all_notes_list->setAttribute(Qt::WA_DeleteOnClose);
    notes_sort_box->setAttribute(Qt::WA_DeleteOnClose);
    note_categories_box->setAttribute(Qt::WA_DeleteOnClose);

    current_note_name_edit->setAttribute(Qt::WA_DeleteOnClose);
    choose_current_note_category_box->setAttribute(Qt::WA_DeleteOnClose);
    choose_current_note_version_box->setAttribute(Qt::WA_DeleteOnClose);
    choose_current_note_category_label->setAttribute(Qt::WA_DeleteOnClose);
    current_note_versions_label->setAttribute(Qt::WA_DeleteOnClose);
    delete_current_note_label->setAttribute(Qt::WA_DeleteOnClose);
    note_field->setAttribute(Qt::WA_DeleteOnClose);
    submit_current_note_button->setAttribute(Qt::WA_DeleteOnClose);

    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainInterface::showEveryhing(){

}

void MainInterface::showWindow(){
    window->show();
}

void MainInterface::bindDefaultInterface(EventHandlers* event_handlers){
    warningMessage = new QErrorMessage();
    event_handlers->bindDefaultMainInterface(sign_out_label,this);
}

void MainInterface::showMessage(QString message){
    warningMessage->showMessage(message);
}

QWidget* MainInterface::getWindow(){
    return this->window;
}

QSize MainInterface::getWindowDefaultSize(){
    return window_size;
}

QWidget* MainInterface::getWidget(QString widget){
    if (widget == "sign_out_label")
        return sign_out_label;
    if (widget == "app_settings_label")
        return app_settings_label;
    if (widget == "group_manager_label")
        return group_manager_label;
    if (widget == "categories_settings_label")
        return categories_settings_label;
    if (widget == "personal_settings_label")
        return personal_settings_label;
    if (widget == "choose_current_note_category_label")
        return choose_current_note_category_label;
    if (widget == "current_note_versions_label")
        return current_note_versions_label;
    if (widget == "delete_current_note_label")
        return delete_current_note_label;
    if (widget == "all_notes_list")
        return all_notes_list;
    if (widget == "hideCurrentNoteSection")
        return hideCurrentNoteSection;
    return new QWidget();
}

QListWidget* MainInterface::getNotesList(){
    return this->all_notes_list;
}

void MainInterface::addNewRowInNotesList(const int& row_counter,QString text, QString wtf, QString bg_color, QString text_color){

    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(100,50));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Times",15));
    item->setText(text);
    item->setWhatsThis(wtf);
    qDebug() << bg_color << text_color;
    item->setBackgroundColor(QColor(bg_color));
    item->setTextColor(QColor(text_color));

    all_notes_list->insertItem(row_counter, item);

}

QPushButton* MainInterface::getSubmitButton(){
    return submit_current_note_button;
}

QWebEngineView* MainInterface::getWebPage(){
    return note_field;
}

QComboBox* MainInterface::getCategoryBox(){
    return choose_current_note_category_box;
}

QComboBox* MainInterface::getAllCategoriesBox(){
    return note_categories_box;
}

QComboBox* MainInterface::getVersionsBox(){
    return choose_current_note_version_box;
}

QLineEdit* MainInterface::getNameEdit(){
    return current_note_name_edit;
}

QLabel* MainInterface::getPersonalSettingsLabel(){
    return personal_settings_label;
}

void MainInterface::createDefaultPersonalInfo(EventHandlers* event_handlers){

    personal_info = new PersonalInfo(event_handlers);

    personal_info->personal_info_window = new QWidget();

    personal_info->personal_section_layout = new QGridLayout(personal_info->personal_info_window);

    personal_info->personal_section_top_layout = new QGridLayout();
    personal_info->user_photo_label = new QLabel();
    personal_info->user_photo_label->setPixmap(QPixmap(":/images/images/default.png").scaled(QSize(100,100),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    personal_info->user_photo_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->user_photo_label->setObjectName("user_photo_label");

    personal_info->personal_section_edits_layout = new QGridLayout();
    personal_info->first_name_label = new QLabel(QLabel::tr("First name"));
    personal_info->last_name_label = new QLabel(QLabel::tr("Last name"));
    personal_info->phone_number_label = new QLabel(QLabel::tr("Phone number"));
    personal_info->email_label = new QLabel(QLabel::tr("E-mail"));

    personal_info->first_name_edit = new QLineEdit();
    personal_info->last_name_edit = new QLineEdit();
    personal_info->phone_number_edit = new QLineEdit();
    personal_info->email_edit = new QLineEdit();

    personal_info->first_name_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->last_name_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->phone_number_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->email_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->first_name_edit->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->last_name_edit->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->phone_number_edit->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->email_edit->setAttribute(Qt::WA_DeleteOnClose);

    personal_info->personal_section_edits_layout->addWidget(personal_info->first_name_label,0,0);
    personal_info->personal_section_edits_layout->addWidget(personal_info->last_name_label,0,1);
    personal_info->personal_section_edits_layout->addWidget(personal_info->phone_number_label,2,0);
    personal_info->personal_section_edits_layout->addWidget(personal_info->email_label,2,1);
    personal_info->personal_section_edits_layout->addWidget(personal_info->first_name_edit,1,0);
    personal_info->personal_section_edits_layout->addWidget(personal_info->last_name_edit,1,1);
    personal_info->personal_section_edits_layout->addWidget(personal_info->phone_number_edit,3,0);
    personal_info->personal_section_edits_layout->addWidget(personal_info->email_edit,3,1);

    personal_info->personal_section_top_layout->addWidget(personal_info->user_photo_label,0,0);
    personal_info->personal_section_top_layout->addLayout(personal_info->personal_section_edits_layout,0,1);

    personal_info->description_label = new QLabel(QLabel::tr("About me"));
    personal_info->description_label->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->description_edit = new QTextEdit();
    personal_info->description_edit->setAttribute(Qt::WA_DeleteOnClose);

    personal_info->button_controls_layout = new QVBoxLayout();
    personal_info->ok_button = new QPushButton(QPushButton::tr("OK"));
    personal_info->ok_button->setAttribute(Qt::WA_DeleteOnClose);
    personal_info->cancel_button = new QPushButton(QPushButton::tr("Cancel"));
    personal_info->cancel_button->setAttribute(Qt::WA_DeleteOnClose);

    personal_info->button_controls_layout->addWidget(personal_info->ok_button);
    personal_info->button_controls_layout->addWidget(personal_info->cancel_button);

    personal_info->personal_section_layout->addLayout(personal_info->personal_section_top_layout,0,0);
    personal_info->personal_section_layout->addWidget(personal_info->description_label,1,0);
    personal_info->personal_section_layout->addWidget(personal_info->description_edit,2,0);
    personal_info->personal_section_layout->addLayout(personal_info->button_controls_layout,3,0);

    personal_info->event_handler->bindDefaultPersonalInterface(this);

    personal_info->personal_info_window->show();

}

PersonalInfo::~PersonalInfo(){

    delete user_photo_label;
    delete first_name_label;
    delete last_name_label;
    delete phone_number_label;
    delete email_label;

    delete first_name_edit;
    delete last_name_edit;
    delete phone_number_edit;
    delete email_edit;

    delete description_label;
    delete description_edit;

    delete ok_button;
    delete cancel_button;

    delete button_controls_layout;
    delete personal_section_edits_layout;
    delete personal_section_top_layout;
    delete personal_section_layout;

    delete personal_info_window;

}

PersonalInfo* MainInterface::getPersonalInterface(){
    return this->personal_info;
}

void MainInterface::createDefaultCustomization(EventHandlers* event_handlers){

    customization = new Customization(event_handlers);

    customization->customization_window = new QWidget();

    customization->customization_section_layout = new QGridLayout(customization->customization_window);

    customization->not_description_layout = new QGridLayout();

    customization->choose_category_label = new QLabel(QLabel::tr("Category"));
    customization->choose_category_box = new QComboBox();
    customization->choose_category_box->addItem("Новая категория", QVariant("New category"));
    customization->choose_category_box->setCurrentIndex(0);

    customization->category_name_label = new QLabel(QLabel::tr("Name"));
    customization->category_name_edit = new QLineEdit();

    customization->color_picker_layout = new QGridLayout();

    customization->text_color_label = new QLabel(QLabel::tr("Text color"));
    customization->text_color_show_label = new QLabel();
    customization->text_color_show_label->setStyleSheet("QLabel {"
                                                        "border-style: solid;"
                                                        "border-width: 1px;"
                                                        "border-color: black; "
                                                        "background-color: black;"
                                                        "}");
    customization->text_color_show_label->setObjectName("text_color_show_label");
    customization->text_color_show_label->setWhatsThis("black");
    customization->text_color_show_label->setMinimumSize(QSize(25,25));

    customization->background_color_label = new QLabel(QLabel::tr("Background color"));
    customization->background_color_show_label = new QLabel();
    customization->background_color_show_label->setStyleSheet("QLabel {"
                                                              "border-style: solid;"
                                                              "border-width: 1px;"
                                                              "border-color: black; "
                                                              "background-color: white;"
                                                              "}");
    customization->background_color_show_label->setObjectName("background_color_show_label");
    customization->background_color_show_label->setWhatsThis("white");
    customization->background_color_show_label->setMinimumSize(QSize(25,25));

    customization->item_customization_label = new QLabel(QLabel::tr("Item"));
    customization->item_customization_label->setStyleSheet("QLabel {"
                                                           "border-style: solid;"
                                                           "border-width: 1px;"
                                                           "border-color: black;"
                                                           "background-color: white;"
                                                           "}");
    customization->item_customization_label->setAlignment(Qt::AlignCenter);

    customization->note_back_label = new QLabel(QLabel::tr("Note style"));
    customization->note_back_image = new QLabel("");
    customization->note_back_image->setStyleSheet("QLabel {"
                                                  "border-style: solid;"
                                                  "border-width: 1px;"
                                                  "border-color: black;"
                                                  "}");
    customization->note_back_image->setObjectName("note_back_image");

    customization->description_label = new QLabel(QLabel::tr("About category"));
    customization->description_edit = new QTextEdit();

    customization->controls_layout = new QHBoxLayout();

    customization->save_button = new QPushButton(QPushButton::tr("Save"));
    customization->delete_button = new QPushButton(QPushButton::tr("Delete"));
    customization->delete_button->setEnabled(false);

    customization->cancel_button = new QPushButton(QPushButton::tr("Cancel"));

    customization->color_dialog = new QColorDialog();
    customization->color_dialog->hide();

    customization->color_picker_layout->addWidget(customization->text_color_label,0,0);
    customization->color_picker_layout->addWidget(customization->text_color_show_label,0,1);
    customization->color_picker_layout->addWidget(customization->background_color_label,1,0);
    customization->color_picker_layout->addWidget(customization->background_color_show_label,1,1);

    customization->not_description_layout->addWidget(customization->choose_category_label,0,0);
    customization->not_description_layout->addWidget(customization->choose_category_box,0,1);
    customization->not_description_layout->addWidget(customization->category_name_label,1,0);
    customization->not_description_layout->addWidget(customization->category_name_edit,1,1);
    customization->not_description_layout->addLayout(customization->color_picker_layout,2,0);
    customization->not_description_layout->addWidget(customization->item_customization_label,2,1);
    customization->not_description_layout->addWidget(customization->note_back_label,3,0);
    customization->not_description_layout->addWidget(customization->note_back_image,3,1);

    customization->controls_layout->addWidget(customization->save_button);
    customization->controls_layout->addWidget(customization->delete_button);

    customization->customization_section_layout->addLayout(customization->not_description_layout,0,0);
    customization->customization_section_layout->addWidget(customization->description_label,1,0);
    customization->customization_section_layout->addWidget(customization->description_edit,2,0);
    customization->customization_section_layout->addLayout(customization->controls_layout,3,0);
    customization->customization_section_layout->addWidget(customization->cancel_button,4,0);

    customization->customization_window->setAttribute(Qt::WA_DeleteOnClose);
    customization->choose_category_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->choose_category_box->setAttribute(Qt::WA_DeleteOnClose);
    customization->category_name_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->category_name_edit->setAttribute(Qt::WA_DeleteOnClose);
    customization->text_color_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->text_color_show_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->background_color_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->background_color_show_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->item_customization_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->note_back_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->note_back_image->setAttribute(Qt::WA_DeleteOnClose);
    customization->description_label->setAttribute(Qt::WA_DeleteOnClose);
    customization->description_edit->setAttribute(Qt::WA_DeleteOnClose);
    customization->save_button->setAttribute(Qt::WA_DeleteOnClose);
    customization->cancel_button->setAttribute(Qt::WA_DeleteOnClose);
    customization->delete_button->setAttribute(Qt::WA_DeleteOnClose);

    customization->event_handler->bindDefaultCustomizationInterface(this);

    customization->customization_window->show();

}

Customization::~Customization(){

    delete choose_category_label;
    delete choose_category_box;

    delete category_name_label;
    delete category_name_edit;

    delete text_color_label;
    delete text_color_show_label;

    delete background_color_label;
    delete background_color_show_label;

    delete item_customization_label;

    delete note_back_label;
    delete note_back_image;

    delete description_label;
    delete description_edit;

    delete save_button;
    delete cancel_button;
    delete delete_button;

    delete controls_layout;
    delete color_picker_layout;
    delete not_description_layout;
    delete customization_section_layout;

    delete customization_window;

}

Customization* MainInterface::getCustomizationInterface(){
    return this->customization;
}

void MainInterface::createDefaultGroup(EventHandlers* event_handlers){

    group = new Group(event_handlers);

    group->group_window = new QWidget();

    group->my_groups_label = new QLabel(QLabel::tr("My groups"));
    group->new_group_label = new QLabel(QLabel::tr("Create group"));
    group->members_label = new QLabel(QLabel::tr("Members"));
    group->invite_label = new QLabel(QLabel::tr("Search"));
    group->notes_label = new QLabel(QLabel::tr("Notes"));

    group->cancel_button = new QPushButton(QPushButton::tr("Cancel"));
    group->create_group_button = new QPushButton(QPushButton::tr("Create"));
    group->invite_button = new QPushButton(QPushButton::tr("Invite"));
    group->share_button = new QPushButton(QPushButton::tr("Share"));

    group->look_for_users_edit = new QLineEdit();
    group->new_group_edit = new QLineEdit();

    group->my_groups_box = new QComboBox();
    group->group_members_box = new QComboBox();
    group->note_for_share_box = new QComboBox();

    group->create_layout = new QHBoxLayout();
    group->create_layout->addWidget(group->new_group_label);
    group->create_layout->addWidget(group->new_group_edit);
    group->create_layout->addWidget(group->create_group_button);

    group->invite_layout = new QHBoxLayout();
    group->invite_layout->addWidget(group->invite_label);
    group->invite_layout->addWidget(group->look_for_users_edit);
    group->invite_layout->addWidget(group->invite_button);

    group->share_layout = new QGridLayout();
    group->share_layout->addWidget(group->members_label,0,0);
    group->share_layout->addWidget(group->group_members_box,0,1);
    group->share_layout->addWidget(group->notes_label,1,0);
    group->share_layout->addWidget(group->note_for_share_box,1,1);
    group->share_layout->addWidget(group->share_button,2,0);
    group->share_layout->addWidget(group->cancel_button,2,1);

    group->group_section_layout = new QGridLayout(group->group_window);
    group->group_section_layout->addLayout(group->create_layout,0,0);
    group->group_section_layout->addWidget(group->my_groups_label,1,0);
    group->group_section_layout->addWidget(group->my_groups_box,2,0);
    group->group_section_layout->addLayout(group->invite_layout,3,0);
    group->group_section_layout->addLayout(group->share_layout,4,0);

    group->group_window->show();

}

