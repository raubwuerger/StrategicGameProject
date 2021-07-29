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
