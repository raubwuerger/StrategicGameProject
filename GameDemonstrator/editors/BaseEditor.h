#ifndef BASEEDITOR_H
#define BASEEDITOR_H

class BaseEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	BaseEditor(QObject *parent);
public slots:
	/** */
	virtual void SlotActivated() = 0;
};

#endif // BASEEDITOR_H