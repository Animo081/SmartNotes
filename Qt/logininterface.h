#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "interface.h"

class Tools;

class LogInInterface: public QWidget, public Interface {
	Q_OBJECT
public:
    LogInInterface(std::shared_ptr<Tools> tools, QWidget* parent = nullptr);
    virtual ~LogInInterface();
	virtual void createInterface(EventHandlers* eventHandlers) override;
	virtual void createInterfaceElements() override;
	virtual void placeInterfaceElements() override;
	virtual void setAttributeToAllWidgets(
		const Qt::WidgetAttribute&& attribute) override;
	virtual void setSizePolicyToAllWidgets(
		const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical) override;

	QString getUsernameEditText();
	QString getPasswordEditText();
	QPushButton* getSignInButton();
	QPushButton* getSignUpButton();
private:
    QScopedPointer<QGridLayout> loginInterfaceLayout_;

	QScopedPointer<QGridLayout> mainPartLayout_;

    QScopedPointer<QLabel> usernameLabel_;
    QScopedPointer<QLabel> passwordLabel_;

    QScopedPointer<QLineEdit> usernameEdit_;
    QScopedPointer<QLineEdit> passwordEdit_;

    QScopedPointer<QCheckBox> savePasswordCheckBox_;

    QScopedPointer<QDialogButtonBox> buttonBox_;

    QScopedPointer<QPushButton> signInButton_;
    QScopedPointer<QPushButton> signUpButton_;

	QPixmap backgroundImagePixmap_;

	std::shared_ptr<Tools> tools_;
};

#endif // LOGININTERFACE_H
