#ifndef GAMEUNITITEMFACTORY_H
#define GAMEUNITITEMFACTORY_H

class QDomNode;
class GameUnitItem;
class ModelUnitType;
class ModelOwnerType;
class GameMapItem;

struct GameUnitParameterObject
{
	GameUnitParameterObject()
		: ModelUnitTypeId(-1),
		GameMapItemId(-1),
		ModelOwnerTypeId(-1),
		ModelUnitTypeObject(nullptr),
		GameMapItemObject(nullptr),
		ModelOwnerTypeObject(nullptr),
		GameUnitItemObject(nullptr)
	{
	}
	int ModelUnitTypeId;
	int GameMapItemId;
	int ModelOwnerTypeId;
	const ModelUnitType*	ModelUnitTypeObject;
	const GameMapItem*		GameMapItemObject;
	const ModelOwnerType*	ModelOwnerTypeObject;
	GameUnitItem*			GameUnitItemObject;
};

/** Creates game map representation */
class GameUnitItemFactory
{
public:
	/** */
	GameUnitItemFactory();
	/** */
	~GameUnitItemFactory();
	/** */
	GameUnitItem* CreateGameUnitItem(const GameUnitParameterObject obj);
	/** */
	GameUnitItem* UpdateGameUnitItem(const GameUnitParameterObject obj);
	/** */
	bool CreateGameUnitItemsFromSaveGame( const QDomNode unitItemElements );
private:
	/** */
	bool Validate(const GameUnitParameterObject& obj) const;
	/** */
	const ModelUnitType* GetModelUnitType(const GameUnitParameterObject& obj) const;
	/** */
	const GameMapItem* GetGameMapItem(const GameUnitParameterObject& obj) const;
	/** */
	const ModelOwnerType* GetModelOwnerType(const GameUnitParameterObject& obj) const;
	/** */
	bool CreateUnitItems(const QDomNode& units);
	//TODO: Sollte ein GameUnitParameterObject erstellen!
	/** */
	GameUnitItem* CreateUnitItemFromXML(const QDomNode& unit);
	/** */
	int CreateId();
	/** */
	QString CreateName(const ModelUnitType* modelUnitType) const;
};

#endif  //GAMEUNITITEMFACTORY_H
