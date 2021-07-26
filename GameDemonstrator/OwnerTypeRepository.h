#pragma once

#include <QMap>
namespace GDModel { class COwnerType; }

class COwnerTypeRepository
{
public:
	static COwnerTypeRepository* GetInstance();
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
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
	/** */
	void Release();
private:
	/** */
	COwnerTypeRepository();
	/** */
	~COwnerTypeRepository();
private:
	QMap<int,GDModel::COwnerType*>	OwnerTypes;
	const GDModel::COwnerType*		DefaultOwnerType;
	static COwnerTypeRepository*	Instance;
};

