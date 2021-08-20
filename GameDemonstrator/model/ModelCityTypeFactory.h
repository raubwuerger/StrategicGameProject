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
	const QImage* LoadImage(const QString& path);
	/** */
	bool AttacheImage(ModelCityType* modelCityType);
};

#endif // MODELOWNERTYPEFACTORY_H

