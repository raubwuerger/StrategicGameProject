#include "stdafx.h"
#include "ModelMapTypeRepository.h"
#include "ModelMapType.h"
#include "LogInterface.h"

ModelMapTypeRepository* ModelMapTypeRepository::Instance = nullptr;


ModelMapTypeRepository* ModelMapTypeRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new ModelMapTypeRepository;
	return Instance;
}

bool ModelMapTypeRepository::Register(const ModelMapType* modelMapType)
{
	if (nullptr == modelMapType)
	{
		return false;
	}

	if (true == Repository.contains(modelMapType->GetId()))
	{
		return false;
	}

	Repository.insert(modelMapType->GetId(), modelMapType);
	return true;
}

int ModelMapTypeRepository::GetCount() const
{
	return Repository.size();
}

QMap<int, const ModelMapType*>::const_iterator ModelMapTypeRepository::GetFirstIterator() const
{
	return Repository.cbegin();
}

QMap<int, const ModelMapType*>::const_iterator ModelMapTypeRepository::GetLastIterator() const
{
	return Repository.cend();
}

const ModelMapType* ModelMapTypeRepository::GetById(int modelMapTypeId) const
{
	if (false == Repository.contains(modelMapTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelMapType with id %1 not registered!").arg(QString::number(modelMapTypeId)));
		return false;
	}
	return Repository[modelMapTypeId];
}
