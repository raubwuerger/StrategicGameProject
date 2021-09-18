#include "stdafx.h"
#include "ModelMapTypeInterface.h"

ModelMapTypeInterface::ModelMapTypeInterface(int id) : Id(id)
{

}

const int ModelMapTypeInterface::GetId() const
{
	return Id;
}
