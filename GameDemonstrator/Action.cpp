#include "stdafx.h"
#include "Action.h"

Action::Action(QObject* parent)
	: QAction(parent)
{

}

Action::Action(const QString &text, QObject* parent)
	: QAction(text,parent)
{

}

Action::Action(const QIcon &icon, const QString &text, QObject* parent)
	: QAction( icon, text, parent )
{
}

Action::~Action()
{
}

void Action::triggered( bool checked /*= false */ )
{
	emit triggered(checked);
}

void Action::hovered()
{
	emit hovered();
}
