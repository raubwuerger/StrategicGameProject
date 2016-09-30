#ifndef MAPVIEWGRAPHICSSCENE_H
#define MAPVIEWGRAPHICSSCENE_H

#include <QGraphicsScene>
class HexItemEventManager;

/** Benutzerschnittstelle zu Karte */
class MapViewGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	/** */
	MapViewGraphicsScene(QObject *parent);
	/** */
	~MapViewGraphicsScene();
public slots:
	/** */
	void HexActive( int row, int col );
protected:
	/** */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
	int ActiveRow;
	int ActiveCol;
	friend class MapView;
	HexItemEventManager	*HexItemEventManager;
};

#endif // MAPVIEWGRAPHICSSCENE_H
