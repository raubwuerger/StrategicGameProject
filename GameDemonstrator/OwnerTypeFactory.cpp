#include "stdafx.h"
#include "OwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "OwnerType.h"
#include "XMLTools.h"

OwnerTypeFactory::OwnerTypeFactory()
{
}

OwnerTypeFactory::~OwnerTypeFactory()
{
}

OwnerType* OwnerTypeFactory::CreateOwnerTypeFromXML( const QDomNode& node )
{
	if( node.attributes().contains("strId") == false )
	{
		jha::GetLog()->Log("Attribute strId missing",LEVEL::LL_WARNING);
		return nullptr;
	}

	OwnerType *newOwnerType = new OwnerType( node.attributes().namedItem("strId").nodeValue().toInt() );

	DomElementFinder finder(node);
	finder.TryFindElement( "Name", newOwnerType->Name );
	finder.TryFindElement( "PicturePath", newOwnerType->PicturePath );
	finder.TryFindElement( "Color", newOwnerType->Color );

	return newOwnerType;
}
