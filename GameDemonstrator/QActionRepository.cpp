#include "stdafx.h"
#include "QActionRepository.h"

QActionRepository* QActionRepository::Instance = nullptr;

QActionRepository* QActionRepository::GetInstanceFirstTimeInit(QObject *parent)
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new QActionRepository(parent);
	return Instance;
}

QActionRepository* QActionRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	//TODO: Fehlermeldung da nicht initialisiert
	return nullptr;
}

QActionRepository::QActionRepository(QObject *parent)
	: QObject(parent)
{

}

QActionRepository::~QActionRepository()
{
	while( Actions.isEmpty() == false )
	{
		delete Actions.takeFirst();
	}
}

void QActionRepository::AddAction( QAction* action )
{
	Actions.push_back( action );
}

void QActionRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
