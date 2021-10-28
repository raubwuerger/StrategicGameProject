#ifndef GAMEUNITFACTORY_H
#define GAMEUNITFACTORY_H

class QDomNode;
class GameUnit;
class ModelUnitType;
class GameOwner;
class GameMapTile;

struct GameUnitParameterObject
{
	GameUnitParameterObject()
		: Id(-1),
		ModelUnitTypeId(-1),
		GameMapTileId(-1),
		GameOwnerId(-1),
		ModelUnitTypeObject(nullptr),
		GameMapTileObject(nullptr),
		GameOwnerObject(nullptr),
		GameUnitObject(nullptr)
	{
	}
	int Id;
	int ModelUnitTypeId;
	int GameMapTileId;
	int GameOwnerId;
	const ModelUnitType*	ModelUnitTypeObject;
	const GameMapTile*		GameMapTileObject;
	const GameOwner*		GameOwnerObject;
	GameUnit*				GameUnitObject;
};

/** Creates game map representation */
class GameUnitFactory
{
public:
	/** */
	GameUnitFactory();
	/** */
	~GameUnitFactory();
	/** */
	bool Create();
	/** */
	GameUnit* Create(const GameUnitParameterObject obj);
	/** */
	GameUnit* Update(const GameUnitParameterObject obj);
	/** */
	GameUnit* Update(const GameUnitParameterObject* obj);
	/** */
	bool Create( const QDomNode node );
private:
	/** */
	bool Validate(const GameUnitParameterObject& obj) const;
	/** */
	const ModelUnitType* GetModelUnitType(const GameUnitParameterObject& obj) const;
	/** */
	const GameMapTile* GetGameMapTile(const GameUnitParameterObject& obj) const;
	/** */
	const GameOwner* GetGameOwner(const GameUnitParameterObject& obj) const;
	/** */
	bool CreateUnits(const QDomNode& units);
	/** */
	GameUnit* CreateUnitFromXML(const QDomNode& unit);
	/** */
	int CreateId( const GameUnitParameterObject obj);
	/** */
	QString CreateName(const ModelUnitType* modelUnitType) const;
};

#endif  //GAMEUNITFACTORY_H
