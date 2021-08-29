#ifndef GAMEMAPITEM_H
#define GAMEMAPITEM_H

class ModelTerrainType;
class ModelOwnerType;
class IGameMapItemCreator;

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
	const ModelOwnerType* GetOwnerType() const;
	/** */
	const int GetId() const;
	/** */
	const int GetRow() const;
	/** */
	const int GetCol() const;
	/** */
	bool operator < (const GameMapItem& rhs) const;
	/** */
	int GetModelTerrainTypeId() const;
	/** */
	void SetModelTerrainTypeId(int modelTerrainTypeId);
private:
	friend class IGameMapItemCreator;
	const int		Row;
	const int		Col;
	const int		Id;
	int				ModelTerrainTypeId;
	const ModelTerrainType*	TerrainType;
	const ModelOwnerType*	OwnerType;
};

#endif // GAMEMAPITEM_H
