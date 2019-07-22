#ifndef GUI_H
#define GUI_H

#include <variant>
#include <QWidget>
#include <QMainWindow>
#include "interface.h"
#include "eventhandlers.h"

class Network;

class Tools {
public:
	Tools();
	void setAttributeToQWidgets(const Qt::WidgetAttribute&& attribute,
		std::initializer_list<QWidget*> list);
	void setSizePolicyToQWidgets(const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical, 
		std::initializer_list<QWidget*> list);
	void showMessage(const QString& message);
	void showMessage(const QString&& message);

	QStringList getImagesFromDir(const QString& dir);
	QString getRandomImage(const QStringList& images);
	QString getDefaultUsernameAndPassRegex();
	QString getDefaultEmailRegex();
private:
	QScopedPointer<QErrorMessage> message_;

	QString defaultUsernameAndPassRegex_;
	QString defaultEmailRegex_;
};

class Gui: public QWidget{
	Q_OBJECT
public:
    Gui(QWidget* parent = nullptr);
	~Gui();
    void startInitialization(std::shared_ptr<Gui>& gui, 
		std::shared_ptr<Network>& network);
	void setWindowSettings();
	void setBackgroundImage(const QString& imageDir, 
		const QString& imageName);
    void createLogInInterface();
	void createRegisterInterface();
    void createMainInterface();
	virtual void destroyInterface(Interface*);
	virtual void destroyCurrentInterface();
    void startMainProgram();
    void finishMainProgram();

	void resizeEvent(QResizeEvent* event) override;

	Tools* getTools();
private:
	std::unique_ptr<EventHandlers> eventHandlers_;

	std::shared_ptr<Tools> tools_;

	std::shared_ptr<Interface> currentInterface_;

    std::shared_ptr<Interface> logInInterface_;
    std::shared_ptr<Interface> registerInterface_;
    std::shared_ptr<Interface> mainInterface_;

	QString backgoundImagesDefaultDir_;
	QPixmap backgroundImagePixmap_;
};

#endif // GUI_H
