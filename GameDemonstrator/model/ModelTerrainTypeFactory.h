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
	static ModelTerrainTypeFactory* GetInstance();
	/** */
	void Release();
	/** */
	bool Create();
private:
	/** */
	ModelTerrainTypeFactory();
	/** */
	~ModelTerrainTypeFactory();
	/** */
	bool OpenFile( QFile* file );
	/** */
	ModelTerrainType* CreateFromXML( const QDomNode& node );
	/** */
	const QImage* LoadTerrainTypeImage( const QString& path );
	/** */
	bool AttacheImage( ModelTerrainType* modelTerrainType );
private:
	/** */
	static ModelTerrainTypeFactory* Instance;
};

#endif
