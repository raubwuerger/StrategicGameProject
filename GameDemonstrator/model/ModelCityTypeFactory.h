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
};

#endif // MODELOWNERTYPEFACTORY_H

