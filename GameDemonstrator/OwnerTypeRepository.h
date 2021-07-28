#pragma once

#include <QMap>
class ModelOwnerType;

class OwnerTypeRepository
{
public:
	static OwnerTypeRepository* GetInstance();
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool RegisterOwnerType( ModelOwnerType *ownerType  );
	/** */
	ModelOwnerType* FindOwnerTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,ModelOwnerType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,ModelOwnerType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const ModelOwnerType* GetDefaultOwnerType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultOwnerType( const ModelOwnerType* val);
	/** */
	void Release();
private:
	/** */
	OwnerTypeRepository();
	/** */
	~OwnerTypeRepository();
private:
	QMap<int,ModelOwnerType*>	OwnerTypes;
	const ModelOwnerType*		DefaultOwnerType;
	static OwnerTypeRepository*	Instance;
};

