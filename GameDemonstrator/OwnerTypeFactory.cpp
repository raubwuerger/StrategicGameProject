#include "stdafx.h"
#include "OwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "OwnerType.h"
#include "XMLTools.h"

COwnerTypeFactory::COwnerTypeFactory()
{
}

COwnerTypeFactory::~COwnerTypeFactory()
{
}

COwnerType* COwnerTypeFactory::CreateOwnerTypeFromXML( const QDomNode& node )
{
	if( node.attributes().contains("strId") == false )
	{
		jha::GetLog()->Log("Attribute strId missing",LEVEL::LL_WARNING);
		return nullptr;
	}

	COwnerType *newOwnerType = new COwnerType( node.attributes().namedItem("strId").nodeValue().toInt() );

	CDomElementFinder finder(node);
	finder.TryFindElement( "Name", newOwnerType->Name );
	finder.TryFindElement( "PicturePath", newOwnerType->PicturePath );
	finder.TryFindElement( "Color", newOwnerType->Color );

	return newOwnerType;
}
