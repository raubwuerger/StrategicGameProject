#ifndef GAMECITYTYPE_H
#define GAMECITYTYPE_H

#include "GameObject.h"

class GameMapItem;
class ModelOwnerType;
class ModelCityType;

/** Game unit tile */
class GameCityItem : public GameObject
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
	/** */
	const ModelCityType* GetCityType() const;
	/** */
	int GetCityTypeId() const;
	/** */
	void UpdateTurn() override;
private:
	friend class GameCityItemFactory;
	const int				Id;
	int						CityTypeId;
	int						OwnerTypeId;
	int						MapItemId;
	const ModelCityType*	CityType;
	const ModelOwnerType*	OwnerType;
	const GameMapItem*		MapItem;
	QString					Name;
	int						Efficiency;
	int						SpezializedUnitTypeId;
};

#endif // GAMECITYTYPE_H
