#include "maininterface.h"
#include "gui.h"

MainInterface::MainInterface(std::shared_ptr<Tools> tools, QWidget* parent):
	tools_(std::move(tools)), QWidget(parent) {}

MainInterface::~MainInterface() {}

void MainInterface::createInterface(const EventHandlers* eventHandlers) {

	createInterfaceElements();
	placeInterfaceElements();

	setAttributeToAllWidgets(Qt::WA_DeleteOnClose);
	tools_->setSizePolicyToQWidgets(QSizePolicy::Fixed, QSizePolicy::Fixed, {
		personalSettingsButton_.get(),
		customizationButton_.get(),
		groupsManagerButton_.get(),
		appSettingsButton_.get(),
		signOutButton_.get(),
	});

	eventHandlers->bindDefaultMainInterface(this);
}

void MainInterface::createInterfaceElements(){

    mainInterfaceLayout_.reset(new QGridLayout(this));

	createUserSection();
	createAllNotesSection();
	createCurrentNoteSection();
}

void MainInterface::placeInterfaceElements() const {

	placeUserSection();
	placeAllNotesSection();
	placeCurrentNoteSection();

	mainInterfaceLayout_->addLayout(userSectionLayout_.get(), 0, 0);
	mainInterfaceLayout_->addLayout(allNotesSectionLayout_.get(), 0, 1);
	mainInterfaceLayout_->addWidget(hideCurrentNoteSectionButton_.get(), 0, 2);
	mainInterfaceLayout_->addLayout(currentNoteSectionLayout_.get(), 0, 3);
}

void MainInterface::createUserSection() {

	userSectionLayout_.reset(new QGridLayout());
	userSectionLayout_->setObjectName("userSectionLayout");

	personalSettingsButton_.reset(new QPushButton());
	personalSettingsButton_->setToolTip("Account");
	personalSettingsButton_->setIcon(QIcon(":/images/images/default.png"));
	personalSettingsButton_->setIconSize(QSize(85, 85));	

	userFacilitiesLayout_.reset(new QVBoxLayout());

	customizationButton_.reset(new QPushButton());
	customizationButton_->setToolTip("Customization");
	customizationButton_->setIcon(QIcon(":/images/images/category.png"));
	customizationButton_->setIconSize(QSize(85, 85));

	groupsManagerButton_.reset(new QPushButton());
	groupsManagerButton_->setToolTip("Groups");
	groupsManagerButton_->setIcon(QIcon(":/images/images/group.png"));
	groupsManagerButton_->setIconSize(QSize(85, 85));

	appSettingsButton_.reset(new QPushButton());
	appSettingsButton_->setToolTip("Settings");
	appSettingsButton_->setIcon(QIcon(":/images/images/settings.png"));
	appSettingsButton_->setIconSize(QSize(85, 85));
	
	signOutButton_.reset(new QPushButton());
	signOutButton_->setToolTip("Sign out");
	signOutButton_->setIcon(QIcon(":/images/images/logout.png"));
	signOutButton_->setIconSize(QSize(85, 85));
}

void MainInterface::placeUserSection() const {
	
	userFacilitiesLayout_->addWidget(customizationButton_.get());
	userFacilitiesLayout_->addWidget(groupsManagerButton_.get());
	userFacilitiesLayout_->addWidget(appSettingsButton_.get());
	userFacilitiesLayout_->addWidget(signOutButton_.get());

	userSectionLayout_->addWidget(personalSettingsButton_.get(), 0, 0, Qt::AlignTop);
	userSectionLayout_->addLayout(userFacilitiesLayout_.get(), 1, 0, Qt::AlignBottom);
}

void MainInterface::createAllNotesSection() {

	allNotesSectionLayout_.reset(new QGridLayout());

	displayedNotesLimitersLayout_.reset(new QHBoxLayout());

	notesSortsBox_.reset(new QComboBox());
	notesSortsBox_->addItem("По дате (сн. новые)", QVariant("По дате добавление (от новых к старым)"));
	notesSortsBox_->addItem("По дате (сн. старые)", QVariant("По дате добавление (от старых к новым)"));
	notesSortsBox_->addItem("Сначала свои", QVariant("По принадлежности (сначала свои)"));
	notesSortsBox_->addItem("Сначала групповые", QVariant("По принадлежности (сначала записки групп)"));
	notesSortsBox_->addItem("По алфавиту", QVariant("По алфавиту"));
	notesSortsBox_->setCurrentIndex(0);

	notesCategoriesBox_.reset(new QComboBox());
	notesCategoriesBox_->addItem("Все", QVariant("Показать все заметки"));
	notesCategoriesBox_->addItem("Свои", QVariant("Показать только свои заметки"));
	notesCategoriesBox_->addItem("Групповые", QVariant("Показать только групповые заметки"));
	notesCategoriesBox_->setMaxVisibleItems(5);
	notesCategoriesBox_->setCurrentIndex(0);

	allNotesList_.reset(new QListWidget(0));
	allNotesList_->setObjectName("allNotesList");

	newNotesListItem_.reset(new QListWidgetItem(tr("+"), allNotesList_.get()));
	//newNotesListItem_->setSizeHint(QSize(100, 50));
	newNotesListItem_->setTextAlignment(Qt::AlignCenter);
	newNotesListItem_->setWhatsThis("newNotesListItem_");
}

