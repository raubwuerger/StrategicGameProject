#pragma once

class CTerrainType;
class QDomNode;
class QDomElement;

//================================================================================
/** @stereotype factory*/
class CTerrainTypeFactory
{
public:
	/** */
	CTerrainTypeFactory();
	/** */
	~CTerrainTypeFactory();
	/** */
	CTerrainType* CreateTerrainTypeFromXML( const QDomNode& node );
private:
	const QImage* LoadTerrainTypeImage( const QString& path );
};
