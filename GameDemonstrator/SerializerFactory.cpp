#include "stdafx.h"
#include "SerializerFactory.h"
#include "SaveBinary.h"
#include "SaveToXML.h"
#include "SerializerInterface.h"
#include "QObject.h"


CSerializerInterface* CSerializerFactory::Interfaces = nullptr;

CSerializerFactory::CSerializerFactory()
{
}

CSerializerFactory::~CSerializerFactory()
{
}

void CSerializerFactory::Release()
{
	delete Interfaces;
}

CSerializerInterface* CSerializerFactory::CreateInterface( QAction *action )
{
	Interfaces = new CSaveToXML;
	QObject::connect( action, SIGNAL(triggered()), Interfaces, SLOT(SerializeMap()) );

	return Interfaces;
}
