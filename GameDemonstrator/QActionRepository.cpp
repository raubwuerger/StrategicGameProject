#include "stdafx.h"
#include "QActionRepository.h"

QActionRepository::QActionRepository(QObject *parent)
	: QObject(parent)
{

}

QActionRepository::~QActionRepository()
{
	while( m_Actions.isEmpty() == false )
	{
		delete m_Actions.takeFirst();
	}
}

void QActionRepository::AddAction( QAction* action )
{
	m_Actions.push_back( action );
}
