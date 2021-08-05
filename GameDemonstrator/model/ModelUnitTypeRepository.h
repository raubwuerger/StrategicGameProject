#ifndef MODELUNITREPOSITORY_H
#define MODELUNITREPOSITORY_H

class ModelUnitType;

class ModelUnitTypeRepository
{
public:
	/** */
	static ModelUnitTypeRepository* GetInstance();
	/** */
	void Release();
	/** */
	bool RegisterModelUnit(const ModelUnitType* modelUnit);
	/** */
	int GetCount() const;
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
