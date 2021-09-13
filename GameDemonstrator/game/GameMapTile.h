#ifndef GAMEMAPTILE_H
#define GAMEMAPTILE_H

class ModelTerrainType;
class ModelOwnerType;
class GameMapTileFactory;

/** Game tile */
class GameMapTile
{
public:
	/** */
	GameMapTile( int row, int col, int id );
	/** */
	~GameMapTile();
	/** */
	const ModelTerrainType* GetTerrainType() const;
	/** */
	int GetModelTerrainTypeId() const;
	/** */
	const ModelOwnerType* GetOwnerType() const;
	/** */
	int GetModelOwnerTypeId() const;
	/** */
	const int GetId() const;
	/** */
	const int GetRow() const;
	/** */
	const int GetCol() const;
	/** */
	bool operator < (const GameMapTile& rhs) const;
	/** */
	void SetModelTerrainType(const ModelTerrainType* modelTerrainType);
	/** */
	void SetModelTerrainTypeId(int id);
private:
	friend class GameMapTileFactory;
	const int		Row;
	const int		Col;
	const int		Id;
	int				ModelTerrainTypeId;
	int				ModelOwnerTypeId;
	const ModelTerrainType*	TerrainTypeObject;
	const ModelOwnerType*	OwnerTypeObject;
};

#endif // GAMEMAPTILE_H
