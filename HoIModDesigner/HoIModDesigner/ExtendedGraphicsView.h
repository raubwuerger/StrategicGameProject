#ifndef EXTENDEDGRAPHICSVIEW_H
#define EXTENDEDGRAPHICSVIEW_H

class ExtendedGraphicsScene;

class ExtendedGraphicsView : public QGraphicsView
{
public:
/** */
	ExtendedGraphicsView(QWidget* parent);
/** */
	void wheelEvent(QWheelEvent* event);
public:
	ExtendedGraphicsScene	*m_Scene;
	
};

#endif // EXTENDEDGRAPHICSVIEW_H
