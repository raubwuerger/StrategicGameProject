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
public slots:
	/** */
	void HexActive( int row, int col );
protected:
	/** */
	virtual void mouseReleaseEvent(QMouseEvent * event);
	/** */
	virtual void mousePressEvent(QMouseEvent *event);
	/** */
	virtual void mouseMoveEvent(QMouseEvent *event);
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
	void EmitHexItemPressed();
public:
	MapViewGraphicsScene	*Scene;					//TODO: Setter
	HexItemEventManager		*HexItemEventManager;	//TODO: Setter
	MapEventManager			*MapEventManager;		//TODO: Setter
private:
	const int	ROW_COL_NOT_INITIALIZED;
	int			ActiveRow;
	int			ActiveCol;
	bool		SelectedItemChanged;

};

#endif // CMAPVIEW_H
