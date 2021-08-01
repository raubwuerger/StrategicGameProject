#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;
class HexagonData;
class HexItemEventManager;
class MapEventManager;
class ModelTerrainType;
class HexagonData;

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
	MapViewGraphicsScene	*Scene;					//TODO: Setter
	HexItemEventManager		*HexItemEventManager;	//TODO: Setter
	MapEventManager			*MapEventManager;		//TODO: Setter
private:
	/** */
	void CreateMapFromModel();
	/** */
	void InitMapEventManager();
	/** */
	double CalcMapWidthInPixel() const;
	/** */
	double CalcMapHeightInPixel() const;
	/** */
	bool CreateTopLeftPosition( int col, int row, QPointF &topLeftPosition );
};

#endif // CMAPVIEW_H
