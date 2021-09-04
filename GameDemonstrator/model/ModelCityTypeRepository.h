#ifndef MODELCITYTYPEREPOSITORY_H
#define MODELCITYTYPEREPOSITORY_H

#include "BaseRepository.h"
class ModelCityType;

class ModelCityTypeRepository : public BaseRepository
{
public:
	/** */
	static ModelCityTypeRepository* GetInstance();
	/** */
	bool Init() override;
	/** If no OwnerTypes are registered, the first will be set as DefaultOwnerType */
	bool RegisterType( ModelCityType *type  );
	/** */
	const ModelCityType* GetTypeById( int id ) const;
	/** */
	int GetCount() const;
	/** */
	QMap<int,const ModelCityType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,const ModelCityType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const ModelCityType* GetDefaultType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultType( const ModelCityType* val);
	/** */
	virtual void Release();
private:
	/** */
	ModelCityTypeRepository();
	/** */
	~ModelCityTypeRepository();
private:
	QMap<int, const ModelCityType*>	Types;
	const ModelCityType*		DefaultType;
	static ModelCityTypeRepository*	Instance;
};

#endif // MODELCITYTYPEREPOSITORY_H

