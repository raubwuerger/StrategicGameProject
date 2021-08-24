#ifndef MODELCITYTYPEFACTORY_H
#define MODELCITYTYPEFACTORY_H

class ModelCityType;
class QDomNode;

class ModelCityTypeFactory
{
public:
	/** */
	ModelCityTypeFactory();
	/** */
	~ModelCityTypeFactory();
	/** */
	bool Create();
private:
	/** */
	ModelCityType* CreateFromXML( const QDomNode& node );
	/** */
	bool AttacheImage(ModelCityType* type);
	/** */
	bool ParsePlacableTerrainTypes(const QDomNode& domNode, QVector<int>& terrainTypes);
};

#endif // MODELOWNERTYPEFACTORY_H

