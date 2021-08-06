#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

//================================================================================
#include <QToolBox>
class ModelTerrainTypeRepository;
class ConnectorButtonTerrainTypeId;
class ConnectorButtonUnitTypeId;
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
	QWidget *CreateTerrainTypeWidget(const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, ConnectorButtonTerrainTypeId *connector);
	/** */
	void CreateGroupBuildingTypes();
	/** */
	void CreateGroupUnitTypes();
	/** */
	QWidget *CreateUnitTypeWidget(const ModelUnitType* modelUnitType, QButtonGroup* buttonGroup, ConnectorButtonUnitTypeId *connector);
private slots:
	/** */
	void ButtonGroupTerrainTypes(QAbstractButton *button);
	/** */
	void ButtonGroupUnitTypes(QAbstractButton *button);
private:
	friend class GameDemonstrator;
	QButtonGroup		*GroupTerrainTypes;
	QButtonGroup		*GroupBuildings;
	QButtonGroup		*GroupUnitsTypes;
	TerrainTypeEditor	*TerrainTypeEditor;
	UnitTypeEditor		*UnitTypeEditor;
	int					MinimumEditWidth;	//Was: itemTerrainType->sizeHint().width()
};

//================================================================================
class ConnectorButtonTerrainTypeId : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorButtonTerrainTypeId( int terrainTypeId );
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
class ConnectorButtonUnitTypeId : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorButtonUnitTypeId(int unitTypeId);
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
