#ifndef GAMEMAPFACTORY_H
#define GAMEMAPFACTORY_H

class QDomNode;
class ModelTerrainType;
class ModelOwnerType;
class GameMapItem;

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
class GameMapItemFactory
{
public:
	/** */
	GameMapItemFactory();
	/** */
	~GameMapItemFactory();
	/** Creates Map */
	bool Create();
	/** Creates Map */
	bool CreateFromSaveGame(const QDomNode mapElements);
private:
	/** */
	bool Validate(const GameMapParameterObject& obj) const;
	/** */
	/** */
	bool InitializeMap(const QDomNode& settings);
	/** */
	const ModelTerrainType* GetModelTerrainType(const GameMapParameterObject& obj) const;
	/** */
	bool CreateGameMapItems(const QDomNode& mapItems);
	/** */
	GameMapItem* CreateGameMapItem(const QDomNode& node);
	/** */
};

#endif // GAMEMAPFACTORY_H
