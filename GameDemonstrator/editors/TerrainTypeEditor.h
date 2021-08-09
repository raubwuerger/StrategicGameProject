#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>
class ModelTerrainType;
class MapEventManager;

class TerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeEditor(QObject *parent);
	/** */
	~TerrainTypeEditor();
	/** */
	void SetMapEventManager(MapEventManager* mapeventManager);
signals:
	/** */
	void SignalTerrainTypeChanged( int mapItemId, int terrainTypeId );
public slots:
	/** */
	void SlotActivateTerrainType( int terrainTypeId );
	/** */
	void ChangeTerrainTypeHexItem( int row, int col );
private:
	ModelTerrainType	*ActiveTerrainType;
	MapEventManager		*MapEventManagerInstance;
};

#endif // TERRAINTYPEEDITOR_H
