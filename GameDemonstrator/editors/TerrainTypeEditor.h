#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>
class ModelTerrainType;
class MapHexItemEventManager;

class TerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeEditor(QObject *parent);
	/** */
	~TerrainTypeEditor();
	/** */
	void SetMapEventManager(MapHexItemEventManager* mapeventManager);
signals:
	/** */
	void SignalTerrainTypeChanged( int mapItemId, int terrainTypeId );
public slots:
	/** */
	void SlotActivateTerrainType( int terrainTypeId );
	/** */
	void SlotChangeTerrainTypeHexItem( int gameMapItemId );
private:
	ModelTerrainType	*ActiveTerrainType;
	MapHexItemEventManager		*MapEventManagerInstance;
};

#endif // TERRAINTYPEEDITOR_H
