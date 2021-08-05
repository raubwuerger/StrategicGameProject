#include "stdafx.h"
#include "ActionRepository.h"

ActionRepository* ActionRepository::Instance = nullptr;

ActionRepository* ActionRepository::GetInstanceFirstTimeInit(QObject *parent)
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ActionRepository(parent);
	return Instance;
}

ActionRepository* ActionRepository::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	//TODO: Fehlermeldung da nicht initialisiert
	return nullptr;
}

ActionRepository::ActionRepository(QObject *parent)
	: QObject(parent)
{

}

ActionRepository::~ActionRepository()
{
	while( Actions.isEmpty() == false )
	{
		delete Actions.takeFirst();
	}
}

void ActionRepository::AddAction( QAction* action )
{
	Actions.push_back( action );
}

void ActionRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}
