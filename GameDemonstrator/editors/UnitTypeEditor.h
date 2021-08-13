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
	void SlotSelectedMapHexItem(int mapHexItemId);
private:
	/** */
	void CreateNewUnit();
	/** */
	void DeleteUnit();
private:
	int					SelectedGameMapItem;
	ModelUnitType		*ActiveUnitType;
	MapHexItemEventManager		*MapEventManagerInstance;
};

#endif // UNITTYPEEDITR_H
