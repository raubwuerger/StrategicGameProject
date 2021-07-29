#include "stdafx.h"
#include "ModelMapRepository.h"
#include "ModelMapItem.h"


ModelMapRepository::ModelMapRepository()
	: Rows(10),
	Cols(10)
{
}

ModelMapRepository::~ModelMapRepository()
{
}

void ModelMapRepository::Create()
{
	for( int row=0;row<Rows;row++ )
	{
		QVector<ModelMapItem*> tempRow;
		for( int col=0;col<Cols;col++ )
		{
			tempRow.append( new ModelMapItem(row,col) );
		}
		MapItems.append( tempRow );
	}
}

void ModelMapRepository::Init( int rows, int cols )
{
	for( int row=0;row<rows;row++ )
	{
		QVector<ModelMapItem*> tempRow;
		for( int col=0;col<cols;col++ )
		{
			tempRow.append( new ModelMapItem(row,col) );
		}
		MapItems.append( tempRow );
	}
}

void ModelMapRepository::Release()
{
	QVector< QVector<ModelMapItem*> >::iterator row = MapItems.begin();
	while( row != MapItems.end() )
	{
		QVector<ModelMapItem*>::iterator col = (*row).begin();
		while( col != (*row).end() )
		{
			delete (*col);
			++col;
		}
		++row;
	}
	MapItems.clear();
}

const QVector< QVector<ModelMapItem*> >& ModelMapRepository::GetMapItems() const
{
	return MapItems;
}
