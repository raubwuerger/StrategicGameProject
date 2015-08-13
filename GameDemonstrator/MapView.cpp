#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	m_Scene = new MapViewGraphicsScene(this);
//	m_Scene->addText("Holla die Mehrjungrfau ...");

	m_Scene->addItem( new MapViewHexItem(nullptr,10,17.32) );
	setScene(m_Scene);
	setSceneRect(0, 0, 5000, 5000);

	//Use ScrollHand Drag Mode to enable Panning
	setDragMode(ScrollHandDrag);
}

MapView::~MapView()
{

}
