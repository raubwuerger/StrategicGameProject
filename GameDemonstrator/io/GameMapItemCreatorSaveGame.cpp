#include "stdafx.h"
#include "GameMapItemCreatorSaveGame.h"
#include <QtXml>
#include "io/SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameMapItem.h"
#include "game/GameMapItemRepository.h"
#include "model/ModelUnitTypeRepository.h"

GameMapItemCreatorSaveGame::GameMapItemCreatorSaveGame( const QDomNode mapElements )
	: Rows(-1), Cols(-1)
{
	MapElements = new QDomNode(mapElements);
}

GameMapItemCreatorSaveGame::~GameMapItemCreatorSaveGame()
{

}

bool GameMapItemCreatorSaveGame::CreateMap()
{
	DomNodeFinder domNodeFinder(*MapElements);

	if( false == InitializeMap(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::SETTINGS)) )
	{
		return false;
	}

	if( false == CreateMapItems(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAPITEMS)) )
	{
		return false;
	}

	return true;
}

bool GameMapItemCreatorSaveGame::InitializeMap(const QDomNode& settings)
{
	QDomNodeList settingsNodeList = settings.childNodes();
	if( true == settingsNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("%1: QDomNodeList has no child elements").arg(settings.nodeName()) );
		return false;
	}

	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROWS, Rows ) )
		{
			return false;
		}
	}

	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COLS, Cols ) )
		{
			return false;
		}
	}

	return true;
}

bool GameMapItemCreatorSaveGame::CreateMapItems(const QDomNode &mapItems)
{
	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if( true == mapItemNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("%1: QDomNodeList has no child elements").arg(mapItems.nodeName()) );
		return false;
	}

	QVector<GameMapItem*> mapItemsUnsorted;
	for( int nodeIndex = 0; nodeIndex < mapItemNodeList.count(); nodeIndex++ )
	{
		GameMapItem* created = CreateFromXML( mapItemNodeList.at(nodeIndex) );
		if( nullptr == created )
		{
			jha::GetLog()->Log_WARNING( QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(mapItemNodeList.at(nodeIndex).columnNumber())) );
			return false;
		}
		mapItemsUnsorted.push_back(created);
	}

	int mapItemsUnsortedIndex = 0;
	QVector< QVector<GameMapItem*> >* gameMap = new QVector< QVector<GameMapItem*> >();
	for( int rowIndex = 0; rowIndex < Rows; rowIndex++ )
	{
		QVector<GameMapItem*> row;
		row.reserve(Cols);
		for( int colIndex = 0; colIndex < Cols; colIndex++ )
		{
			row.append(mapItemsUnsorted.at(mapItemsUnsortedIndex++));
		}
		gameMap->append(row);
	}

	GameMapItemRepository::GetInstance()->Init();
	GameMapItemRepository::GetInstance()->SetGameMapItems(gameMap);
	return true;
}

GameMapItem* GameMapItemCreatorSaveGame::CreateFromXML(const QDomNode& mapNode)
{
	QDomNodeList mapNodes = mapNode.childNodes();
	if( true == mapNodes.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNode has no child elements!") );
		return nullptr;
	}

	int currentId = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ID, currentId ) )
		{
			return nullptr;
		}
	}

	int currentRow = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROW, currentRow ) )
		{
			return nullptr;
		}
	}

	int currentCol = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COL, currentCol ) )
		{
			return nullptr;
		}
	}

	int currentTerrainTyp = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::TERRAINTYPE, currentTerrainTyp ) )
		{
			return nullptr;
		}
	}

	GameMapItem *newModelMapItem = new GameMapItem( currentRow, currentCol, currentId );
	newModelMapItem->SetModelTerrainType( ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById(currentTerrainTyp) );
	return newModelMapItem;
}

