#include "stdafx.h"
#include "GameMapItemRepository.h"
#include "GameMapItem.h"
#include "LogInterface.h"

GameMapItemRepository*	GameMapItemRepository::Instance = nullptr;

GameMapItemRepository* GameMapItemRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameMapItemRepository;
	return Instance;
}

void GameMapItemRepository::Init()
{
	if ( nullptr != MapItems )
	{ 
		MapItems->clear();
	}
	IdToModelMapItem.clear();
}

void GameMapItemRepository::Release()
{
	delete Instance;
}

const QVector< QVector<GameMapItem*> >* GameMapItemRepository::GetMapItems() const
{
	return MapItems;
}

void GameMapItemRepository::SetGameMapItems( QVector< QVector<GameMapItem*>>* mapItems)
{
	delete MapItems;
	MapItems = nullptr;
	MapItems = mapItems;
	UpdateIdToModelMapItem();
}

void GameMapItemRepository::UpdateIdToModelMapItem()
{
	IdToModelMapItem.clear();
	int rows = GetRows();
	int cols = GetCols();
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			QVector<GameMapItem*> row = MapItems->at(currentRow);
			IdToModelMapItem.insert( row.at(currentCol)->GetId(), row.at(currentCol) );
		}
	}
}

GameMapItemRepository::GameMapItemRepository()
	: MapItems(nullptr)
{
}

GameMapItemRepository::~GameMapItemRepository()
{
	delete MapItems;
}

int GameMapItemRepository::GetCols() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	QVector<GameMapItem*> firstRow = MapItems->at(0);
	if( true == firstRow.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	return firstRow.size();
}

int GameMapItemRepository::GetRows() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}
	return MapItems->size();
}

GameMapItem* GameMapItemRepository::GetGameMapItem( unsigned int row, unsigned int col)
{
	int rowCount = GetRows();
	if( row > rowCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested row index %1 out of bounds: %2" ).arg(row).arg(rowCount) );
		return nullptr;
	}

	QVector<GameMapItem*> concreteRow = MapItems->at(row);

	int colCount = GetCols();
	if( col > colCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested column index %1 out of bounds: %2" ).arg(col).arg(colCount) );
		return nullptr;
	}
	return concreteRow.at(col);
}

int GameMapItemRepository::GetGameMapItemId( unsigned int row, unsigned int col)
{
	const GameMapItem* found = GetGameMapItem(row,col);
	if( nullptr == found )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map item not found: column|row: %1|%2" ).arg(col).arg(row) );
		return -1;
	}
	return found->GetId();
}

bool GameMapItemRepository::UpdateGameMapItem( const GameMapItem* ItemToUpdate )
{
	jha::GetLog()->Log_DEBUG( QObject::tr("Not yet implemented!") );
	return false;
}

GameMapItem* GameMapItemRepository::GetGameMapItemById(unsigned int id)
{
	if( id < 0 )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map item id is invalid (below zero)!" ) );
		return nullptr;
	}

	GameMapItem* modelMapItem = IdToModelMapItem.value(id);
	if( nullptr == modelMapItem )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map item id %1 is not registered!" ).arg(QString::number(id)) );
		return nullptr;
	}
	return modelMapItem;
}
