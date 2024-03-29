#ifndef MODELTERRAINTYPEREPOSITORY_H
#define MODELTERRAINTYPEREPOSITORY_H

#include "BaseRepository.h"
class ModelTerrainType;

class ModelTerrainTypeRepository
{
public:
	/** */
	static ModelTerrainTypeRepository* GetInstance();
	/** If no TerrainTypes are registered, the first will be set as DefaultTerrainType */
	bool Register( ModelTerrainType *terrainType  );
	/** */
	ModelTerrainType* GetById( int id );
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

#endif // MODELTERRAINTYPEREPOSITORY_H

