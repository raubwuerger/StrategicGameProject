#pragma once

class CTerrainType;
class QDomNode;

class CTerrainTypeFactory
{
public:
	/** */
	CTerrainTypeFactory();
	/** */
	~CTerrainTypeFactory();
	/** */
	CTerrainType* CreateTerrainTypeFromXML( const QDomNode& node );
};

