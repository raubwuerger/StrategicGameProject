#ifndef UNITTYPEEDITR_H
#define UNITTYPEEDITR_H

#include <QObject>
class ModelUnitType;
class MapView;

class UnitTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	UnitTypeEditor(QObject *parent);
	/** */
	~UnitTypeEditor();
	/** */
	void SetMapView(MapView* mapView);
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
	const ModelUnitType*	ActiveUnitType;
	MapView*				MapViewInstance;
};

#endif // UNITTYPEEDITR_H
