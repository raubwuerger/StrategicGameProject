#ifndef GAMEMAPFACTORY_H
#define GAMEMAPFACTORY_H

class QDomNode;
class ModelTerrainType;
class ModelOwnerType;
class GameMapTile;

struct GameMapParameterObject
{
	GameMapParameterObject()
		: Row(NOT_INITIALIZED_INT),
		Col(NOT_INITIALIZED_INT),
		Id(NOT_INITIALIZED_INT),
		ModelOwnerTypeId(NOT_INITIALIZED_INT),
		ModelTerrainTypeId(NOT_INITIALIZED_INT),
		TerrainType(nullptr),
		OwnerType(nullptr)
	{

	}
	int		Row;
	int		Col;
	int		Id;
	int		ModelTerrainTypeId;
	int		ModelOwnerTypeId;
	const ModelTerrainType*	TerrainType;
	const ModelOwnerType*	OwnerType;
};

/** Creates game map representation */
class GameMapTileFactory
{
public:
	/** */
	GameMapTileFactory();
	/** */
	~GameMapTileFactory();
	/** Creates Map */
	bool Create();
	/** Creates Map */
	bool Create(const QDomNode mapElements);
private:
	/** */
	bool Validate(const GameMapParameterObject& obj) const;
	/** */
	/** */
	bool InitializeMap(const QDomNode& settings);
	/** */
	const ModelTerrainType* GetModelTerrainType(const GameMapParameterObject& obj) const;
	/** */
	bool CreateGameMapTiles(const QDomNode& node);
	/** */
	GameMapTile* CreateGameMapTile(const QDomNode& node);
	/** */
};

#endif // GAMEMAPFACTORY_H
