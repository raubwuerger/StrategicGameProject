#ifndef ConnectorEditorModelRepository_H
#define ConnectorEditorModelRepository_H

class ConnectorTerrainEditorGameMap : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorTerrainEditorGameMap();
	/** */
	~ConnectorTerrainEditorGameMap();
public slots:
	/** */
	void TerrainTypeChanged( int modelMapId, int terrainTypeId );
};

#endif



