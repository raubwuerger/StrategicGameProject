#pragma once

class ModelTerrainType;
class QDomNode;
class QDomElement;

//================================================================================
/** @stereotype factory*/
class ModelTerrainTypeFactory
{
public:
	/** */
	ModelTerrainTypeFactory();
	/** */
	~ModelTerrainTypeFactory();
	/** */
	ModelTerrainType* CreateTerrainTypeFromXML( const QDomNode& node );
private:
	const QImage* LoadTerrainTypeImage( const QString& path );
};
