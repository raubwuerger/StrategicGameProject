#ifndef UNITTYPEIDSELECTOR_H
#define UNITTYPEIDSELECTOR_H

class UnitTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	UnitTypeIdSelector(int unitTypeId);
public slots:
	/** */
	void SlotTrigger();
signals:
	/** */
	void SignalActiveUnitType(int unitTypeId);
private:
	int UnitTypeId;
};

#endif //UNITTYPEIDSELECTOR_H
