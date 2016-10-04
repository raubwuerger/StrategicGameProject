#include "stdafx.h"
#include "Action.h"

CAction::CAction(QObject* parent)
	: QAction(parent)
{

}

CAction::CAction(const QString &text, QObject* parent)
	: QAction(text,parent)
{

}

CAction::CAction(const QIcon &icon, const QString &text, QObject* parent)
	: QAction( icon, text, parent )
{
}

CAction::~CAction()
{
}

void CAction::triggered( bool checked /*= false */ )
{
	emit triggered(checked);
}

void CAction::hovered()
{
	emit hovered();
}
