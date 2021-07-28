#include "stdafx.h"
#include "ModelOwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "XMLTools.h"

ModelOwnerTypeFactory::ModelOwnerTypeFactory()
{
}

ModelOwnerTypeFactory::~ModelOwnerTypeFactory()
{
}

ModelOwnerType* ModelOwnerTypeFactory::CreateOwnerTypeFromXML( const QDomNode& node )
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
