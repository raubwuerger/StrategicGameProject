#include "stdafx.h"
#include "QActionRepository.h"

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
