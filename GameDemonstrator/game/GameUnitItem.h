#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

class ModelUnitType;
class GameMapItem;

/** Game unit tile */
class GameUnitItem
{
public:
	/** */
	GameUnitItem( int gameUnitId );
	/** */
	~GameUnitItem();
	/** */
	void SetModelUnitType( const ModelUnitType *type );
	/** */
	const ModelUnitType* GetModelUnitType() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnitItem& rhs) const;
	/** */
	int GetGameMapItemId() const;
	/** */
	void SetGameMapItemId(int val);
private:
	const int		Id;
	int				GameMapItemId;
	const ModelUnitType	*UnitType;
};

#endif // GAMEUNITTYPE_H
