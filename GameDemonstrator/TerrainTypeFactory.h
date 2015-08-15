#pragma once

class CTerrainType;
class QDomNode;
class QDomElement;

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