#include "stdafx.h"
#include "MapViewGraphicsScene.h"

MapViewGraphicsScene::MapViewGraphicsScene(QObject *parent)
	: QGraphicsScene(parent),
	m_ActiveCol(-1),
	m_ActiveRow(-1),
	m_HexItemEventManager(nullptr)
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
	if( m_HexItemEventManager != nullptr )
	{
		emit m_HexItemEventManager->HexItemPressed( m_ActiveRow, m_ActiveCol );
	}
	QGraphicsScene::mousePressEvent(event);
}

void MapViewGraphicsScene::HexActive( int row, int col )
{
	m_ActiveCol = col;
	m_ActiveRow = row;
}
