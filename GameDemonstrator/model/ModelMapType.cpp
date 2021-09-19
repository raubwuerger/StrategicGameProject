#include "stdafx.h"
#include "ModelMapType.h"

ModelMapType::ModelMapType(const int id) : Id(id)
{

}

const int ModelMapType::GetId() const
{
	return Id;
}

const QString ModelMapType::GetName() const
{
	return Name;
}
