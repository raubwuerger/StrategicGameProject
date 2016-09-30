#include "stdafx.h"
#include "MapViewGraphicsScene.h"

MapViewGraphicsScene::MapViewGraphicsScene(QObject *parent)
	: QGraphicsScene(parent),
	ActiveCol(-1),
	ActiveRow(-1),
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

#include "MapViewHexItem.h"
void MapViewGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	if( HexItemEventManager != nullptr )
	{
		emit HexItemEventManager->HexItemPressed( ActiveRow, ActiveCol );
	}
	QGraphicsScene::mousePressEvent(event);
}

void MapViewGraphicsScene::HexActive( int row, int col )
{
	ActiveCol = col;
	ActiveRow = row;
}
