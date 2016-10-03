#include "stdafx.h"
#include "SerializerInterface.h"


CSerializerInterface::CSerializerInterface( QAction *action )
	: Action( new QAction(action) )
{
}


CSerializerInterface::~CSerializerInterface()
{
}

