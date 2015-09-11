#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;
class HexagonData;
class HexItemEventManager;
class CMapEventManager;
class CTerrainType;

namespace GDModel { class CGameInitialisationData; }

class MapView : public QGraphicsView
{
	Q_OBJECT

public:
	/** */
	MapView(QWidget *parent);
	/** */
	~MapView();
	/** */
	void Init( const GDModel::CGameInitialisationData &data, const CTerrainType* defaultTerrainType );
public:
	MapViewGraphicsScene	*m_Scene;
	HexItemEventManager		*m_HexItemEventManager;
	CMapEventManager		*m_MapEventManager;
private:
	/** */
	void CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon, const QImage* defaultTerrainType );
	/** */
	double CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const;
	/** */
	double CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const;
private:
};

#endif // MAPVIEW_H
