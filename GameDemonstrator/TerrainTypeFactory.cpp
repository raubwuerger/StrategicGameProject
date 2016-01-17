#include "stdafx.h"
#include "TerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "TerrainType.h"
#include "XMLTools.h"

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

	//TODO: Wo werden die ganzen globalen Strings definiert!?
	QString baseTerrainPicturePath("../GameDemonstrator/Resources/");
	QString terrainPicturePath(baseTerrainPicturePath);
	terrainPicturePath += newTerrainType->m_PicturePath;
	const QImage *terrainTypeImage = LoadTerrainTypeImage( terrainPicturePath );

	if( terrainTypeImage == nullptr )
	{
		jha::GetLog()->Log("Unable to load terrain image: " +terrainPicturePath ,LEVEL::LL_WARNING);
	}
	else
	{
		newTerrainType->SetImage( terrainTypeImage );
	}

	return newTerrainType;
}

const QImage* CTerrainTypeFactory::LoadTerrainTypeImage( const QString& path )
{
	QImage* newImage = new QImage;
	try
	{
		if( newImage->load( path ) == false )
		{
			delete newImage;
			return nullptr;
		}
		return newImage;
	}
	catch( ... )
	{
		delete newImage;
		return nullptr;
	}
	return newImage;
}

