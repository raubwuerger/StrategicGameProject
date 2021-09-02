#ifndef GAMEMAPITEM_H
#define GAMEMAPITEM_H

class ModelTerrainType;
class ModelOwnerType;
class GameMapItemFactory;

/** Game tile */
class GameMapItem
{
public:
	/** */
	GameMapItem( int row, int col, int id );
	/** */
	~GameMapItem();
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
	bool operator < (const GameMapItem& rhs) const;
	/** */
	void SetTerrainTypeObject(const ModelTerrainType* modelTerrainType);
private:
	friend class GameMapItemFactory;
	const int		Row;
	const int		Col;
	const int		Id;
	int				ModelTerrainTypeId;
	int				ModelOwnerTypeId;
	const ModelTerrainType*	TerrainTypeObject;
	const ModelOwnerType*	OwnerTypeObject;
};

#endif // GAMEMAPITEM_H
