#pragma once

#include <QObject>
class ModelOwnerType;
class OwnerTypeRepository;
class QDomNode;

class OwnerTypeFactory : public QObject
{
	Q_OBJECT
public:
	/** */
	OwnerTypeFactory();
	/** */
	~OwnerTypeFactory();
	/** */
	ModelOwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	OwnerTypeRepository	*OwnerTypeRepository;
};

