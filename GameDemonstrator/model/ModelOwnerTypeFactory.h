#pragma once

#include <QObject>
class ModelOwnerType;
class ModelOwnerTypeRepository;
class QDomNode;

class ModelOwnerTypeFactory : public QObject
{
	Q_OBJECT
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
	ModelOwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	ModelOwnerTypeRepository		*ModelOwnerTypeRepositoryInstance;
	static ModelOwnerTypeFactory	*Instance;
};

