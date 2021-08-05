#ifndef ModelOwnerTypeFactory_H
#define ModelOwnerTypeFactory_H

class ModelOwnerType;
class ModelOwnerTypeRepository;
class QDomNode;

class ModelOwnerTypeFactory
{
public:
	static ModelOwnerTypeFactory* GetInstance();
	/** */
	bool Create();
private:
	/** */
	ModelOwnerTypeFactory();
	/** */
	~ModelOwnerTypeFactory();
	/** */
	bool OpenFile( QFile* file );
	/** */
	ModelOwnerType* CreateFromXML( const QDomNode& node );
private:
	ModelOwnerTypeRepository		*ModelOwnerTypeRepositoryInstance;
	static ModelOwnerTypeFactory	*Instance;
};

#endif

