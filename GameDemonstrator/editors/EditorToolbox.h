#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

//================================================================================
#include <QToolBox>
class UnitTypeIdSelector;
class UnitTypeEditor;
class TerrainTypeIdSelector;
class TerrainTypeEditor;
class ModelTerrainType;
class ModelUnitType;
class ModelTerrainTypeRepository;
class ConnectorMapHexItem;
class ConnectorUnitTypeGameMap;
class MapHexItemEventManager;
class ConnectorMapUnitItem;
class MapView;
class EditorController;
class BaseEditor;
class ModelOwnerType;
class OwnerTypeIdSelector;
class OwnerTypeEditor;
class ModelCityType;
class CityTypeIdSelector;
class CityTypeEditor;

class EditorToolbox : public QToolBox
{
	Q_OBJECT
public:
	/** */
	EditorToolbox(QWidget *parent);
	/** */
	~EditorToolbox();
	/** Erzeugt die Toolboxeinträge */
	void Create();
public slots:
	/** */
	void SlotEditorTypeChanged(int editorIndex);
private:
	/** */
	void CreateGroupTerrainTypes();
	/** */
	QWidget* CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup);
	/** */
	QWidget* CreateReleaseTerrainTypeWidget(QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector);
	/** */
	BaseEditor* CreateTerrainTypeEditor();
	/** */
	void CreateGroupUnitTypes();
	/** */
	QWidget *CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector);
	/** */
	BaseEditor* CreateUnitTypeEditor();
	/** */
	void CreateGroupOwnerType();
	/** */
	QWidget *CreateOwnerTypeWidget(const ModelOwnerType* modelCityType, QButtonGroup* buttonGroup, OwnerTypeIdSelector *selector);
	/** */
	BaseEditor* CreateOwnerTypeEditor();
	/** */
	void CreateGroupCityType();
	/** */
	QWidget *CreateCityTypeWidget(const ModelCityType* modelCityType, QButtonGroup* buttonGroup, CityTypeIdSelector *selector);
	/** */
	BaseEditor* CreateCityTypeEditor();
	/** */
	void CreateGroupBuildingTypes();
private:
	friend class GameModeEditor;
	int								MinimumEditWidth;	//Has been: itemTerrainType->sizeHint().width()
	QButtonGroup*					GroupTerrainTypes;
	QButtonGroup*					GroupBuildings;
	QButtonGroup*					GroupUnitsTypes;
	QButtonGroup*					GroupOwnerTypes;
	QButtonGroup*					GroupCityTypes;
	TerrainTypeEditor*				TerrainTypeEditorInstance;
	UnitTypeEditor*					UnitTypeEditorInstance;
	OwnerTypeEditor*				OwnerTypeEditorInstance;
	CityTypeEditor*					CityTypeEditorInstance;
	ConnectorUnitTypeGameMap*		ConnectorUnitTypeEditorGameMapInstance;
	ConnectorMapUnitItem*			ConnectorMapUnitItemInstance;
	MapView*						MapViewInstance;
	EditorController*				EditorControllerInstance;
	QMap<int, BaseEditor*>			EditorMap;

};

#endif // CEDITORTOOLBOX_H
