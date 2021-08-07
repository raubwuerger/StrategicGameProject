#include "stdafx.h"
#include "MapGraphicsScene.h"

MapGraphicsScene::MapGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{

}

MapGraphicsScene::~MapGraphicsScene()
{

}

void MapGraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	QGraphicsScene::mouseReleaseEvent(event);
}

void MapGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsScene::mousePressEvent(event);
}

void MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
}
