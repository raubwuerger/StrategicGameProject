#pragma once

#include <QMap>
namespace GDModel { class COwnerType; }

class COwnerTypeRepository
{
public:
	/** */
	COwnerTypeRepository();
	/** */
	~COwnerTypeRepository();
	/** */
	bool RegisterOwnerType( GDModel::COwnerType *ownerType  );
	/** */
	GDModel::COwnerType* FindOwnerTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,GDModel::COwnerType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,GDModel::COwnerType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const GDModel::COwnerType* GetDefaultOwnerType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultOwnerType( const GDModel::COwnerType* val);
private:
	QMap<int,GDModel::COwnerType*>	m_OwnerTypes;
	const GDModel::COwnerType*			m_DefaultOwnerType;
};

