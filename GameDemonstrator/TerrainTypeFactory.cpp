#include "stdafx.h"
#include "TerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "TerrainType.h"

CTerrainTypeFactory::CTerrainTypeFactory()
{
}

CTerrainTypeFactory::~CTerrainTypeFactory()
{
}

CTerrainType* CTerrainTypeFactory::CreateTerrainTypeFromXML( const QDomNode& node )
{
	if( node.attributes().contains("strId") == false )
	{
		jha::GetLog()->Log("Attribute strId missing",LEVEL::LL_WARNING);
		return nullptr;
	}

	CTerrainType *newTerrainType = new CTerrainType( node.attributes().namedItem("strId").nodeValue().toInt() );

	CDomElementFinder finder(node);
	finder.TryFindElement( "Oil", newTerrainType->m_Oil );
	finder.TryFindElement( "Timber", newTerrainType->m_Timber );
	finder.TryFindElement( "Infrastructure", newTerrainType->m_Infrastructure );
	finder.TryFindElement( "MovementModifier", newTerrainType->m_MovementModifier );
	finder.TryFindElement( "DefenseModifier", newTerrainType->m_DefenseModifier );
	finder.TryFindElement( "Name", newTerrainType->m_Name );
	finder.TryFindElement( "PicturePath", newTerrainType->m_PicturePath );

	return newTerrainType;
}


/************************************************************************/
/* CDomElementFinder                                                    */
/************************************************************************/
CDomElementFinder::CDomElementFinder( const QDomNode& node ) 
	: theNode(node)
{

}

void CDomElementFinder::TryFindElement( const QString& elementName, int& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	return;	value = element.text().toInt();
}

void CDomElementFinder::TryFindElement( const QString& elementName, QString& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text();
}

bool CDomElementFinder::ValidateNode( const QString& elementName, QDomElement& element ) const
{
	element = theNode.firstChildElement(elementName);
	if( element.isNull() == true )
	{
		jha::GetLog()->Log("Element missing: " +elementName, LEVEL::LL_WARNING );
		return false;
	}
	return true;
}
