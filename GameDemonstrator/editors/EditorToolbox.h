#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

//================================================================================
#include <QToolBox>
class ModelTerrainTypeRepository;
class TerrainTypeIdSelector;
class UnitTypeIdSelector;
class ModelTerrainType;
class TerrainTypeEditor;
class UnitTypeEditor;
class ModelUnitType;

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
	int					MinimumEditWidth;	//Was: itemTerrainType->sizeHint().width()
};

//================================================================================
class TerrainTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeIdSelector( int terrainTypeId );
public slots:
	/** */
	void Trigger();
signals:
	/** */
	void TerrainTypeActive( int terrainTypeId );
private:
	int TerrainTypeId;
};

//================================================================================
class UnitTypeIdSelector : public QObject
{
	Q_OBJECT
public:
	/** */
	UnitTypeIdSelector(int unitTypeId);
public slots:
	/** */
void Trigger();
signals:
	/** */
	void UnitTypeActive(int unitTypeId);
private:
	int UnitTypeId;
};

#endif // CEDITORTOOLBOX_H