void MainInterface::placeAllNotesSection() const {

	displayedNotesLimitersLayout_->addWidget(notesSortsBox_.get());
	displayedNotesLimitersLayout_->addWidget(notesCategoriesBox_.get());

	allNotesSectionLayout_->addLayout(displayedNotesLimitersLayout_.get(), 0, 0);
	allNotesSectionLayout_->addWidget(allNotesList_.get(), 1, 0);
}

void MainInterface::createCurrentNoteSection() {

	hideCurrentNoteSectionButton_.reset(new QPushButton(tr("<")));
	hideCurrentNoteSectionButton_->setObjectName("hideCurrentNoteSectionButton");

	currentNoteSectionLayout_.reset(new QGridLayout());

	currentNoteTopPanelLayout_.reset(new QGridLayout());

	currentNoteNameEdit_.reset(new QLineEdit());
	currentNoteNameEdit_->setPlaceholderText("Set name");
	currentNoteNameEdit_->setMaximumWidth(200);

	currentNoteOptionsLayout_.reset(new QHBoxLayout());
	currentNoteOptionsLayout_->setMargin(0);
	currentNoteOptionsLayout_->setSpacing(40);

	chooseCurrentNoteCategoryBox_.reset(new QComboBox());
	chooseCurrentNoteCategoryBox_->hide();
	chooseCurrentNoteCategoryBox_->addItem("Без категории", QVariant("Нет категории"));
	chooseCurrentNoteCategoryBox_->setCurrentIndex(0);
	//исправить язык на англ
	chooseCurrentNoteVersionBox_.reset(new QComboBox());
	chooseCurrentNoteVersionBox_->hide();
	chooseCurrentNoteVersionBox_->addItem("Текущая версия", QVariant("Current"));
	chooseCurrentNoteVersionBox_->setCurrentIndex(0);
	//исправить язык на англ
	chooseCurrentNoteCategoryButton_.reset(new QPushButton());
	chooseCurrentNoteCategoryButton_->setToolTip("Присвоить текущей заметки определённую категорию");
	chooseCurrentNoteCategoryButton_->setIcon(QIcon(":/images/images/select_category.png"));
	chooseCurrentNoteCategoryButton_->setIconSize(QSize(38, 38));
	//исправить язык на англ
	chooseCurrentNoteVersionsButton_.reset(new QPushButton());
	chooseCurrentNoteVersionsButton_->setToolTip("Просмотреть предыдущие версии текущей заметки");
	chooseCurrentNoteVersionsButton_->setIcon(QIcon(":/images/images/version.png"));
	chooseCurrentNoteVersionsButton_->setIconSize(QSize(38, 38));
	//исправить язык на англ
	deleteCurrentNoteButton_.reset(new QPushButton());
	deleteCurrentNoteButton_->setToolTip("Удалить текущую заметку");
	deleteCurrentNoteButton_->setIcon(QIcon(":/images/images/delete.png"));
	deleteCurrentNoteButton_->setIconSize(QSize(38, 38));

	//choose_current_note_category_label->setObjectName("choose_current_note_category_label");
	//current_note_versions_label->setObjectName("current_note_versions_label");
	//delete_current_note_label->setObjectName("delete_current_note_label");

	
	//currentNoteField_.reset(new QWebEngineView());
	//currentNoteField_->page()->profile()->clearHttpCache();
	//currentNoteField_->load(QUrl("http://localhost:8080/"));
	//currentNoteField_->setMinimumWidth(600);

	saveCurrentNoteButton_.reset(new QPushButton(QPushButton::tr("Submit")));
}

