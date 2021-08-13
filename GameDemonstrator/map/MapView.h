#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include <QGraphicsView>
class MapGraphicsScene;
class MapHexItemHexagonData;
class ConnectorMapHexItem;
class ConnectorMapUnitItem;
class MapHexItemEventManager;
class ModelTerrainType;
class MapHexItemHexagonData;
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
	ConnectorMapUnitItem* GetConnectorMapUnitItem() const;
	/** */
	bool AddMapHexItem(MapHexItem* mapHexItem);
	/** */
	bool AddedMapUnit(MapUnitItem *mapUnitItem);
public slots:
	/** */
	void SlotHexMapItemActive( int row, int col );
	/** */
	void SlotUnitItemActive(int unitItemId);
	/** */
	void SlotUnitItemDeacivated();
protected:
	/** */
	virtual void mouseReleaseEvent(QMouseEvent * event);
	/** */
	virtual void mousePressEvent(QMouseEvent *event);
	/** */
	virtual void wheelEvent( QWheelEvent *event );
private:
	/** */
	void InitMapEventManager();
	/** */
	double CalcMapWidthInPixel() const;
	/** */
	double CalcMapHeightInPixel() const;
	/** */
	void EmitHexItemPressed();
	/** */
	void DoZoom(QWheelEvent *event);
public:
	MapGraphicsScene*		Scene;					
	ConnectorMapHexItem*	ConnectorMapHexItemInstance;
	ConnectorMapUnitItem*	ConnectorMapUnitItemInstance;
	MapHexItemEventManager*		MapEventManagerInstance;	
private:
	const int	NO_ACTIVE_UNIT_ID;
	const int	ROW_COL_NOT_INITIALIZED;
	int			ActiveRow;
	int			ActiveCol;
	int			ActiveUnitItemId;
};

#endif // CMAPVIEW_H
