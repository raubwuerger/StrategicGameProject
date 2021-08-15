#ifndef UNITTYPEEDITR_H
#define UNITTYPEEDITR_H

#include <QObject>
class ModelUnitType;
class MapView;
class EditorController;

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
	/** */
	void SetEditorController(EditorController* editorController);
public slots:
	/** */
	void SlotActiveUnitTypeId(int unitTypeId);
	/** */
	void SlotAddUnit(int mapHexItemId);
	/** */
	void SlotDeleteUnit(int mapHexItemId);
	/** */
	void SlotActivated();
private:
	/** */
	void CreateUnit();
	/** */
	void DeleteUnit();
	/** */
	bool HasMapHexItemUnits() const;
	/** */
	bool IsSelectedGameMapItemInitialized() const;
	/** */
	bool IsUnitTypeEditorInitialzed() const;
	/** */
	bool IsUnitTypeEditorInitialzedForCreatingUnit() const;
	/** */
	bool IsUnitTypeEditorInitialzedForDeletingUnit() const;
private:
	const int				NO_UNITS;
	const int				MAX_UNITS;
	const int				SELECTEDGAMEMAPITEM_NOT_INITIALIZED;
	int						SelectedGameMapItem;
	const ModelUnitType*	ActiveUnitType;
	MapView*				MapViewInstance;
	EditorController*		EditorControllerInstance;
};

#endif // UNITTYPEEDITR_H
