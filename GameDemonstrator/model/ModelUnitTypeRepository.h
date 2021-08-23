#ifndef MODELUNITREPOSITORY_H
#define MODELUNITREPOSITORY_H

#include "BaseRepository.h"

class ModelUnitType;

class ModelUnitTypeRepository : public BaseRepository
{
public:
	/** */
	static ModelUnitTypeRepository* GetInstance();
	/** */
	void Init();
	/** */
	void Release() override;
	/** */
	bool RegisterModelUnitType(const ModelUnitType* modelUnit);
	/** */
	int GetCount() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetLastIterator() const;
	/** */
	const ModelUnitType* GetModelUnitTypeById( int modelUnitTypeId ) const;
private:
	/** */
	ModelUnitTypeRepository();
	/** */
	~ModelUnitTypeRepository();
private:
	/** */
	QMap<int, const ModelUnitType*>	Repository;
	static ModelUnitTypeRepository* Instance;
};

#endif
