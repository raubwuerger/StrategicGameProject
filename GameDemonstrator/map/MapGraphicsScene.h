#ifndef MAPVIEWGRAPHICSSCENE_H
#define MAPVIEWGRAPHICSSCENE_H

#include <QGraphicsScene>

/** Benutzerschnittstelle zu Karte */
class MapGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	/** */
	MapGraphicsScene(QObject *parent);
	/** */
	~MapGraphicsScene();
protected:
	/** */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	/** */
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAPVIEWGRAPHICSSCENE_H
