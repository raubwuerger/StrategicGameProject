#ifndef MODELUNITREPOSITORY_H
#define MODELUNITREPOSITORY_H

#include "BaseRepository.h"

class ModelUnitType;

class ModelUnitTypeRepository
{
public:
	/** */
	static ModelUnitTypeRepository* GetInstance();
	/** */
	bool Register(const ModelUnitType* modelUnit);
	/** */
	int GetCount() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetLastIterator() const;
	/** */
	const ModelUnitType* GetById( int modelUnitTypeId ) const;
private:
	/** */
	ModelUnitTypeRepository();
	/** */
	~ModelUnitTypeRepository();
private:
	static ModelUnitTypeRepository* Instance;
	QMap<int, const ModelUnitType*>	Repository;
};

#endif
