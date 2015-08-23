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

//================================================================================
class CDomElementFinder
{
public:
	/** */
	CDomElementFinder( const QDomNode& node );
	/** */
	void TryFindElement( const QString& elementName, int& value ) const;
	/** */
	void TryFindElement( const QString& elementName, QString& value ) const;
private:
	bool ValidateNode( const QString& elementName, QDomElement& element ) const;

private:
	const QDomNode& theNode;
};