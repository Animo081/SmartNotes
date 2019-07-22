#ifndef REGISTERINTERFACE_H
#define REGISTERINTERFACE_H

#include "interface.h"

class Tools;

class RegisterInterface: public QWidget, public Interface{
	Q_OBJECT
public:
    RegisterInterface(std::shared_ptr<Tools> tools, QWidget* parent = nullptr);
    virtual ~RegisterInterface();
	virtual void createInterface(const EventHandlers* eventHandlers) override;
	virtual void createInterfaceElements() override;
	virtual void placeInterfaceElements() const override;
	virtual void setAttributeToAllWidgets(
		const Qt::WidgetAttribute&& attribute) const override;
	virtual void setSizePolicyToAllWidgets(
		const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical) const override;
	virtual void show() override;
	virtual void hide() override;
	virtual void resize(const int& width, const int& height) override;
	virtual void resize(const int&& width, const int&& height) override;

	void paintEvent(QPaintEvent* event) override;

	void setUsernameRegex(const QString&& regex);
	void setUsernameRegex(const QRegExp& regex);
	void setPasswordRegex(const QString&& regex);
	void setPasswordRegex(const QRegExp& regex);
	void setEmailRegex(const QString&& regex);
	void setEmailRegex(const QRegExp& regex);

	QString getUsernameEditText() const;
	QString getPasswordEditText() const;
	QString getRepeatPasswordEditText() const;
	QString getEmailEditText() const;
	const QPushButton* getSubmitRegistrationButton() const;
	const QPushButton* getCancelButton() const;
	const QRegExp& getUsernameRegex() const;
	const QRegExp& getPasswordRegex() const;
	const QRegExp& getEmailRegex() const;
private:
    QScopedPointer<QGridLayout> registerInterfaceLayout_;

	QScopedPointer<QGridLayout> mainPartLayout_;

	QScopedPointer<QGridLayout> informationPartLayout_;

	QScopedPointer<QLabel> usernameLabel_;
	QScopedPointer<QLabel> passwordLabel_;
	QScopedPointer<QLabel> repeatPasswordLabel_;
	QScopedPointer<QLabel> emailLabel_;

	QScopedPointer<QGraphicsDropShadowEffect> usernameLabelEffect_;
	QScopedPointer<QGraphicsDropShadowEffect> passwordLabelEffect_;
	QScopedPointer<QGraphicsDropShadowEffect> repeatPasswordLabelEffect_;
	QScopedPointer<QGraphicsDropShadowEffect> emailLabelEffect_;

	QScopedPointer<QLineEdit> usernameEdit_;
	QScopedPointer<QLineEdit> passwordEdit_;
	QScopedPointer<QLineEdit> repeatPasswordEdit_;
	QScopedPointer<QLineEdit> emailEdit_;

	QRegExp usernameRegex_;
	QRegExp passwordRegex_;
	QRegExp emailRegex_;

	QScopedPointer<QPushButton> submitRegistrationButton_;
	QScopedPointer<QPushButton> cancelRegistrationButton_;

	std::shared_ptr<Tools> tools_;
};

#endif // REGISTERINTERFACE_H
