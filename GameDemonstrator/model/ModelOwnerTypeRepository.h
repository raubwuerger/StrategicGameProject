#ifndef MODELOWNERTYPEREPOSITORY_H
#define MODELOWNERTYPEREPOSITORY_H

#include "BaseRepository.h"
class ModelOwnerType;

class ModelOwnerTypeRepository
{
public:
	/** */
	static ModelOwnerTypeRepository* GetInstance();
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool Register( ModelOwnerType *ownerType  );
	/** */
	const ModelOwnerType* GetById( int id ) const;
	/** */
	int GetCount() const;
	/** */
	QMap<int,const ModelOwnerType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,const ModelOwnerType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const ModelOwnerType* GetDefaultOwnerType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultOwnerType( const ModelOwnerType* val);
private:
	/** */
	ModelOwnerTypeRepository();
	/** */
	~ModelOwnerTypeRepository();
private:
	QMap<int, const ModelOwnerType*>	OwnerTypes;
	const ModelOwnerType*		DefaultOwnerType;
	static ModelOwnerTypeRepository*	Instance;
};

#endif // MODELOWNERTYPEREPOSITORY_H

