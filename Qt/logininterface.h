#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "interface.h"

class Tools;

class LogInInterface: public QWidget, public Interface {
	Q_OBJECT
public:
    LogInInterface(std::shared_ptr<Tools> tools, QWidget* parent = nullptr);
    virtual ~LogInInterface();
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

	QString getUsernameEditText() const;
	QString getPasswordEditText() const;
	const QPushButton* getSignInButton() const;
	const QPushButton* getSignUpButton() const;
private:
    QScopedPointer<QGridLayout> loginInterfaceLayout_;

	QScopedPointer<QGridLayout> mainPartLayout_;

    QScopedPointer<QLabel> usernameLabel_;
    QScopedPointer<QLabel> passwordLabel_;

	QScopedPointer<QGraphicsDropShadowEffect> usernameLabelEffect_;
	QScopedPointer<QGraphicsDropShadowEffect> passwordLabelEffect_;

    QScopedPointer<QLineEdit> usernameEdit_;
    QScopedPointer<QLineEdit> passwordEdit_;

    QScopedPointer<QCheckBox> savePasswordCheckBox_;

    QScopedPointer<QDialogButtonBox> buttonBox_;

    QScopedPointer<QPushButton> signInButton_;
    QScopedPointer<QPushButton> signUpButton_;

	std::shared_ptr<Tools> tools_;
};

#endif // LOGININTERFACE_H
