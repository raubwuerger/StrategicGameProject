#ifndef GAMECITYITEMFACTORY_H
#define GAMECITYITEMFACTORY_H

class QDomNode;
class GameCityItem;
class GameOwnerItem;
class ModelCityType;
class GameMapItem;
class GameUnitProduction;

struct GameCityParameterObject
{
	GameCityParameterObject()
		: Id(-1),
		ModelCityTypeId(-1),
		GameMapItemId(-1),
		GameOwnerItemId(-1),
		ModelCityTypeObject(nullptr),
		GameMapItemObject(nullptr),
		GameOwnerItemObject(nullptr),
		GameCityItemObject(nullptr)
	{
	}
	int	Id;
	int ModelCityTypeId;
	int GameMapItemId;
	int GameOwnerItemId;
	const ModelCityType*	ModelCityTypeObject;
	const GameMapItem*		GameMapItemObject;
	const GameOwnerItem*	GameOwnerItemObject;
	GameCityItem*			GameCityItemObject;
};

/** Creates game map representation */
class GameCityItemFactory
{
public:
	/** */
	GameCityItemFactory();
	/** */
	~GameCityItemFactory();
	/** */
	GameCityItem* Create(const GameCityParameterObject gameCityParameterObject);
	/** */
	bool Create( const QDomNode cityItemElements );
private:
	/** */
	bool Validate(const GameCityParameterObject obj);
	/** */
	bool CreateItems(const QDomNode& city);
	/** */
	GameCityItem* CreateItemFromXML(const QDomNode& city);
	/** */
	GameUnitProduction* CreateGameUnitProduction(const QDomNode& domNode, int gameCityId);
	/** */
	int CreateId(const GameCityParameterObject obj);
	/** */
	const ModelCityType* GetModelCityType(const GameCityParameterObject obj) const;
	/** */
	const GameOwnerItem* GetGameOwnerItem(const GameCityParameterObject obj) const;
	/** */
	const GameMapItem* GetGameMapItem(const GameCityParameterObject obj) const;
	/** */
	QString	CreateCityName( int cityId ) const;
	/** */
	int GetBaseEfficency(int cityId) const;
	/** */
	int GetBaseStrength(int cityId) const;
private:
	const QString	DefaultCityName;
};

#endif  //GAMECITYITEMFACTORY_H
