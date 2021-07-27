#include "stdafx.h"
#include "OwnerType.h"

OwnerType::OwnerType( int id )
	: Id(id)
{
}


OwnerType::~OwnerType()
{
}

const QString& OwnerType::GetName() const
{
	return Name;
}

int OwnerType::GetId() const
{
	return Id;
}
