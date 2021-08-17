#ifndef UNITTYPEEDITR_H
#define UNITTYPEEDITR_H

#include "BaseEditor.h"
class ModelUnitType;
class MapView;
class EditorController;

class UnitTypeEditor : public BaseEditor
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
	void SlotActiveOwnerTypeId(int ownerTypeId);
	/** */
	void SlotAddUnit(int mapHexItemId);
	/** */
	void SlotDeleteUnitFromMapHexItemId(int mapHexItemId);
	/** */
	void SlotDeleteUnitFromGameUnitId(int gameUnitId);
	/** */
	virtual void SlotActivated();
private:
	/** */
	void CreateUnit();
	/** */
	void DeleteUnit( int gameMapItemId );
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
	const int				VALUE_NOT_INITIALIZED;
	int						ActiveGameMapItemId;
	int						ActiveGameOwnerItemId;
	const ModelUnitType*	ActiveUnitType;
	MapView*				MapViewInstance;
	EditorController*		EditorControllerInstance;
};

#endif // UNITTYPEEDITR_H
