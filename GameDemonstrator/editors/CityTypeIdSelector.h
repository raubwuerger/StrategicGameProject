#ifndef CITYTYPEIDSELECTOR_H
#define CITYTYPEIDSELECTOR_H

class CityTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	CityTypeIdSelector(int CityTypeId);
public slots:
	/** */
	void SlotTrigger();
signals:
	/** */
	void SignalCityTypeActive(int CityTypeId);
private:
	int CityTypeId;
};

#endif // CITYTYPEIDSELECTOR_H