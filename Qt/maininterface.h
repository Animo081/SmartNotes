#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "interface.h"
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QPixmap>
#include <QListWidget>
#include <QFont>
#include <QComboBox>
#include <QTextEdit>
#include <QColorDialog>

struct PersonalInfo{
    PersonalInfo(EventHandlers* event_handlers) { this->event_handler = event_handlers; }
    ~PersonalInfo();

    EventHandlers* event_handler;

    QWidget* personal_info_window;

    QGridLayout* personal_section_layout;

    QGridLayout* personal_section_top_layout;

    QGridLayout* personal_section_edits_layout;
    QLabel* user_photo_label;
    QLabel* first_name_label;
    QLabel* last_name_label;
    QLabel* phone_number_label;
    QLabel* email_label;

    QLineEdit* first_name_edit;
    QLineEdit* last_name_edit;
    QLineEdit* phone_number_edit;
    QLineEdit* email_edit;

    QLabel* description_label;
    QTextEdit* description_edit;

    QVBoxLayout* button_controls_layout;
    QPushButton* ok_button;
    QPushButton* cancel_button;
};

struct Customization{
    Customization(EventHandlers* event_handlers) { this->event_handler = event_handlers; }
    ~Customization();

    EventHandlers* event_handler;

    QWidget* customization_window;

    QGridLayout* customization_section_layout;

    QGridLayout* not_description_layout;

    QLabel* choose_category_label;
    QComboBox* choose_category_box;

    QLabel* category_name_label;
    QLineEdit* category_name_edit;

    QGridLayout* color_picker_layout;

    QLabel* text_color_label;
    QLabel* text_color_show_label;

    QLabel* background_color_label;
    QLabel* background_color_show_label;

    QLabel* item_customization_label;

    QLabel* note_back_label;
    QLabel* note_back_image;

    QLabel* description_label;
    QTextEdit* description_edit;

    QHBoxLayout* controls_layout;

    QPushButton* save_button;
    QPushButton* cancel_button;
    QPushButton* delete_button;

    QColorDialog* color_dialog;

};

struct Group{
    Group(EventHandlers* event_handlers) { this->event_handler = event_handlers; }
    ~Group();

    QWidget* group_window;

    QLabel* my_groups_label;
    QLabel* new_group_label;
    QLabel* members_label;
    QLabel* invite_label;
    QLabel* notes_label;

    QPushButton* cancel_button;
    QPushButton* create_group_button;
    QPushButton* invite_button;
    QPushButton* share_button;

    QLineEdit* look_for_users_edit;
    QLineEdit* new_group_edit;
    QCompleter* users;
    QComboBox* my_groups_box;
    QComboBox* group_members_box;
    QComboBox* note_for_share_box;

    QHBoxLayout* create_layout;
    QHBoxLayout* invite_layout;
    QGridLayout* share_layout;

    QGridLayout* group_section_layout;

    EventHandlers* event_handler;
};

class MainInterface: public Interface, public QMainWindow{
public:
    MainInterface(QWidget*,EventHandlers*);
    virtual ~MainInterface();
	virtual void createInterface(EventHandlers* eventHandlers) override;
	virtual void createInterfaceElements() override;
	virtual void placeInterfaceElements() override;
	virtual void setAttributeToAllWidgets(const Qt::WidgetAttribute&&) override;
	virtual void setSizePolicyToAllWidgets(const QSizePolicy::Policy&&,
		const QSizePolicy::Policy&&) override;

    QGridLayout* createDefaultUserSection();
    QGridLayout* createDefaultAllNotesSection();
    QGridLayout* createDefaultCurrentNoteSection();
    void showDefaultCurrentNoteSection();
    void hideDefaultCurrentNoteSection();

    QSize getWindowDefaultSize();
    void addNewRowInNotesList(const int&, QString, QString, QString, QString);
    QPushButton* getSubmitButton();
    QWebEngineView* getWebPage();
    QComboBox* getCategoryBox();
    QComboBox* getAllCategoriesBox();
    QComboBox* getVersionsBox();
    QLineEdit* getNameEdit();
    QLabel* getPersonalSettingsLabel();

    void createDefaultPersonalInfo(EventHandlers*);
    PersonalInfo* getPersonalInterface();

    void createDefaultCustomization(EventHandlers*);
    Customization* getCustomizationInterface();

    void createDefaultGroup(EventHandlers*);
    Group* getGroupInterface();
private:
    QWidget* window;
    QSize window_size;

    QGridLayout* main_layout;

    QGridLayout* user_section_layout;
    QVBoxLayout* user_facilities_layout;
    QLabel* personal_settings_label;
    QLabel* categories_settings_label;
    QLabel* group_manager_label;
    QLabel* app_settings_label;
    QLabel* sign_out_label;

    QGridLayout* all_notes_section_layout;
    QListWidget *all_notes_list;
    QListWidgetItem* new_note_row_item;
    QComboBox* notes_sort_box;
    QComboBox* note_categories_box;
    QHBoxLayout* notes_sort_layout;
    QPushButton* hideCurrentNoteSection;

    QGridLayout* current_note_section_layout;
    QGridLayout* current_note_panel_layout;
    QLineEdit* current_note_name_edit;
    QHBoxLayout* current_note_options_layout;
    QComboBox* choose_current_note_category_box;
    QComboBox* choose_current_note_version_box;
    QLabel* choose_current_note_category_label;
    QLabel* current_note_versions_label;
    QLabel* delete_current_note_label;
    QWebEngineView* note_field;
    QPushButton* submit_current_note_button;

    QErrorMessage* warningMessage;

    PersonalInfo* personal_info;

    Customization* customization;

    Group* group;
};

#endif // MAININTERFACE_H
