#include "stdafx.h"
#include "GameMapTileRepository.h"
#include "GameMapTile.h"
#include "LogInterface.h"

GameMapTileRepository*	GameMapTileRepository::Instance = nullptr;

GameMapTileRepository* GameMapTileRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameMapTileRepository;
	return Instance;
}

bool GameMapTileRepository::Init()
{
	if ( nullptr != GameMapTiles )
	{ 
		GameMapTiles->clear();
	}
	IdToModelMapTile.clear();
	return true;
}

void GameMapTileRepository::Release()
{
	delete Instance;
}

const QVector< QVector<GameMapTile*> >* GameMapTileRepository::GetMapTiles() const
{
	return GameMapTiles;
}

void GameMapTileRepository::SetGameMapTiles( QVector< QVector<GameMapTile*>>* gameMapTiles)
{
	delete GameMapTiles;
	GameMapTiles = gameMapTiles;
	UpdateIdToModelMapTile();
}

void GameMapTileRepository::UpdateIdToModelMapTile()
{
	IdToModelMapTile.clear();
	int rows = GetRows();
	int cols = GetCols();
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			QVector<GameMapTile*> row = GameMapTiles->at(currentRow);
			IdToModelMapTile.insert( row.at(currentCol)->GetId(), row.at(currentCol) );
		}
	}
}

GameMapTileRepository::GameMapTileRepository()
	: GameMapTiles(nullptr)
{
}

GameMapTileRepository::~GameMapTileRepository()
{
	delete GameMapTiles;
}

int GameMapTileRepository::GetCols() const
{
	if( nullptr == GameMapTiles )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapTiles()" ) );
		return 0;
	}

	QVector<GameMapTile*> firstRow = GameMapTiles->at(0);
	if( true == firstRow.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapTiles()" ) );
		return 0;
	}

	return firstRow.size();
}

int GameMapTileRepository::GetRows() const
{
	if( nullptr == GameMapTiles )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapTiles()" ) );
		return 0;
	}
	return GameMapTiles->size();
}

GameMapTile* GameMapTileRepository::GetGameMapTile( unsigned int row, unsigned int col)
{
	int rowCount = GetRows();
	if( row > rowCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested row index %1 out of bounds: %2" ).arg(row).arg(rowCount) );
		return nullptr;
	}

	QVector<GameMapTile*> concreteRow = GameMapTiles->at(row);

	int colCount = GetCols();
	if( col > colCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested column index %1 out of bounds: %2" ).arg(col).arg(colCount) );
		return nullptr;
	}
	return concreteRow.at(col);
}

int GameMapTileRepository::GetGameMapTileId( unsigned int row, unsigned int col)
{
	const GameMapTile* found = GetGameMapTile(row,col);
	if( nullptr == found )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map tile not found: column|row: %1|%2" ).arg(col).arg(row) );
		return -1;
	}
	return found->GetId();
}

bool GameMapTileRepository::UpdateGameMapTile(const GameMapTile* gameMapTile)
{
	jha::GetLog()->Log_DEBUG( QObject::tr("Not yet implemented!") );
	return false;
}

GameMapTile* GameMapTileRepository::GetById(unsigned int id)
{
	if( id < 0 )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map tile id is invalid (below zero)!" ) );
		return nullptr;
	}

	GameMapTile* gameMapTile = IdToModelMapTile.value(id);
	if( nullptr == gameMapTile )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map tile id %1 is not registered!" ).arg(QString::number(id)) );
		return nullptr;
	}
	return gameMapTile;
}

const GameMapTile* GameMapTileRepository::GetByColAndRow(int col, int row)
{
	if (col < 0)
	{
		jha::GetLog()->Log_INFO(QObject::tr("Column mustn't be lesser the 0!"));
		return nullptr;
	}
	if (row < 0)
	{
		jha::GetLog()->Log_INFO(QObject::tr("Row mustn't be lesser the 0!"));
		return nullptr;
	}

	int rowCount = GameMapTiles->size();
	if (row >= rowCount)
	{
		jha::GetLog()->Log_INFO(QObject::tr("Row is to great!!"));
		return nullptr;
	}

	const QVector<GameMapTile*>& concreteRow = GameMapTiles->at(row);

	int colCount = concreteRow.size();
	if (col >= colCount)
	{
		jha::GetLog()->Log_INFO(QObject::tr("Column is to great!!"));
		return nullptr;
	}

	return concreteRow.at(col);
}
