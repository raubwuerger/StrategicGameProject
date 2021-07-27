#pragma once

#include <QMap>
class OwnerType;

class OwnerTypeRepository
{
public:
	static OwnerTypeRepository* GetInstance();
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool RegisterOwnerType( OwnerType *ownerType  );
	/** */
	OwnerType* FindOwnerTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,OwnerType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,OwnerType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const OwnerType* GetDefaultOwnerType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultOwnerType( const OwnerType* val);
	/** */
	void Release();
private:
	/** */
	OwnerTypeRepository();
	/** */
	~OwnerTypeRepository();
private:
	QMap<int,OwnerType*>	OwnerTypes;
	const OwnerType*		DefaultOwnerType;
	static OwnerTypeRepository*	Instance;
};

