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
class ConnectorTerrainEditorGameMap;
class ConnectorUnitTypeGameMap;
class MapEventManager;

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
private:
	/** */
	void CreateGroupTerrainTypes();
	/** */
	QWidget *CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, TerrainTypeIdSelector *connector);
	/** */
	void CreateTerrainTypeEditor(MapEventManager* mapEventManager);
	/** */
	void CreateGroupBuildingTypes();
	/** */
	void CreateGroupUnitTypes();
	/** */
	QWidget *CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector);
	/** */
	void CreateUnitTypeEditor(MapEventManager* mapEventManager);
private:
	friend class GameDemonstrator;
	int								MinimumEditWidth;	//Has been: itemTerrainType->sizeHint().width()
	QButtonGroup*					GroupTerrainTypes;
	QButtonGroup*					GroupBuildings;
	QButtonGroup*					GroupUnitsTypes;
	TerrainTypeEditor*				TerrainTypeEditorInstance;
	UnitTypeEditor*					UnitTypeEditorInstance;
	ConnectorMapHexItem*			ConnectorMapHexItemInstance;
	ConnectorTerrainEditorGameMap*	ConnectorEditorModelRepositoryInstance;
	ConnectorUnitTypeGameMap*		ConnectorUnitTypeEditorGameMapInstance;
	MapEventManager*				MapEventManagerInstance;
};

#endif // CEDITORTOOLBOX_H
