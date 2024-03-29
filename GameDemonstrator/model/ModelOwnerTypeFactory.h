#ifndef MODELOWNERTYPEFACTORY_H
#define MODELOWNERTYPEFACTORY_H

class ModelOwnerType;
class ModelOwnerTypeRepository;
class QDomNode;

class ModelOwnerTypeFactory
{
public:
	/** */
	ModelOwnerTypeFactory();
	/** */
	~ModelOwnerTypeFactory();
	/** */
	bool Create();
private:
	/** */
	ModelOwnerType* CreateFromXML( const QDomNode& node );
	/** */
	bool AttacheImage(ModelOwnerType* type);
};

#endif // MODELOWNERTYPEFACTORY_H

