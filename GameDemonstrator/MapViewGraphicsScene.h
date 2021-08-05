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
protected:
	/** */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	/** */
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
	friend class MapView;
	HexItemEventManager	*HexItemEventManager;
	bool		StartAddingTerrainType;
};

#endif // MAPVIEWGRAPHICSSCENE_H
