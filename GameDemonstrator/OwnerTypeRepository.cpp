#include "stdafx.h"
#include "OwnerTypeRepository.h"
#include "OwnerType.h"

OwnerTypeRepository* OwnerTypeRepository::Instance = nullptr;

OwnerTypeRepository* OwnerTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new OwnerTypeRepository;
	return Instance;
}

OwnerTypeRepository::OwnerTypeRepository()
	: DefaultOwnerType(nullptr)
{
}


OwnerTypeRepository::~OwnerTypeRepository()
{
	OwnerTypes.clear();
}

bool OwnerTypeRepository::RegisterOwnerType( OwnerType *ownerType )
{
	if( ownerType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	QMap<int,OwnerType*>::const_iterator allreadyExists = OwnerTypes.find(ownerType->GetId() );
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

OwnerType* OwnerTypeRepository::FindOwnerTypeById( int id )
{
	QMap<int,OwnerType*>::iterator exists = OwnerTypes.find( id );
	if( exists == OwnerTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int OwnerTypeRepository::GetCount() const
{
	return OwnerTypes.size();
}

QMap<int,OwnerType*>::const_iterator OwnerTypeRepository::GetFirstIterator() const
{
	return OwnerTypes.cbegin();
}

QMap<int,OwnerType*>::const_iterator OwnerTypeRepository::GetLastIterator() const
{
	return OwnerTypes.cend();
}

const OwnerType* OwnerTypeRepository::GetDefaultOwnerType() const
{
	return DefaultOwnerType;
}

void OwnerTypeRepository::SetDefaultOwnerType( const OwnerType* val )
{
	DefaultOwnerType = val;
}

void OwnerTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
