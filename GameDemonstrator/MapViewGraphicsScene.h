#ifndef MAPVIEWGRAPHICSSCENE_H
#define MAPVIEWGRAPHICSSCENE_H

#include <QGraphicsScene>
class HexItemEventManager;

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
	int m_ActiveRow;
	int m_ActiveCol;
	friend class MapView;
	HexItemEventManager	*m_HexItemEventManager;
};

#endif // MAPVIEWGRAPHICSSCENE_H
