#ifndef ModelMapItem_H
#define ModelMapItem_H

class ModelTerrainType;
class ModelOwnerType;

/** Game tile */
class GameMapItem
{
public:
	/** */
	GameMapItem( int row, int col, int id );
	/** */
	~GameMapItem();
	/** */
	void SetModelTerrainType( const ModelTerrainType *type );
	/** */
	const ModelTerrainType* GetTerrainType() const;
	/** */
	const int GetId() const;
	/** */
	const int GetRow() const;
	/** */
	const int GetCol() const;
	/** */
	bool operator < (const GameMapItem& rhs) const;
private:
	const int		Row;
	const int		Col;
	const int		Id;
	const ModelTerrainType	*TerrainType;
	const ModelOwnerType	*OwnerType;
};

#endif
