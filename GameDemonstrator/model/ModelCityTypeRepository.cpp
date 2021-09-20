#include "stdafx.h"
#include "ModelCityTypeRepository.h"
#include "ModelCityType.h"
#include "LogInterface.h"

ModelCityTypeRepository* ModelCityTypeRepository::Instance = nullptr;

ModelCityTypeRepository* ModelCityTypeRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelCityTypeRepository;
	return Instance;
}

ModelCityTypeRepository::ModelCityTypeRepository()
	: DefaultType(nullptr)
{
}

ModelCityTypeRepository::~ModelCityTypeRepository()
{
	Types.clear();
}

bool ModelCityTypeRepository::Register( ModelCityType *type )
{
	if( type == nullptr )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr( "ModelCityType must not be null!"));
		return false;
	}
	QMap<int,const ModelCityType*>::const_iterator allreadyExists = Types.find(type->GetId() );
	if( allreadyExists != Types.end() )
	{
		return false;
	}

	if( true == Types.isEmpty() )
	{
		SetDefaultType(type);
	}

	jha::GetLog()->Log_DEBUG( QObject::tr( "ModelCityType registered: ") +type->toString());
	//TODO: insert kann prinzipiell auch fehlschlagen. Falls ein type schon vorhanden ist
	Types.insert( type->GetId(), type );
	return true;
}

const ModelCityType* ModelCityTypeRepository::GetById( int id ) const
{
	QMap<int,const ModelCityType*>::const_iterator exists = Types.find( id );
	if( exists == Types.end() )
	{
		return nullptr;
	}
	return exists.value();
}

int ModelCityTypeRepository::GetCount() const
{
	return Types.size();
}

QMap<int,const ModelCityType*>::const_iterator ModelCityTypeRepository::GetFirstIterator() const
{
	return Types.cbegin();
}

QMap<int, const ModelCityType*>::const_iterator ModelCityTypeRepository::GetLastIterator() const
{
	return Types.cend();
}

const ModelCityType* ModelCityTypeRepository::GetDefaultType() const
{
	return DefaultType;
}

void ModelCityTypeRepository::SetDefaultType( const ModelCityType* val )
{
	DefaultType = val;
}
