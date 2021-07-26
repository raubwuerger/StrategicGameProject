#pragma once

#include <QMap>
class CTerrainType;
class CTerrainTypeRepository
{
public:
	static CTerrainTypeRepository* GetInstance();
	/** */
	bool RegisterTerrainType( CTerrainType *terrainType  );
	/** */
	CTerrainType* FindTerrainTypeById( int id );
	/** */
	int GetCount() const;
	/** */
	QMap<int,CTerrainType*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int,CTerrainType*>::const_iterator GetLastIterator() const;
	/** Get m_DefaultTerrainType */
	const CTerrainType* GetDefaultTerrainType() const;
	/** Set m_DefaultTerrainType */
	void SetDefaultTerrainType( const CTerrainType* val);
	/** */
	void Release();
private:
	/** */
	CTerrainTypeRepository();
	/** */
	~CTerrainTypeRepository();
private:
	QMap<int,CTerrainType*>			TerrainTypes;
	const CTerrainType*				DefaultTerrainType;
	static CTerrainTypeRepository* Instance;
};

