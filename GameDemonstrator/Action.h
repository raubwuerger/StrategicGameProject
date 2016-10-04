#pragma once
#include <qaction>

class CAction : public QAction
{
public:
/** */
	CAction(QObject* parent);
/** */
	CAction(const QString &text, QObject* parent);
/** */
	CAction(const QIcon &icon, const QString &text, QObject* parent);
/** */
	virtual ~CAction();
/** */
public slots:
	virtual void triggered( bool checked = false );
	virtual void hovered();
};

