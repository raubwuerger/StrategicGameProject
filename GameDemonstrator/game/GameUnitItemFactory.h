#ifndef GAMEUNITITEMFACTORY_H
#define GAMEUNITITEMFACTORY_H

class QDomNode;
class GameUnitItem;
class ModelUnitType;
class GameOwnerItem;
class GameMapItem;

struct GameUnitParameterObject
{
	GameUnitParameterObject()
		: Id(-1),
		ModelUnitTypeId(-1),
		GameMapItemId(-1),
		GameOwnerItemId(-1),
		ModelUnitTypeObject(nullptr),
		GameMapItemObject(nullptr),
		GameOwnerItemObject(nullptr),
		GameUnitItemObject(nullptr)
	{
	}
	int Id;
	int ModelUnitTypeId;
	int GameMapItemId;
	int GameOwnerItemId;
	const ModelUnitType*	ModelUnitTypeObject;
	const GameMapItem*		GameMapItemObject;
	const GameOwnerItem*	GameOwnerItemObject;
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
	bool Init();
	/** */
	GameUnitItem* CreateGameUnitItem(const GameUnitParameterObject obj);
	/** */
	GameUnitItem* UpdateGameUnitItem(const GameUnitParameterObject obj);
	/** */
	bool Create( const QDomNode unitItemElements );
private:
	/** */
	bool Validate(const GameUnitParameterObject& obj) const;
	/** */
	const ModelUnitType* GetModelUnitType(const GameUnitParameterObject& obj) const;
	/** */
	const GameMapItem* GetGameMapItem(const GameUnitParameterObject& obj) const;
	/** */
	const GameOwnerItem* GetGameOwnerItem(const GameUnitParameterObject& obj) const;
	/** */
	bool CreateUnitItems(const QDomNode& units);
	/** */
	GameUnitItem* CreateUnitItemFromXML(const QDomNode& unit);
	/** */
	int CreateId( const GameUnitParameterObject obj);
	/** */
	QString CreateName(const ModelUnitType* modelUnitType) const;
};

#endif  //GAMEUNITITEMFACTORY_H
