#pragma once

class TerrainType;
class QDomNode;
class QDomElement;

//================================================================================
/** @stereotype factory*/
class TerrainTypeFactory
{
public:
	/** */
	TerrainTypeFactory();
	/** */
	~TerrainTypeFactory();
	/** */
	TerrainType* CreateTerrainTypeFromXML( const QDomNode& node );
private:
	const QImage* LoadTerrainTypeImage( const QString& path );
};
