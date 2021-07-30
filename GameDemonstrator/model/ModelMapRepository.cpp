#include "stdafx.h"
#include "ModelMapRepository.h"
#include "ModelMapItem.h"

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

ModelMapRepository::ModelMapRepository()
{
}

ModelMapRepository::~ModelMapRepository()
{
}

const QVector< QVector<ModelMapItem*> >& ModelMapRepository::GetMapItems() const
{
	return MapItems;
}
