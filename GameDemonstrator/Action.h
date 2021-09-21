#ifndef ACTION_H
#define ACTION_H

#include <qaction>

class Action : public QAction
{
public:
/** */
	Action(QObject* parent);
/** */
	Action(const QString &text, QObject* parent);
/** */
	Action(const QIcon &icon, const QString &text, QObject* parent);
/** */
	virtual ~Action();
/** */
public slots:
	virtual void triggered( bool checked = false );
	virtual void hovered();
};

#endif // ACTION_H