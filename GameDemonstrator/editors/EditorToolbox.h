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
	void CreateGroupBuildingTypes();
	/** */
	void CreateGroupUnitTypes();
	/** */
	QWidget *CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, UnitTypeIdSelector *connector);
private slots:
	/** */
	void ButtonGroupTerrainTypes(QAbstractButton *button);
	/** */
	void ButtonGroupUnitTypes(QAbstractButton *button);
private:
	friend class GameDemonstrator;
	QButtonGroup*		GroupTerrainTypes;
	QButtonGroup*		GroupBuildings;
	QButtonGroup*		GroupUnitsTypes;
	TerrainTypeEditor*	TerrainTypeEditorInstance;
	UnitTypeEditor*		UnitTypeEditorInstance;
	int					MinimumEditWidth;	//Has been: itemTerrainType->sizeHint().width()
};

#endif // CEDITORTOOLBOX_H
