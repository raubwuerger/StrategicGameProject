#include "stdafx.h"
#include "GameMap.h"
#include "MapItem.h"

namespace GDModel
{

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::Init( int rows, int cols )
{
	for( int row=0;row<rows;row++ )
	{
		QVector<GDModel::CMapItem*> tempRow;
		for( int col=0;col<cols;col++ )
		{
			tempRow.append( new GDModel::CMapItem(row,col) );
		}
		MapItems.append( tempRow );
	}
}

void GameMap::Release()
{
	QVector< QVector<GDModel::CMapItem*> >::iterator row = MapItems.begin();
	while( row != MapItems.end() )
	{
		QVector<GDModel::CMapItem*>::iterator col = (*row).begin();
		while( col != (*row).end() )
		{
			delete (*col);
			++col;
		}
		++row;
	}
	MapItems.clear();
}

const QVector< QVector<GDModel::CMapItem*> >& GameMap::GetMapItems() const
{
	return MapItems;
}

}