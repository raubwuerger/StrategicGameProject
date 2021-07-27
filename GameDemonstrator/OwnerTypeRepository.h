#pragma once

#include <QMap>
class COwnerType;

class COwnerTypeRepository
{
public:
	static COwnerTypeRepository* GetInstance();
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool RegisterOwnerType( COwnerType *ownerType  );
	/** */
	COwnerType* FindOwnerTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,COwnerType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,COwnerType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const COwnerType* GetDefaultOwnerType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultOwnerType( const COwnerType* val);
	/** */
	void Release();
private:
	/** */
	COwnerTypeRepository();
	/** */
	~COwnerTypeRepository();
private:
	QMap<int,COwnerType*>	OwnerTypes;
	const COwnerType*		DefaultOwnerType;
	static COwnerTypeRepository*	Instance;
};

