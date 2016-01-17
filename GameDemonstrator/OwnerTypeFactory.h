#pragma once

#include <QObject>
namespace GDModel { class COwnerType; }
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
	GDModel::COwnerType* CreateOwnerTypeFromXML( const QDomNode& node );
private:
	COwnerTypeRepository	*m_OwnerTypeRepository;
};

