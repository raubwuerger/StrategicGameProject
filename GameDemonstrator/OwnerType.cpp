#include "stdafx.h"
#include "OwnerType.h"

COwnerType::COwnerType( int id )
	: Id(id)
{
}


COwnerType::~COwnerType()
{
}

const QString& COwnerType::GetName() const
{
	return Name;
}

int COwnerType::GetId() const
{
	return Id;
}
