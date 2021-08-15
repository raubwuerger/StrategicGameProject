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
	void SlotButtonGroupChanged(int buttonGroupIndex);
private:
	/** */
	void CreateGroupTerrainTypes();
	/** */
	QWidget *CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector);
	/** */
	void CreateTerrainTypeEditor();
	/** */
	void CreateGroupBuildingTypes();
	/** */
	void CreateGroupUnitTypes();
	/** */
	QWidget *CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector);
	/** */
	void CreateUnitTypeEditor();
private:
	friend class GameDemonstrator;
	int								MinimumEditWidth;	//Has been: itemTerrainType->sizeHint().width()
	QButtonGroup*					GroupTerrainTypes;
	QButtonGroup*					GroupBuildings;
	QButtonGroup*					GroupUnitsTypes;
	TerrainTypeEditor*				TerrainTypeEditorInstance;
	UnitTypeEditor*					UnitTypeEditorInstance;
	ConnectorUnitTypeGameMap*		ConnectorUnitTypeEditorGameMapInstance;
	ConnectorMapUnitItem*			ConnectorMapUnitItemInstance;
	MapView*						MapViewInstance;
	EditorController*				EditorControllerInstance;

};

#endif // CEDITORTOOLBOX_H
