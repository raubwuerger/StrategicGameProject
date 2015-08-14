#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;
class HexagonData;

class MapView : public QGraphicsView
{
	Q_OBJECT

public:
	MapView(QWidget *parent);
	~MapView();
public:
	MapViewGraphicsScene	*m_Scene;
private:
	/** */
	void CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon );
	/** */
	double CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const;
	/** */
	double CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const;
private:
	
};

#endif // MAPVIEW_H
