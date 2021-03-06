#ifndef TERRAINTYPEEDITOR_H
#define TERRAINTYPEEDITOR_H

#include <QObject>
class CTerrainType;
class CTerrainTypeRepository;
class CMapEventManager;

class CTerrainTypeEditor : public QObject
{
	Q_OBJECT
public:
	/** */
	CTerrainTypeEditor(QObject *parent);
	/** */
	~CTerrainTypeEditor();
public slots:
	/** */
	void ActivateTerrainType( int terrainTypeId );
	/** */
	void ChangeTerrainTypeHexItem( int row, int col );
private:
	friend class GameDemonstrator;
	CTerrainType			*ActiveTerrainType;
	CTerrainTypeRepository	*TerrainTypeRepository;
	CMapEventManager		*MapEventManager;
};

#endif // TERRAINTYPEEDITOR_H
