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
class ModelMapItem;

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
	bool AddedMapUnit(int row, int col, MapUnitItem *mapUnitItem);
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
	bool CreateMapFromModel();
	/** */
	void InitMapEventManager();
	/** */
	double CalcMapWidthInPixel() const;
	/** */
	double CalcMapHeightInPixel() const;
	/** */
	bool CreateTopLeftPosition( int col, int row, QPointF &topLeftPosition );
	/** */
	const QImage* GetImage(const ModelMapItem* modelMapItem);
	/** */
	void EmitHexItemPressed();
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
