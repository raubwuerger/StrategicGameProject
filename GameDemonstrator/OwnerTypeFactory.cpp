#include "stdafx.h"
#include "OwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "XMLTools.h"

OwnerTypeFactory::OwnerTypeFactory()
{
}

OwnerTypeFactory::~OwnerTypeFactory()
{
}

ModelOwnerType* OwnerTypeFactory::CreateOwnerTypeFromXML( const QDomNode& node )
{
	if( node.attributes().contains("strId") == false )
	{
		jha::GetLog()->Log("Attribute strId missing",LEVEL::LL_WARNING);
		return nullptr;
	}

	ModelOwnerType *newOwnerType = new ModelOwnerType( node.attributes().namedItem("strId").nodeValue().toInt() );

	DomElementFinder finder(node);
	finder.TryFindElement( "Name", newOwnerType->Name );
	finder.TryFindElement( "PicturePath", newOwnerType->PicturePath );
	finder.TryFindElement( "Color", newOwnerType->Color );

	return newOwnerType;
}
