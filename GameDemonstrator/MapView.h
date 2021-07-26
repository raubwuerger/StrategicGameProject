#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;
class HexagonData;
class HexItemEventManager;
class CMapEventManager;
class CTerrainType;

class CGameInitialisationData;

class CMapView : public QGraphicsView
{
	Q_OBJECT

public:
	/** */
	CMapView(QWidget *parent);
	/** */
	~CMapView();
	/** */
	void Init( const CGameInitialisationData &data, const CTerrainType* defaultTerrainType );
	/** */
	void Create();
public:
	MapViewGraphicsScene	*Scene;
	HexItemEventManager		*HexItemEventManager;
	CMapEventManager		*MapEventManager;
private:
	/** */
	void CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon, const QImage* defaultTerrainType );
	/** */
	double CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const;
	/** */
	double CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const;
private:
};

#endif // CMAPVIEW_H
