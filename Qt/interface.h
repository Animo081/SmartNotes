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


class Interface{
public:
	virtual ~Interface() = default;
	virtual void createInterface(EventHandlers*) = 0;
	virtual void createInterfaceElements() = 0;
	virtual void placeInterfaceElements() = 0;
	virtual void setAttributeToAllWidgets(const Qt::WidgetAttribute&&) = 0;
	virtual void setSizePolicyToAllWidgets(const QSizePolicy::Policy&&,
		const QSizePolicy::Policy&&) = 0;
};

#endif // INTEFRACE_H
