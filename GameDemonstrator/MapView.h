#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
class MapViewGraphicsScene;

class MapView : public QGraphicsView
{
	Q_OBJECT

public:
	MapView(QWidget *parent);
	~MapView();

public:
	MapViewGraphicsScene	*m_Scene;
private:
	
};

#endif // MAPVIEW_H
