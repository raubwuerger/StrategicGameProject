#pragma once

#include <QObject>
class ModelOwnerType;
class OwnerTypeRepository;
class QDomNode;

class ModelOwnerTypeFactory : public QObject
{
	Q_OBJECT
public:
	/** */
	ModelOwnerTypeFactory();
	/** */
	~ModelOwnerTypeFactory();
	/** */
	ModelOwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	OwnerTypeRepository	*OwnerTypeRepository;
};

