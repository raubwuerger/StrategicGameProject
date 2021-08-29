#ifndef CITYTYPEEDITOR_H
#define CITYTYPEEDITOR_H

class ModelCityType;
class EditorController;
class MapView;
class ModelTerrainType;
#include "BaseEditor.h"

class CityTypeEditor : public BaseEditor
{
public:
	/** */
	CityTypeEditor(QObject *parent);
public slots:
	/** */
	void SlotActivated() override;
	/** */
	void SlotDeactivated() override;
	/** */
	void SlotActiveCityTypeId(int cityTypeId);
	/** */
	void SlotActiveOwnerTypeId(int ownerTypeId);
	/** */
	void SlotAddCity(int mapItemId);
	/** */
	void SlotDeleteCity(int mapItemId);
private:
	/** */
	int GetModelTerrainType(int mapId);
private:
	friend class EditorToolbox;
	const ModelCityType*	ActiveModelCityType;
	int						OwnerTypeId;
	EditorController*		EditorControllerInstance;
	MapView*				MapViewInstance;
};

#endif // CITYTYPEEDITOR_H