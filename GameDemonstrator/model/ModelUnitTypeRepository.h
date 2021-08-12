#ifndef MODELUNITREPOSITORY_H
#define MODELUNITREPOSITORY_H

class ModelUnitType;

class ModelUnitTypeRepository
{
public:
	/** */
	static ModelUnitTypeRepository* GetInstance();
	/** */
	void Init();
	/** */
	void Release();
	/** */
	bool RegisterModelUnitType(const ModelUnitType* modelUnit);
	/** */
	int GetCount() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, const ModelUnitType*>::const_iterator GetLastIterator() const;
	/** */
	const ModelUnitType* FindModelUnitTypeById( int modelUnitTypeId ) const;
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
