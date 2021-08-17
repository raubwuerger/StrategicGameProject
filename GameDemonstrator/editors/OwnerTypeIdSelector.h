#ifndef OWNERTYPEIDSELECTOR_H
#define OWNERTYPEIDSELECTOR_H

class OwnerTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	OwnerTypeIdSelector(int ownerTypeId);
public slots:
	/** */
	void SlotTrigger();
signals:
	/** */
	void SignalOwnerTypeActive(int ownerTypeId);
private:
	int OwnerTypeId;
};

#endif // OWNERTYPEIDSELECTOR_H