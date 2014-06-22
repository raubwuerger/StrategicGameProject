#include "stdafx.h"
#include "ExtendedGraphicsScene.h"

ExtendedGraphicsScene::ExtendedGraphicsScene( QObject *parent /*= 0*/ )
	: QGraphicsScene(parent),
	m_ActionEditProvinceDetails(nullptr),
	m_LastSelectedItem(nullptr)
{
}

void ExtendedGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
// 	QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(), event->buttonDownScenePos(Qt::LeftButton).y());
// 	const QList<QGraphicsItem *> itemList = items(mousePos);
//	m_LastSelectedItem = itemList.isEmpty() ? nullptr : itemList.first();
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

void ExtendedGraphicsScene::contextMenuEvent( QGraphicsSceneContextMenuEvent * contextMenuEvent )
{
	QList<QGraphicsView *> viewList = views();
	QMenu menu( viewList.empty() == true ? nullptr : viewList.at(0) );
	menu.addAction(m_ActionEditProvinceDetails);
// 	menu.addAction(copyAct);
// 	menu.addAction(pasteAct);
	menu.exec(contextMenuEvent->screenPos());
}

#include "DialogProvinceDetails.h"
#include "HoI3Scriptparser.h"
#include "ParserHoI3.h"
#include "ProvinceItem.h"
#include "ProvinceGraphicsPixmapItem.h"
void ExtendedGraphicsScene::OpenProvinceDetailDialog()
{
	QGraphicsItem *activeItem = mouseGrabberItem();

	DialogProvinceDetails dialog;
	dialog.SetProvinceItem(m_LastSelectedItem);
	if( dialog.exec() != QDialog::Accepted )
	{
		return;
	}
	dialog.UpdateProvinceItem(m_LastSelectedItem);

	HoI3Script provinceScript( m_LastSelectedItem->m_FilePath );

	QMap<QString,ItemData>::ConstIterator iter;
	for( iter = m_LastSelectedItem->GetItemMap().constBegin(); iter != m_LastSelectedItem->GetItemMap().constEnd(); iter++ )
	{
		if( iter->GetData().type() == QVariant::StringList )
		{
			QStringList stringList = iter->GetData().toStringList();
			for( int i=0;i<stringList.size();i++ )
			{
				provinceScript.m_TokenList.append( HoI3Token( iter->GetName(), stringList.at(i)) );
			}
		}
		else
		{
			provinceScript.m_TokenList.append( HoI3Token( iter->GetName(), iter->GetData().toString()) );
		}
	}

	HoI3Scriptparser scriptParser;
	scriptParser.SaveScript( provinceScript );
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
