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

class Tools;

class MainInterface: public QWidget, public Interface {
	Q_OBJECT
public:
    MainInterface(std::shared_ptr<Tools> tools, QWidget* parent = nullptr);
	virtual ~MainInterface();
	virtual void createInterface(const EventHandlers* eventHandlers) override;
	virtual void createInterfaceElements() override;
	virtual void placeInterfaceElements() const override;

	void createUserSection();
	void placeUserSection() const;

	void createAllNotesSection();
	void placeAllNotesSection() const;

	void createCurrentNoteSection();
	void placeCurrentNoteSection() const;

	virtual void setAttributeToAllWidgets(
		const Qt::WidgetAttribute&& attribute) const override;
	virtual void setSizePolicyToAllWidgets(
		const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical) const override;

    


    void showDefaultCurrentNoteSection();
    void hideDefaultCurrentNoteSection();

    QSize getWindowDefaultSize();
    void addNewRowInNotesList(const int&, QString, QString, QString, QString);
    /*QPushButton* getSubmitButton();
    QWebEngineView* getWebPage();
    QComboBox* getCategoryBox();
    QComboBox* getAllCategoriesBox();
    QComboBox* getVersionsBox();
    QLineEdit* getNameEdit();
    QPushButton* getPersonalSettingsButton();*/

    //void createDefaultPersonalInfo(EventHandlers*);
    //PersonalInfo* getPersonalInterface();

    //void createDefaultCustomization(EventHandlers*);
    //Customization* getCustomizationInterface();

    //void createDefaultGroup(EventHandlers*);

	virtual void show() override;
	virtual void hide() override;
	virtual void resize(const int& width, const int& height) override;
	virtual void resize(const int&& width, const int&& height) override;

	void paintEvent(QPaintEvent* event) override;
private:
	QScopedPointer<QGridLayout> mainInterfaceLayout_;

	//User section

	QScopedPointer<QGridLayout> userSectionLayout_;

    QScopedPointer<QPushButton> personalSettingsButton_;

	QScopedPointer<QVBoxLayout> userFacilitiesLayout_;

	QScopedPointer<QPushButton> customizationButton_;
	QScopedPointer<QPushButton> groupsManagerButton_;
	QScopedPointer<QPushButton> appSettingsButton_;
	QScopedPointer<QPushButton> signOutButton_;

	//
	//All notes section

    QScopedPointer<QGridLayout> allNotesSectionLayout_;

	QScopedPointer<QHBoxLayout> displayedNotesLimitersLayout_;

	QScopedPointer<QComboBox> notesSortsBox_;
	QScopedPointer<QComboBox> notesCategoriesBox_;

    QScopedPointer<QListWidget> allNotesList_;
	QScopedPointer<QListWidgetItem> newNotesListItem_;

	//
	//Current note section

	QScopedPointer<QPushButton> hideCurrentNoteSectionButton_;

	QScopedPointer<QGridLayout> currentNoteSectionLayout_;

	QScopedPointer<QGridLayout> currentNoteTopPanelLayout_;

	QScopedPointer<QLineEdit> currentNoteNameEdit_;

	QScopedPointer<QHBoxLayout> currentNoteOptionsLayout_;

	QScopedPointer<QComboBox> chooseCurrentNoteCategoryBox_;
	QScopedPointer<QComboBox> chooseCurrentNoteVersionBox_;

	QScopedPointer<QPushButton> chooseCurrentNoteCategoryButton_;
	QScopedPointer<QPushButton> chooseCurrentNoteVersionsButton_;
	QScopedPointer<QPushButton> deleteCurrentNoteButton_;

	QScopedPointer<QWebEngineView> currentNoteField_;

	QScopedPointer<QPushButton> saveCurrentNoteButton_;

	//

	std::shared_ptr<Tools> tools_;

	struct PersonalInfoPanel: public QWidget { 
		PersonalInfoPanel(EventHandlers* event_handlers);
		//~PersonalInfoPanel();

		QScopedPointer<QGridLayout> personal_section_layout;

		QScopedPointer<QGridLayout> personal_section_top_layout;

		QScopedPointer<QGridLayout> personal_section_edits_layout;
		QScopedPointer<QLabel> user_photo_label;
		QScopedPointer<QLabel> first_name_label;
		QScopedPointer<QLabel> last_name_label;
		QScopedPointer<QLabel> phone_number_label;
		QScopedPointer<QLabel> email_label;

		QScopedPointer<QLineEdit> first_name_edit;
		QScopedPointer<QLineEdit> last_name_edit;
		QScopedPointer<QLineEdit> phone_number_edit;
		QScopedPointer<QLineEdit> email_edit;

		QScopedPointer<QLabel> description_label;
		QScopedPointer<QTextEdit> description_edit;

		QScopedPointer<QVBoxLayout> button_controls_layout;
		QScopedPointer<QPushButton> ok_button;
		QScopedPointer<QPushButton> cancel_button;
	};

	QScopedPointer<PersonalInfoPanel> personalInfoPanel_;

	struct CustomizationPanel: public QWidget {
		CustomizationPanel(EventHandlers* event_handlers);
		//~CustomizationPanel();

		QScopedPointer<QGridLayout> customization_section_layout;

		QScopedPointer<QGridLayout> not_description_layout;

		QScopedPointer<QLabel> choose_category_label;
		QScopedPointer<QComboBox> choose_category_box;

		QScopedPointer<QLabel> category_name_label;
		QScopedPointer<QLineEdit> category_name_edit;

		QScopedPointer<QGridLayout> color_picker_layout;

		QScopedPointer<QLabel> text_color_label;
		QScopedPointer<QLabel> text_color_show_label;

		QScopedPointer<QLabel> background_color_label;
		QScopedPointer<QLabel> background_color_show_label;

		QScopedPointer<QLabel> item_customization_label;

		QScopedPointer<QLabel> note_back_label;
		QScopedPointer<QLabel> note_back_image;

		QScopedPointer<QLabel> description_label;
		QScopedPointer<QTextEdit> description_edit;

		QScopedPointer<QHBoxLayout> controls_layout;

		QScopedPointer<QPushButton> save_button;
		QScopedPointer<QPushButton> cancel_button;
		QScopedPointer<QPushButton> delete_button;

		QScopedPointer<QColorDialog> color_dialog;

	};

	QScopedPointer<CustomizationPanel> customizationPanel_;

	struct GroupsPanel: public QWidget {
		GroupsPanel(EventHandlers* event_handlers);
		//~GroupsPanel();

		QScopedPointer<QLabel> my_groups_label;
		QScopedPointer<QLabel> new_group_label;
		QScopedPointer<QLabel> members_label;
		QScopedPointer<QLabel> invite_label;
		QScopedPointer<QLabel> notes_label;

		QScopedPointer<QPushButton> cancel_button;
		QScopedPointer<QPushButton> create_group_button;
		QScopedPointer<QPushButton> invite_button;
		QScopedPointer<QPushButton> share_button;

		QScopedPointer<QLineEdit> look_for_users_edit;
		QScopedPointer<QLineEdit> new_group_edit;
		QScopedPointer<QCompleter> users;
		QScopedPointer<QComboBox> my_groups_box;
		QScopedPointer<QComboBox> group_members_box;
		QScopedPointer<QComboBox> note_for_share_box;

		QScopedPointer<QHBoxLayout> create_layout;
		QScopedPointer<QHBoxLayout> invite_layout;
		QScopedPointer<QGridLayout> share_layout;

		QScopedPointer<QGridLayout> group_section_layout;
	};

	QScopedPointer<GroupsPanel> groupsPanel_;
};

#endif // MAININTERFACE_H
