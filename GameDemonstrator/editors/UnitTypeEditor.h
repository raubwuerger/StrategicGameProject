#ifndef UNITTYPEEDITR_H
#define UNITTYPEEDITR_H

#include <QObject>
class ModelUnitType;
class MapHexItemEventManager;

class UnitTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	UnitTypeEditor(QObject *parent);
	/** */
	~UnitTypeEditor();
	/** */
	void SetMapEventManager(MapHexItemEventManager* mapEventManager);
public slots:
	/** */
	void SlotActiveUnitTypeId(int unitTypeId);
	/** */
	void SlotAddUnit(int mapHexItemId);
	/** */
	void SlotDeleteUnit(int mapHexItemId);
private:
	/** */
	void CreateUnit();
	/** */
	void DeleteUnit();
	/** */
	bool HasMapHexItemUnits();
private:
	int						SelectedGameMapItem;
	const ModelUnitType		*ActiveUnitType;
	MapHexItemEventManager	*MapEventManagerInstance;
};

#endif // UNITTYPEEDITR_H
