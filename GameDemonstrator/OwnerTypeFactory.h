#pragma once

#include <QObject>
class OwnerType;
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
	OwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	OwnerTypeRepository	*OwnerTypeRepository;
};

