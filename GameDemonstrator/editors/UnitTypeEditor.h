#ifndef UNITTYPEEDITR_H
#define UNITTYPEEDITR_H

#include <QObject>
class ModelUnitType;
class MapEventManager;

class UnitTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	UnitTypeEditor(QObject *parent);
	/** */
	~UnitTypeEditor();
	/** */
	void SetMapEventManager(MapEventManager* mapEventManager);
signals:
	/** */
	void UnitAdded(int mapItemId, int unitTypeId);
private:
	ModelUnitType		*ActiveUnitType;
	MapEventManager		*MapEventManagerInstance;
};

#endif // UNITTYPEEDITR_H
