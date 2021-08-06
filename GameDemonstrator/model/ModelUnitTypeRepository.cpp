#include "stdafx.h"
#include "ModelUnitTypeRepository.h"
#include "ModelUnitType.h"

ModelUnitTypeRepository* ModelUnitTypeRepository::Instance = nullptr;

ModelUnitTypeRepository* ModelUnitTypeRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new ModelUnitTypeRepository;
	return Instance;
}

void ModelUnitTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool ModelUnitTypeRepository::RegisterModelUnitType(const ModelUnitType* modelUnit)
{
	if (true == Repository.contains(modelUnit->GetId()))
	{
		return false;
	}

	Repository.insert(modelUnit->GetId(), modelUnit);
	return true;
}

int ModelUnitTypeRepository::GetCount() const
{
	return Repository.size();
}

ModelUnitTypeRepository::ModelUnitTypeRepository()
{
}

ModelUnitTypeRepository::~ModelUnitTypeRepository()
{
	Repository.clear();
}

