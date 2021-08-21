#ifndef GAMECITYTYPE_H
#define GAMECITYTYPE_H

class GameMapItem;
class ModelOwnerType;

/** Game unit tile */
class GameCityItem
{
public:
	/** */
	GameCityItem( int id );
	/** */
	~GameCityItem();
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameCityItem& rhs) const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name);
	/** */
	const ModelOwnerType* GetModelOwnerType() const;
	/** */
	int GetModelOwnerTypeId() const;
	/** */
	const GameMapItem* GetGameMapItem() const;
	/** */
	int GetGameMapItemId() const;
private:
	friend class GameCityItemFactory;
	const int				Id;
	int						OwnerTypeId;
	int						MapItemId;
	const ModelOwnerType*	OwnerType;
	const GameMapItem*		MapItem;
	QString					Name;
	int						Efficiency;
	int						SpezializedUnitTypeId;
};

#endif // GAMECITYTYPE_H
