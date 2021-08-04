#pragma once

class ConnectorEditorModelRepository : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorEditorModelRepository();
	/** */
	~ConnectorEditorModelRepository();
public slots:
	/** */
	void TerrainTypeChanged( int modelMapId, int terrainTypeId );
};



