#ifndef EXTENDEDGRAPHICSSCENE_H
#define EXTENDEDGRAPHICSSCENE_H

class ProvinceItem;

class ExtendedGraphicsScene : public QGraphicsScene
{
 	Q_OBJECT
public:
 	ExtendedGraphicsScene(QObject *parent = 0);
signals:
	void SignalProvinceEntered( const ProvinceItem* );
	void SignalProvinceLeft( const ProvinceItem* );
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	bool event(QEvent *event);
};

#include <QGraphicsSceneHoverEvent>
#include <QEvent>

class VisitorEventTranslator
{
public:
	QPointF Position( QGraphicsSceneHoverEvent *event )
	{
		return event->pos();
	}
	QPointF Position( QEvent *event )
	{
		return QPointF(0.0,0.0);
	}
};

#endif // EXTENDEDGRAPHICSSCENE_H
