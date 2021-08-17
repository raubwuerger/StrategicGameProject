#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

class ModelUnitType;
class GameMapItem;
class ModelOwnerType;

/** Game unit tile */
class GameUnitItem
{
public:
	/** */
	GameUnitItem( int gameUnitId );
	/** */
	~GameUnitItem();
	/** */
	const ModelUnitType* GetModelUnitType() const;
	/** */
	const ModelOwnerType* GetModelOwnerType() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnitItem& rhs) const;
	/** */
	void SetGameMapItemId(int gameMapUnitId);
	/** */
	int GetGameMapItemId() const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name);
private:
	friend class GameUnitItemFactory;
	const int				Id;
	int						GameMapItemId;
	const ModelUnitType*	UnitType;
	const ModelOwnerType*	OwnerType;
	QString					Name;
};

#endif // GAMEUNITTYPE_H
