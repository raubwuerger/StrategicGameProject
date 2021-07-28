#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;
class HexagonData;
class HexItemEventManager;
class MapEventManager;
class TerrainType;

class MapView : public QGraphicsView
{
	Q_OBJECT

public:
	/** */
	MapView(QWidget *parent);
	/** */
	~MapView();
	/** */
	void Create();
public:
	MapViewGraphicsScene	*Scene;
	HexItemEventManager		*HexItemEventManager;
	MapEventManager		*MapEventManager;
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
