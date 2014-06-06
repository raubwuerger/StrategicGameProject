#include "stdafx.h"
#include "ExtendedGraphicsScene.h"

ExtendedGraphicsScene::ExtendedGraphicsScene( QObject *parent /*= 0*/ )
	: QGraphicsScene(parent)
{

}

void ExtendedGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(), event->buttonDownScenePos(Qt::LeftButton).y());
	const QList<QGraphicsItem *> itemList = items(mousePos);
	QGraphicsItem *selected = itemList.isEmpty() ? 0 : itemList.first();
	if( selected != nullptr )
	{
		//			selected->setBrus
	}
	// 
	// 		if (movingItem != 0 && event->button() == Qt::LeftButton) {
	// 			oldPos = movingItem->pos();
	// 		}
	// 
	clearSelection();
	QGraphicsScene::mousePressEvent(event);
}

bool ExtendedGraphicsScene::event(QEvent *event)
{
	if( event->type() == QEvent::GraphicsSceneHoverEnter ) 
	{
		const QList<QGraphicsItem *> itemList = items( VisitorEventTranslator().Position(event) );
		QGraphicsItem *selected = itemList.isEmpty() ? 0 : itemList.first();
		if( selected != nullptr )
		{
			int waitHere = 0;
		}
		return true;
	}
	return QGraphicsScene::event(event);
}