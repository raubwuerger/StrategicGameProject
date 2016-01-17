#include "stdafx.h"
#include "OwnerTypeRepository.h"
#include "OwnerType.h"

COwnerTypeRepository::COwnerTypeRepository()
	: m_DefaultOwnerType(nullptr)
{
}


COwnerTypeRepository::~COwnerTypeRepository()
{
}

bool COwnerTypeRepository::RegisterOwnerType( GDModel::COwnerType *ownerType )
{
	if( ownerType == nullptr )
	{
		Q_ASSERT(false);
		return false;
	}
	QMap<int,GDModel::COwnerType*>::const_iterator allreadyExists = m_OwnerTypes.find(ownerType->GetId() );
	if( allreadyExists != m_OwnerTypes.end() )
	{
		return false;
	}
	m_OwnerTypes.insert( ownerType->GetId(), ownerType );
	return true;
}

GDModel::COwnerType* COwnerTypeRepository::FindOwnerTypeById( int id )
{
	QMap<int,GDModel::COwnerType*>::iterator exists = m_OwnerTypes.find( id );
	if( exists == m_OwnerTypes.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int COwnerTypeRepository::GetCount() const
{
	return m_OwnerTypes.size();
}

QMap<int,GDModel::COwnerType*>::const_iterator COwnerTypeRepository::GetFirstIterator() const
{
	return m_OwnerTypes.cbegin();
}

QMap<int,GDModel::COwnerType*>::const_iterator COwnerTypeRepository::GetLastIterator() const
{
	return m_OwnerTypes.cend();
}

const GDModel::COwnerType* COwnerTypeRepository::GetDefaultOwnerType() const
{
	return m_DefaultOwnerType;
}

void COwnerTypeRepository::SetDefaultOwnerType( const GDModel::COwnerType* val )
{
	m_DefaultOwnerType = val;
}
