#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapGraphicsScene;
class HexagonData;
class ConnectorMapHexItem;
class MapEventManager;
class ModelTerrainType;
class HexagonData;
class MapUnitItem;
class GameMapItem;
class MapHexItem;

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
	/** */
	ConnectorMapHexItem* GetConnectorMapHexItem() const;
	/** */
	bool AddMapHexItem(MapHexItem* mapHexItem);
	/** */
	bool AddedMapUnit(MapUnitItem *mapUnitItem);
public slots:
	/** */
	void SlotHexActive( int row, int col );
protected:
	/** */
	virtual void mouseReleaseEvent(QMouseEvent * event);
	/** */
	virtual void mousePressEvent(QMouseEvent *event);
	/** */
	virtual void mouseMoveEvent(QMouseEvent *event);
	/** */
	virtual void wheelEvent( QWheelEvent *event );
private:
	/** */
	void InitMapEventManager();
	/** */
	bool CreateUnits();
	/** */
	double CalcMapWidthInPixel() const;
	/** */
	double CalcMapHeightInPixel() const;
	/** */
	void EmitHexItemPressed();
	/** */
	void DoZoom(QWheelEvent *event);
public:
	MapGraphicsScene*		Scene;					//TODO: Setter
	ConnectorMapHexItem*	ConnectorMapHexItemInstance;	//TODO: Setter
	MapEventManager*		MapEventManagerInstance;		//TODO: Setter
private:
	const int	ROW_COL_NOT_INITIALIZED;
	int			ActiveRow;
	int			ActiveCol;
};

#endif // CMAPVIEW_H
