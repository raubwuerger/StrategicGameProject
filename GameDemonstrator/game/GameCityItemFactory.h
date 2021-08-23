#ifndef GAMECITYITEMFACTORY_H
#define GAMECITYITEMFACTORY_H

class QDomNode;
class GameCityItem;
class ModelOwnerType;
class ModelCityType;
class GameMapItem;

struct GameCityParameterObject
{
	GameCityParameterObject()
		: ModelCityTypeId(-1),
		GameMapItemId(-1),
		ModelOwnerTypeId(-1),
		ModelCityTypeObject(nullptr),
		GameMapItemObject(nullptr),
		ModelOwnerTypeObject(nullptr),
		GameCityItemObject(nullptr)
	{
	}
	int ModelCityTypeId;
	int GameMapItemId;
	int ModelOwnerTypeId;
	const ModelCityType*	ModelCityTypeObject;
	const GameMapItem*		GameMapItemObject;
	const ModelOwnerType*	ModelOwnerTypeObject;
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
	int CreateId();
	/** */
	const ModelCityType* GetModelCityType(const GameCityParameterObject obj) const;
	/** */
	const ModelOwnerType* GetModelOwnerType(const GameCityParameterObject obj) const;
	/** */
	const GameMapItem* GetGameMapItem(const GameCityParameterObject obj) const;
};

#endif  //GAMECITYITEMFACTORY_H
