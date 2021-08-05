#ifndef ModelOwnerTypeFactory_H
#define ModelOwnerTypeFactory_H

class ModelOwnerType;
class ModelOwnerTypeRepository;
class QDomNode;

class ModelOwnerTypeFactory
{
public:
	/** */
	bool Create();
	/** */
	ModelOwnerTypeFactory();
	/** */
	~ModelOwnerTypeFactory();
private:
	/** */
	bool OpenFile( QFile* file );
	/** */
	ModelOwnerType* CreateFromXML( const QDomNode& node );
};

#endif

