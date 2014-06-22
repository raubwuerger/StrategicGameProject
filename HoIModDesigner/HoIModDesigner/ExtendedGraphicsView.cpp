#include "stdafx.h"
#include "ExtendedGraphicsView.h"
#include "ExtendedGraphicsScene.h"

ExtendedGraphicsView::ExtendedGraphicsView( QWidget* parent ) : QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	m_Scene = new ExtendedGraphicsScene(this);
	setScene(m_Scene);
	m_Scene->Init();
	//Set-up the view
	setSceneRect(0, 0, 5000, 5000);

	//Use ScrollHand Drag Mode to enable Panning
	setDragMode(ScrollHandDrag);
}

void ExtendedGraphicsView::wheelEvent( QWheelEvent* event )
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	// Scale the view / do the zoom
	double scaleFactor = 1.15;
	if(event->delta() > 0) 
	{
		// Zoom in
		scale(scaleFactor, scaleFactor);
	} 
	else 
	{
		// Zooming out
		scale(1.0 / scaleFactor, 1.0 / scaleFactor);
	}

	// Don't call superclass handler here
	// as wheel is normally used for moving scrollbars
}
