#include "stdafx.h"
#include "MapCreatorSaveGame.h"
#include <QtXml>
#include "SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "ModelTerrainTypeRepository.h"
#include "ModelMapItem.h"
#include "ModelMapRepository.h"

MapCreatorSaveGame::MapCreatorSaveGame( const QDomNode mapElements )
	: Rows(-1), Cols(-1)
{
	MapElements = new QDomNode(mapElements);
}

MapCreatorSaveGame::~MapCreatorSaveGame()
{

}

bool MapCreatorSaveGame::CreateMap()
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

ModelMapRepository* MapCreatorSaveGame::GetMap()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool MapCreatorSaveGame::InitializeMap(const QDomNode& settings)
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

bool MapCreatorSaveGame::CreateMapItems(const QDomNode &mapItems)
{
	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if( true == mapItemNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
		return false;
	}

	QVector<ModelMapItem*> mapItemsUnsorted;
	for( int nodeIndex = 0; nodeIndex < mapItemNodeList.count(); nodeIndex++ )
	{
		ModelMapItem* created = CreateFromXML( mapItemNodeList.at(nodeIndex) );
		if( nullptr == created )
		{
			jha::GetLog()->Log_WARNING( QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(mapItemNodeList.at(nodeIndex).columnNumber())) );
			return false;
		}
		mapItemsUnsorted.push_back(created);
	}

	int mapItemsUnsortedIndex = 0;
	QVector< QVector<ModelMapItem*> >* gameMap = new QVector< QVector<ModelMapItem*> >();
	for( int rowIndex = 0; rowIndex < Rows; rowIndex++ )
	{
		QVector<ModelMapItem*> row;
		row.reserve(Cols);
		for( int colIndex = 0; colIndex < Cols; colIndex++ )
		{
			row.append(mapItemsUnsorted.at(mapItemsUnsortedIndex++));
		}
		gameMap->append(row);
	}

	ModelMapRepository::GetInstance()->SetMapItems(gameMap);
	return true;
}

ModelMapItem* MapCreatorSaveGame::CreateFromXML(const QDomNode& mapNode)
{
	QDomNodeList mapNodes = mapNode.childNodes();
	if( true == mapNodes.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNode has no child elements!") );
		return false;
	}

	int currentId = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ID, currentId ) )
		{
			return false;
		}
	}

	int currentRow = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROW, currentRow ) )
		{
			return false;
		}
	}

	int currentCol = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COL, currentCol ) )
		{
			return false;
		}
	}

	int currentTerrainTyp = -1;
	{
		DomValueExtractor domNodeListValueExtractor( mapNode );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::TERRAINTYPE, currentTerrainTyp ) )
		{
			return false;
		}
	}

	ModelMapItem *newModelMapItem = new ModelMapItem( currentRow, currentCol, currentId );
	newModelMapItem->SetModelTerrainType( ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById(currentTerrainTyp) );
	return newModelMapItem;
}

/*
MapItemId = 0;
unsigned int cols = ModelMapConfig::GetInstance()->Cols;
unsigned int rows = ModelMapConfig::GetInstance()->Rows;

const ModelTerrainType* defaultTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();

QVector< QVector<ModelMapItem*> >* theCreatedMap = new QVector< QVector<ModelMapItem*> >();
theCreatedMap->reserve(rows);
for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
{
QVector<ModelMapItem*> tempRow;
tempRow.reserve(cols);
for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
{
ModelMapItem* modelMapItem = new ModelMapItem(currentRow,currentCol,++MapItemId);
modelMapItem->SetModelTerrainType( defaultTerrainType );
tempRow.append( modelMapItem );
}
theCreatedMap->append(tempRow);
}

ModelMapRepository::GetInstance()->SetMapItems( theCreatedMap );
return true;
*/



