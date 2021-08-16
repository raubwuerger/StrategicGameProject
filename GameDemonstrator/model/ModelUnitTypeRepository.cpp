#include "stdafx.h"
#include "ModelUnitTypeRepository.h"
#include "ModelUnitType.h"
#include "LogInterface.h"

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

void ModelUnitTypeRepository::Init()
{
	Repository.clear();
}

void ModelUnitTypeRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool ModelUnitTypeRepository::RegisterModelUnitType(const ModelUnitType* modelUnit)
{
	if (nullptr == modelUnit)
	{
		return false;
	}

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

QMap<int, const ModelUnitType*>::const_iterator ModelUnitTypeRepository::GetFirstIterator() const
{
	return Repository.cbegin();
}

QMap<int, const ModelUnitType*>::const_iterator ModelUnitTypeRepository::GetLastIterator() const
{
	return Repository.cend();
}

const ModelUnitType* ModelUnitTypeRepository::FindModelUnitTypeById(int modelUnitTypeId) const
{
	QMap<int, const ModelUnitType*>::const_iterator itemFound = Repository.constFind(modelUnitTypeId);
	if (Repository.cend() == itemFound)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("UnitType with id %1 not registered!").arg(modelUnitTypeId));
		return nullptr;
	}
	return itemFound.value();
}

ModelUnitTypeRepository::ModelUnitTypeRepository()
{
}

ModelUnitTypeRepository::~ModelUnitTypeRepository()
{
	Repository.clear();
}

