#ifndef ModelTerrainTypeRepository_H
#define ModelTerrainTypeRepository_H

#include <QMap>
class ModelTerrainType;

class ModelTerrainTypeRepository
{
public:
	/** */
	static ModelTerrainTypeRepository* GetInstance();
	/** */
	void Init();
	/** If no TerrainTypes are registered, the first will be set as DefaultTerrainType */
	bool RegisterTerrainType( ModelTerrainType *terrainType  );
	/** */
	ModelTerrainType* FindTerrainTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,ModelTerrainType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,ModelTerrainType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const ModelTerrainType* GetDefaultTerrainType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultTerrainType( const ModelTerrainType* val);
	/** */
	void Release();
private:
	/** */
	ModelTerrainTypeRepository();
	/** */
	~ModelTerrainTypeRepository();
private:
	QMap<int,ModelTerrainType*>			TerrainTypes;
	const ModelTerrainType*				DefaultTerrainType;
	static ModelTerrainTypeRepository* Instance;
};

#endif

