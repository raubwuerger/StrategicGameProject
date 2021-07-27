#pragma once

#include <QMap>
class TerrainType;
class TerrainTypeRepository
{
public:
	static TerrainTypeRepository* GetInstance();
	/** If no TerrainTypes are registered, the first will be set as DefaultTerrainType */
	bool RegisterTerrainType( TerrainType *terrainType  );
	/** */
	TerrainType* FindTerrainTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,TerrainType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,TerrainType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const TerrainType* GetDefaultTerrainType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultTerrainType( const TerrainType* val);
	/** */
	void Release();
private:
	/** */
	TerrainTypeRepository();
	/** */
	~TerrainTypeRepository();
private:
	QMap<int,TerrainType*>			TerrainTypes;
	const TerrainType*				DefaultTerrainType;
	static TerrainTypeRepository* Instance;
};

