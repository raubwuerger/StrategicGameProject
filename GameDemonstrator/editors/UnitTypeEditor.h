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
signals:
	/** */
	void UnitAdded(int mapItemId, int unitTypeId);
private:
	friend class GameDemonstrator;
	ModelUnitType		*ActiveUnitType;
	MapEventManager		*MapEventManager;
};

#endif // UNITTYPEEDITR_H
