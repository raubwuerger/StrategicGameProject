#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>
class TerrainType;
class MapEventManager;

class TerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	TerrainTypeEditor(QObject *parent);
	/** */
	~TerrainTypeEditor();
public slots:
	/** */
	void ActivateTerrainType( int terrainTypeId );
	/** */
	void ChangeTerrainTypeHexItem( int row, int col );
private:
	friend class GameDemonstrator;
	TerrainType			*ActiveTerrainType;
	MapEventManager		*MapEventManager;
};

#endif // TERRAINTYPEEDITOR_H
