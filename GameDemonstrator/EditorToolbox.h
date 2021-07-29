#ifndef CEDITORTOOLBOX_H
#define CEDITORTOOLBOX_H

//================================================================================
#include <QToolBox>
class ModelTerrainTypeRepository;
class ConnectorButtonTerrainTypeId;
class ModelTerrainType;
class TerrainTypeEditor;

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
	QWidget *CreateTerrainTypeWidget( const ModelTerrainType* modelTerrainType, QButtonGroup* buttonGroup, ConnectorButtonTerrainTypeId *connector );
private slots:
	/** */
	void ButtonGroupTerrainTypes(QAbstractButton *button);
private:
	friend class GameDemonstrator;
	QButtonGroup		*GroupTerrainTypes;
	QButtonGroup		*GroupBuildings;
	TerrainTypeEditor	*TerrainTypeEditor;
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

#endif // CEDITORTOOLBOX_H
