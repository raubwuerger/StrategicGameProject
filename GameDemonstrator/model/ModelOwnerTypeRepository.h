#ifndef MODELOWNERTYPEREPOSITORY_H
#define MODELOWNERTYPEREPOSITORY_H

#include "BaseRepository.h"
class ModelOwnerType;

class ModelOwnerTypeRepository : public BaseRepository
{
public:
	/** */
	static ModelOwnerTypeRepository* GetInstance();
	/** */
	bool Init() override;
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool RegisterOwnerType( ModelOwnerType *ownerType  );
	/** */
	const ModelOwnerType* GetOwnerTypeById( int id ) const;
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
	/** */
	void Release() override;
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

