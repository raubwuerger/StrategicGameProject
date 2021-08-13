#ifndef CONNECTOREDITORMODELREPOSITORY_H
#define CONNECTOREDITORMODELREPOSITORY_H

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
	void SlotTerrainTypeChanged( int modelMapId, int terrainTypeId );
};

#endif // CONNECTOREDITORMODELREPOSITORY_H
