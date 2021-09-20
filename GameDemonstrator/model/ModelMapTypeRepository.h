#ifndef MODELMAPTYPEREPOSITORY_H
#define MODELMAPTYPEREPOSITORY_H

class ModelMapType;

class ModelMapTypeRepository
{
public:
	/** */
	static ModelMapTypeRepository* GetInstance();
	/** */
	bool Register(const ModelMapType* modelMapType);
	/** */
	int GetCount() const;
	/** */
	QMap<int, const ModelMapType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, const ModelMapType*>::const_iterator GetLastIterator() const;
	/** */
	const ModelMapType* GetById(int modelMapTypeId) const;
private:
	/** */
	ModelMapTypeRepository() {}
	/** */
	~ModelMapTypeRepository() {}
private:
	static ModelMapTypeRepository* Instance;
	QMap<int, const ModelMapType*>	Repository;
};

#endif // MODELMAPTYPEREPOSITORY_H