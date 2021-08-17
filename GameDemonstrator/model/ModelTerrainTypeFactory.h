#ifndef MODELTERRAINTYPEFACTORY_H
#define MODELTERRAINTYPEFACTORY_H

class ModelTerrainType;
class QDomNode;

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
	bool Create();
private:
	/** */
	ModelTerrainType* CreateFromXML( const QDomNode& node );
	/** */
	const QImage* LoadImage( const QString& path );
	/** */
	bool AttacheImage( ModelTerrainType* modelTerrainType );
};

#endif // MODELTERRAINTYPEFACTORY_H
