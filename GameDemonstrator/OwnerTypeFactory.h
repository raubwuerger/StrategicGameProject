#pragma once

#include <QObject>
class COwnerType;
class COwnerTypeRepository;
class QDomNode;

class COwnerTypeFactory : public QObject
{
	Q_OBJECT
public:
	/** */
	COwnerTypeFactory();
	/** */
	~COwnerTypeFactory();
	/** */
	COwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	COwnerTypeRepository	*OwnerTypeRepository;
};

