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
	void UpdateTerrainType( int modelMapId, int terrainTypeId );
};



