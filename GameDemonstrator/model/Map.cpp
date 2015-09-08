#include "stdafx.h"
#include "Map.h"
#include "MapItem.h"

namespace GDModel
{

CMap::CMap()
{
}

CMap::~CMap()
{
}

void CMap::Init( int rows, int cols )
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

void CMap::Release()
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

}
