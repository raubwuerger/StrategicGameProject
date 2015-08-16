#pragma once

#include <QMap>
class CTerrainType;
class CTerrainTypeRepository
{
public:
	/** */
	CTerrainTypeRepository();
	/** */
	~CTerrainTypeRepository();
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
private:
	QMap<int,CTerrainType*>	m_TerrainTypes;
};

