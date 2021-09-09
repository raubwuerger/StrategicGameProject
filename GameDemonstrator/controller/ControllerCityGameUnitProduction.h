#ifndef CITYGAMEUNITPRODUCTIONCONTROLLER_H
#define CITYGAMEUNITPRODUCTIONCONTROLLER_H

class ControllerCityGameUnitProduction : public QObject
{
	Q_OBJECT
public:
public slots:
	/** */
	void SlotProduceUnit( int unitTypeId );
};

#endif // CITYGAMEUNITPRODUCTIONCONTROLLER_H