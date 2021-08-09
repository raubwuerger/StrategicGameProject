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
void Trigger();
signals:
	/** */
	void UnitTypeActive(int unitTypeId);
private:
	int UnitTypeId;
};

#endif //UNITTYPEIDSELECTOR_H
