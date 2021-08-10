#include "stdafx.h"
#include "GameMapCreatorSaveGame.h"
#include <QtXml>
#include "io/SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "model/ModelTerrainTypeRepository.h"
#include "GameMapItem.h"
#include "GameMapRepository.h"
#include "model/ModelUnitTypeRepository.h"

GameMapCreatorSaveGame::GameMapCreatorSaveGame( const QDomNode mapElements )
	: Rows(-1), Cols(-1)
{
	MapElements = new QDomNode(mapElements);
}

GameMapCreatorSaveGame::~GameMapCreatorSaveGame()
{

}

bool GameMapCreatorSaveGame::CreateMap()
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

	if (false == CreateUnitItems(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::UNITS)))
	{
		return false;
	}

	return true;
}

GameMapRepository* GameMapCreatorSaveGame::GetMap()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool GameMapCreatorSaveGame::InitializeMap(const QDomNode& settings)
{
	QDomNodeList settingsNodeList = settings.childNodes();
	if( true == settingsNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
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

bool GameMapCreatorSaveGame::CreateMapItems(const QDomNode &mapItems)
{
	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if( true == mapItemNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
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

	GameMapRepository::GetInstance()->SetModelMapItems(gameMap);
	return true;
}

GameMapItem* GameMapCreatorSaveGame::CreateFromXML(const QDomNode& mapNode)
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

bool GameMapCreatorSaveGame::CreateUnitItems(const QDomNode& units)
{
	QDomNodeList unitItemNodeList = units.childNodes();
	if (true == unitItemNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNodeList has no child elements"));
		return false;
	}

	QVector<GameUnitItem*> mapItemsUnsorted;
	for (int nodeIndex = 0; nodeIndex < unitItemNodeList.count(); nodeIndex++)
	{
		GameUnitItem* created = CreateUnitItemFromXML(unitItemNodeList.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(unitItemNodeList.at(nodeIndex).columnNumber())));
			return false;
		}
		mapItemsUnsorted.push_back(created);
	}


	return true;

}

#include "GameUnitItem.h"
GameUnitItem* GameMapCreatorSaveGame::CreateUnitItemFromXML(const QDomNode& unitNode)
{
	QDomNodeList mapNodes = unitNode.childNodes();
	if (true == mapNodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	int id = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_ID, id))
		{
			return nullptr;
		}
	}

	int unitTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_UNITTYPEID, unitTypeId))
		{
			return nullptr;
		}
	}

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
	if (nullptr == modelUnitType )
	{
		return nullptr;
	}

	int mapItemId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_MAPITEMID, mapItemId))
		{
			return nullptr;
		}
	}

	GameUnitItem *newUnitItem = new GameUnitItem(id);
	newUnitItem->SetModelUnitType(modelUnitType);
	newUnitItem->SetGameMapItemId(mapItemId);
	return newUnitItem;
}
