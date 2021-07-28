#include "stdafx.h"
#include "ModelOwnerType.h"

ModelOwnerType::ModelOwnerType( int id )
	: Id(id)
{
}


ModelOwnerType::~ModelOwnerType()
{
}

const QString& ModelOwnerType::GetName() const
{
	return Name;
}

int ModelOwnerType::GetId() const
{
	return Id;
}
