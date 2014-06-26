#include "stdafx.h"
#include "ExtendedGraphicsScene.h"
#include "CommandFactory.h"

ExtendedGraphicsScene::ExtendedGraphicsScene( QObject *parent /*= 0*/ )
	: QGraphicsScene(parent),
	m_ActionEditProvinceDetails(nullptr),
	m_LastSelectedItem(nullptr),
	m_PainterFactory(nullptr)
{
}

#include "ProvinceItem.h"
void ExtendedGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
// 	QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(), event->buttonDownScenePos(Qt::LeftButton).y());
// 	const QList<QGraphicsItem *> itemList = items(mousePos);
//	m_LastSelectedItem = itemList.isEmpty() ? nullptr : itemList.first();
	QGraphicsScene::mousePressEvent(event);
}

#include "ProvinceGraphicsPixmapItem.h"
void ExtendedGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if( m_LastSelectedItem != nullptr && event->button() == Qt::LeftButton && m_PainterFactory != nullptr )
	{
		QSharedPointer<jha::Command> command( m_PainterFactory->CreateCommandProvincePainter(m_LastSelectedItem) );
		if( command->Execute() == true )
		{
			emit SignalProvinceMouseReleased( m_LastSelectedItem );
		}
	}
	QGraphicsScene::mouseReleaseEvent(event);
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

void ExtendedGraphicsScene::contextMenuEvent( QGraphicsSceneContextMenuEvent * contextMenuEvent )
{
	QList<QGraphicsView *> viewList = views();
	QMenu menu( viewList.empty() == true ? nullptr : viewList.at(0) );
	menu.addAction(m_ActionEditProvinceDetails);
// 	menu.addAction(copyAct);
// 	menu.addAction(pasteAct);
	menu.exec(contextMenuEvent->screenPos());
}

#include "CommandFactory.h"
void ExtendedGraphicsScene::OpenProvinceDetailDialog()
{
	QSharedPointer<jha::Command> command( CommandFactory().CreateCommandUpdateProvinceDetails(m_LastSelectedItem) );
	command->Execute();
	emit UpdateProvinceOwner(m_LastSelectedItem);
}

void ExtendedGraphicsScene::Init()
{
	m_ActionEditProvinceDetails = new QAction(QIcon(":HoIModDesigner/images/folder_document.ico"),tr("Province details..."), views().at(0));
	m_ActionEditProvinceDetails->setStatusTip(tr("Edit province details"));
	connect(m_ActionEditProvinceDetails, SIGNAL(triggered()), this, SLOT(OpenProvinceDetailDialog()));
}

void ExtendedGraphicsScene::SlotProvinceEntered( ProvinceItem *item )
{
	m_LastSelectedItem = item;
}

void ExtendedGraphicsScene::SetPainterFactory( CommandFactoryProvincePainter * val )
{
	delete m_PainterFactory;
	m_PainterFactory = val;
}
