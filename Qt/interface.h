#ifndef INTEFRACE_H
#define INTEFRACE_H

#include "eventhandlers.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <QGraphicsDropShadowEffect>


class Interface{
public:
	virtual ~Interface() = default;
	virtual void createInterface(const EventHandlers* eventHandlers) = 0;
	virtual void createInterfaceElements() = 0;
	virtual void placeInterfaceElements() const = 0;
	virtual void setAttributeToAllWidgets(const Qt::WidgetAttribute&& attribute) const = 0;
	virtual void setSizePolicyToAllWidgets(const QSizePolicy::Policy&& horizontal,
		const QSizePolicy::Policy&& vertical) const = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void resize(const int& width, const int& height) = 0;
	virtual void resize(const int&& width, const int&& height) = 0;
};

#endif // INTEFRACE_H
