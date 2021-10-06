#ifndef GAMECITYFACTORY_H
#define GAMECITYFACTORY_H

class QDomNode;
class GameCity;
class GameOwner;
class ModelCityType;
class GameMapTile;
class GameUnitProduction;

struct GameCityParameterObject
{
	GameCityParameterObject()
		: Id(-1),
		ModelCityTypeId(-1),
		GameMapTileId(-1),
		GameOwnerId(-1),
		ModelCityTypeObject(nullptr),
		GameMapTileObject(nullptr),
		GameOwnerObject(nullptr),
		GameCityObject(nullptr)
	{
	}
	int	Id;
	int ModelCityTypeId;
	int GameMapTileId;
	int GameOwnerId;
	const ModelCityType*	ModelCityTypeObject;
	const GameMapTile*		GameMapTileObject;
	const GameOwner*	GameOwnerObject;
	GameCity*			GameCityObject;
};

/** Creates game map representation */
class GameCityFactory
{
public:
	/** */
	GameCityFactory();
	/** */
	~GameCityFactory();
	/** */
	bool Create();
	//TODO: Sollte kein GameCity-Objekt zurück geben. Wird aktuell vom Editor verwendet! 
	/** */
	GameCity* Create(const GameCityParameterObject gameCityParameterObject);
	/** */
	bool Create( const QDomNode node );
private:
	/** */
	bool Validate(const GameCityParameterObject obj);
	/** */
	bool CreateGameCities(const QDomNode& city);
	/** */
	GameCity* CreateGameCityFromXML(const QDomNode& city);
	/** */
	GameUnitProduction* CreateGameUnitProduction(const QDomNode& domNode, int gameCityId);
	/** */
	int CreateId(const GameCityParameterObject obj);
	/** */
	const ModelCityType* GetModelCityType(const GameCityParameterObject obj) const;
	/** */
	const GameOwner* GetGameOwner(const GameCityParameterObject obj) const;
	/** */
	const GameMapTile* GetGameMapTile(const GameCityParameterObject obj) const;
	/** */
	QString	CreateCityName( int cityId ) const;
	/** */
	int GetBaseEfficency(int cityId) const;
	/** */
	int GetBaseStrength(int cityId) const;
	/** */
	GameUnitProduction* CreateGameUnitProductionDefault(int gameCityId);

private:
	const QString	DefaultCityName;
};

#endif  //GAMECITYFACTORY_H
