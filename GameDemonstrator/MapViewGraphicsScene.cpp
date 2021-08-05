#include "stdafx.h"
#include "MapViewGraphicsScene.h"
#include "HexItemEventManager.h"

MapViewGraphicsScene::MapViewGraphicsScene(QObject *parent)
	: QGraphicsScene(parent),
	HexItemEventManager(nullptr)
{

}

MapViewGraphicsScene::~MapViewGraphicsScene()
{

}

void MapViewGraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
	QGraphicsScene::mouseReleaseEvent(event);
}

void MapViewGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsScene::mousePressEvent(event);
}

void MapViewGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);
}
