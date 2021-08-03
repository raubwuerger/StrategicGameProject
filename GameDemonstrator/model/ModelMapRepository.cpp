#include "stdafx.h"
#include "ModelMapRepository.h"
#include "ModelMapItem.h"
#include "LogInterface.h"

ModelMapRepository*	ModelMapRepository::Instance = nullptr;

ModelMapRepository* ModelMapRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new ModelMapRepository;
	return Instance;
}

void ModelMapRepository::Release()
{

}

const QVector< QVector<ModelMapItem*> >* ModelMapRepository::GetMapItems() const
{
	return MapItems;
}

void ModelMapRepository::SetModelMapItems( const QVector< QVector<ModelMapItem*>>* mapItems)
{
	delete MapItems;
	MapItems = nullptr;
	MapItems = mapItems;
	UpdateIdToModelMapItem();
}

void ModelMapRepository::UpdateIdToModelMapItem()
{
	IdToModelMapItem.clear();
	int rows = GetRows();
	int cols = GetCols();
	for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
	{
		for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
		{
			QVector<ModelMapItem*> row = MapItems->at(currentRow);
			IdToModelMapItem.insert( row.at(currentCol)->GetId(), row.at(currentCol) );
		}
	}
}

ModelMapRepository::ModelMapRepository()
	: MapItems(nullptr)
{
}

ModelMapRepository::~ModelMapRepository()
{
	delete MapItems;
}

int ModelMapRepository::GetCols() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	QVector<ModelMapItem*> firstRow = MapItems->at(0);
	if( true == firstRow.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}

	return firstRow.size();
}

int ModelMapRepository::GetRows() const
{
	if( nullptr == MapItems )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Map not initialized! ->SetMapItems()" ) );
		return 0;
	}
	return MapItems->size();
}

ModelMapItem* ModelMapRepository::GetModelMapItem( unsigned int row, unsigned int col)
{
	int rowCount = GetRows();
	if( row > rowCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested row index %1 out of bounds: %2" ).arg(row).arg(rowCount) );
		return nullptr;
	}

	QVector<ModelMapItem*> concreteRow = MapItems->at(row);

	int colCount = GetCols();
	if( col > colCount )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested column index %1 out of bounds: %2" ).arg(col).arg(colCount) );
		return nullptr;
	}
	return concreteRow.at(col);
}

int ModelMapRepository::GetModelMapItemId( unsigned int row, unsigned int col)
{
	const ModelMapItem* found = GetModelMapItem(row,col);
	if( nullptr == found )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Requested map item not found: column|row: %1|%2" ).arg(col).arg(row) );
		return -1;
	}
	return found->GetId();
}

bool ModelMapRepository::UpdateItem( const ModelMapItem* ItemToUpdate )
{
	jha::GetLog()->Log_DEBUG( QObject::tr("Not yet implemented!") );
	return false;
}

ModelMapItem* ModelMapRepository::GetModelMapItemById(unsigned int id)
{
	return nullptr;
}
