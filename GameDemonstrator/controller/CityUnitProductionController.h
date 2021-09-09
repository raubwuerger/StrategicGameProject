#ifndef CITYGAMEUNITPRODUCTIONCONTROLLER_H
#define CITYGAMEUNITPRODUCTIONCONTROLLER_H

class CityUnitProductionController : public QObject
{
	Q_OBJECT
public:
public slots:
	/** */
	void SlotProduceUnit( int unitTypeId );
};

#endif // CITYGAMEUNITPRODUCTIONCONTROLLER_H