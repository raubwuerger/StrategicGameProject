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
	void CheckForHiResTerrain(QString& pictureName);
	/** */
	bool AttacheImage( ModelTerrainType* type );
};

#endif // MODELTERRAINTYPEFACTORY_H
