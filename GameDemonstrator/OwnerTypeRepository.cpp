#include "stdafx.h"
#include "OwnerTypeRepository.h"
#include "OwnerType.h"

COwnerTypeRepository* COwnerTypeRepository::Instance = nullptr;

COwnerTypeRepository* COwnerTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new COwnerTypeRepository;
	return Instance;
}

COwnerTypeRepository::COwnerTypeRepository()
	: DefaultOwnerType(nullptr)
{
}


COwnerTypeRepository::~COwnerTypeRepository()
{
	OwnerTypes.clear();
}

bool COwnerTypeRepository::RegisterOwnerType( GDModel::COwnerType *ownerType )
{
	if( ownerType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	QMap<int,GDModel::COwnerType*>::const_iterator allreadyExists = OwnerTypes.find(ownerType->GetId() );
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

GDModel::COwnerType* COwnerTypeRepository::FindOwnerTypeById( int id )
{
	QMap<int,GDModel::COwnerType*>::iterator exists = OwnerTypes.find( id );
	if( exists == OwnerTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int COwnerTypeRepository::GetCount() const
{
	return OwnerTypes.size();
}

QMap<int,GDModel::COwnerType*>::const_iterator COwnerTypeRepository::GetFirstIterator() const
{
	return OwnerTypes.cbegin();
}

QMap<int,GDModel::COwnerType*>::const_iterator COwnerTypeRepository::GetLastIterator() const
{
	return OwnerTypes.cend();
}

const GDModel::COwnerType* COwnerTypeRepository::GetDefaultOwnerType() const
{
	return DefaultOwnerType;
}

void COwnerTypeRepository::SetDefaultOwnerType( const GDModel::COwnerType* val )
{
	DefaultOwnerType = val;
}

void COwnerTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
