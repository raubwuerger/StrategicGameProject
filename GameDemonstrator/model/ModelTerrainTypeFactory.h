#ifndef ModelTerrainTypeFactory_H
#define ModelTerrainTypeFactory_H

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
	const QImage* LoadTerrainTypeImage( const QString& path );
	/** */
	bool AttacheImage( ModelTerrainType* modelTerrainType );
};

#endif
