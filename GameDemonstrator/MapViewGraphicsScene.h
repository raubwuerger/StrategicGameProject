#ifndef MAPVIEWGRAPHICSSCENE_H
#define MAPVIEWGRAPHICSSCENE_H

#include <QGraphicsScene>

class MapViewGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MapViewGraphicsScene(QObject *parent);
	~MapViewGraphicsScene();
private:
	
};

#endif // MAPVIEWGRAPHICSSCENE_H
