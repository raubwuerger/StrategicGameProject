#include "stdafx.h"
#include "GameMap.h"
#include "MapItem.h"


GameMap::GameMap()
	: Rows(10),
	Cols(10)
{
}

GameMap::~GameMap()
{
}

void GameMap::Create()
{
	for( int row=0;row<Rows;row++ )
	{
		QVector<MapItem*> tempRow;
		for( int col=0;col<Cols;col++ )
		{
			tempRow.append( new MapItem(row,col) );
		}
		MapItems.append( tempRow );
	}
}

void GameMap::Init( int rows, int cols )
{
	for( int row=0;row<rows;row++ )
	{
		QVector<MapItem*> tempRow;
		for( int col=0;col<cols;col++ )
		{
			tempRow.append( new MapItem(row,col) );
		}
		MapItems.append( tempRow );
	}
}

void GameMap::Release()
{
	QVector< QVector<MapItem*> >::iterator row = MapItems.begin();
	while( row != MapItems.end() )
	{
		QVector<MapItem*>::iterator col = (*row).begin();
		while( col != (*row).end() )
		{
			delete (*col);
			++col;
		}
		++row;
	}
	MapItems.clear();
}

const QVector< QVector<MapItem*> >& GameMap::GetMapItems() const
{
	return MapItems;
}