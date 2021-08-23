#ifndef BASEEDITOR_H
#define BASEEDITOR_H

class BaseEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	BaseEditor(QObject *parent);
	/** */
	void SetActive(bool active);
	/** */
	bool GetActive() const;
public slots:
	/** */
	virtual void SlotActivated() = 0;
	/** */
	virtual void SlotDeactivated() = 0;
private:
	bool Active;
};

#endif // BASEEDITOR_H