void MainInterface::placeCurrentNoteSection() const {

	currentNoteOptionsLayout_->addWidget(chooseCurrentNoteCategoryBox_.get(), 0, Qt::AlignLeft);
	currentNoteOptionsLayout_->addWidget(chooseCurrentNoteVersionBox_.get(), 0, Qt::AlignLeft);
	currentNoteOptionsLayout_->addWidget(chooseCurrentNoteCategoryButton_.get(), 0, Qt::AlignRight);
	currentNoteOptionsLayout_->addWidget(chooseCurrentNoteVersionsButton_.get(), 0, Qt::AlignRight);
	currentNoteOptionsLayout_->addWidget(deleteCurrentNoteButton_.get(), 0, Qt::AlignRight);

	currentNoteTopPanelLayout_->addWidget(currentNoteNameEdit_.get(), 0, 0, Qt::AlignLeft);
	currentNoteTopPanelLayout_->addLayout(currentNoteOptionsLayout_.get(), 0, 1, Qt::AlignRight);

	currentNoteSectionLayout_->addLayout(currentNoteTopPanelLayout_.get(), 0, 0);
	currentNoteSectionLayout_->addWidget(currentNoteField_.get(), 1, 0);
	currentNoteSectionLayout_->addWidget(saveCurrentNoteButton_.get(), 2, 0, Qt::AlignRight);
}

void MainInterface::setAttributeToAllWidgets(const Qt::WidgetAttribute&& attribute) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setAttribute(attribute);
	}
}

void MainInterface::setSizePolicyToAllWidgets(const QSizePolicy::Policy&& horizontal,
	const QSizePolicy::Policy&& vertical) const {

	auto&& interfaceWidgetsList = this->children();
	for (auto&& widget : interfaceWidgetsList) {
		if (widget->isWidgetType())
			qobject_cast<QWidget*>(widget)->setSizePolicy(QSizePolicy(horizontal, vertical));
	}
}

void MainInterface::showDefaultCurrentNoteSection(){

    /*current_note_name_edit->show();
    choose_current_note_category_label->show();
    current_note_versions_label->show();
    delete_current_note_label->show();
    note_field->show();
    submit_current_note_button->show();*/

}

void MainInterface::hideDefaultCurrentNoteSection(){

   /* current_note_name_edit->hide();
    choose_current_note_category_box->hide();
    choose_current_note_version_box->hide();
    choose_current_note_category_label->hide();
    current_note_versions_label->hide();
    delete_current_note_label->hide();
    note_field->hide();
    submit_current_note_button->hide();*/

	// Исправить баг с изменением разрешения окна после закрытия
	// поля заметки
    //window->adjustSize();
    //window->adjustSize();

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

    //all_notes_list->insertItem(row_counter, item);

}
/*
QPushButton* MainInterface::getSubmitButton(){
    return submit_current_note_button.get();
}

QWebEngineView* MainInterface::getWebPage(){
    return note_field.get();
}

QComboBox* MainInterface::getCategoryBox(){
    return choose_current_note_category_box.get();
}

QComboBox* MainInterface::getAllCategoriesBox(){
    return note_categories_box.get();
}

QComboBox* MainInterface::getVersionsBox(){
    return choose_current_note_version_box.get();
}

QLineEdit* MainInterface::getNameEdit(){
    return current_note_name_edit.get();
}

QPushButton* MainInterface::getPersonalSettingsButton(){
    return personalSettingsButton_.get();
}
*/
/*
void MainInterface::createDefaultPersonalInfo(EventHandlers* event_handlers){

    personal_info.reset(new PersonalInfo(event_handlers));

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

}*/


/*PersonalInfoPanel* MainInterface::getPersonalInterface(){
    return this->personal_info.get();
}*/
/*
void MainInterface::createDefaultCustomization(EventHandlers* event_handlers){

    customization.reset(new Customization(event_handlers));

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
*/
/*
Customization* MainInterface::getCustomizationInterface(){
    return this->customization.get();
}*/
/*
void MainInterface::createDefaultGroup(EventHandlers* event_handlers){

    group.reset(new Group(event_handlers));

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
*/

void MainInterface::show() {

	if (this->isHidden())
		QWidget::show();
}

void MainInterface::hide() {

	if (!this->isHidden())
		QWidget::hide();
}

void MainInterface::resize(const int& width, const int& height) {

	QWidget::resize(width, height);
}

void MainInterface::resize(const int&& width, const int&& height) {

	QWidget::resize(width, height);
}

void MainInterface::paintEvent(QPaintEvent*) {

	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
