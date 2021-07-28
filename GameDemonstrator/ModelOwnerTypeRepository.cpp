#include "stdafx.h"
#include "ModelOwnerTypeRepository.h"
#include "ModelOwnerType.h"

ModelOwnerTypeRepository* ModelOwnerTypeRepository::Instance = nullptr;

ModelOwnerTypeRepository* ModelOwnerTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelOwnerTypeRepository;
	return Instance;
}

ModelOwnerTypeRepository::ModelOwnerTypeRepository()
	: DefaultOwnerType(nullptr)
{
}


ModelOwnerTypeRepository::~ModelOwnerTypeRepository()
{
	OwnerTypes.clear();
}

bool ModelOwnerTypeRepository::RegisterOwnerType( ModelOwnerType *ownerType )
{
	if( ownerType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	QMap<int,ModelOwnerType*>::const_iterator allreadyExists = OwnerTypes.find(ownerType->GetId() );
	if( allreadyExists != OwnerTypes.end() )
	{
		return false;
	}

	if( true == OwnerTypes.isEmpty() )
	{
		SetDefaultOwnerType(ownerType);
	}

	OwnerTypes.insert( ownerType->GetId(), ownerType );
	return true;
}

ModelOwnerType* ModelOwnerTypeRepository::FindOwnerTypeById( int id )
{
	QMap<int,ModelOwnerType*>::iterator exists = OwnerTypes.find( id );
	if( exists == OwnerTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int ModelOwnerTypeRepository::GetCount() const
{
	return OwnerTypes.size();
}

QMap<int,ModelOwnerType*>::const_iterator ModelOwnerTypeRepository::GetFirstIterator() const
{
	return OwnerTypes.cbegin();
}

QMap<int,ModelOwnerType*>::const_iterator ModelOwnerTypeRepository::GetLastIterator() const
{
	return OwnerTypes.cend();
}

const ModelOwnerType* ModelOwnerTypeRepository::GetDefaultOwnerType() const
{
	return DefaultOwnerType;
}

void ModelOwnerTypeRepository::SetDefaultOwnerType( const ModelOwnerType* val )
{
	DefaultOwnerType = val;
}

void ModelOwnerTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
