#include "stdafx.h"
#include "TerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "TerrainType.h"
#include "XMLTools.h"

TerrainTypeFactory::TerrainTypeFactory()
{
}

TerrainTypeFactory::~TerrainTypeFactory()
{
}

TerrainType* TerrainTypeFactory::CreateTerrainTypeFromXML( const QDomNode& node )
{
	if( node.attributes().contains("strId") == false )
	{
		jha::GetLog()->Log("Attribute strId missing",LEVEL::LL_WARNING);
		return nullptr;
	}

	TerrainType *newTerrainType = new TerrainType( node.attributes().namedItem("strId").nodeValue().toInt() );

	DomElementFinder finder(node);
	finder.TryFindElement( "Oil", newTerrainType->Oil );
	finder.TryFindElement( "Timber", newTerrainType->Timber );
	finder.TryFindElement( "Infrastructure", newTerrainType->Infrastructure );
	finder.TryFindElement( "MovementModifier", newTerrainType->MovementModifier );
	finder.TryFindElement( "DefenseModifier", newTerrainType->DefenseModifier );
	finder.TryFindElement( "Name", newTerrainType->Name );
	finder.TryFindElement( "PicturePath", newTerrainType->PicturePath );

	//TODO: Wo werden die ganzen globalen Strings definiert!?
	QString baseTerrainPicturePath("../GameDemonstrator/Resources/");
	QString terrainPicturePath(baseTerrainPicturePath);
	terrainPicturePath += newTerrainType->PicturePath;
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

const QImage* TerrainTypeFactory::LoadTerrainTypeImage( const QString& path )
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

