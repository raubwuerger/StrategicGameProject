#ifndef GAMECITYTYPE_H
#define GAMECITYTYPE_H

#include "GameObject.h"

class GameMapItem;
class GameOwnerItem;
class ModelCityType;
class GameCityItemRuntimeData;

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
	const GameOwnerItem* GetGameOwnerItem() const;
	/** */
	void SetGameOwnerItem(const GameOwnerItem* gameOwnerItem);
	/** */
	void SetGameOwnerItemId(int gameOwnerItemId);
	/** */
	int GetGameOwnerItemId() const;
	/** */
	const GameMapItem* GetGameMapItem() const;
	/** */
	int GetGameMapItemId() const;
	/** */
	const ModelCityType* GetCityModelType() const;
	/** */
	int GetModelCityTypeId() const;
	/** */
	int GetSpezializedUnitTypeId() const;
	/** */
	void UpdateTurn() const override;
	/** */
	bool Move() const override;
	/** */
	void Attacks() const override;
	/** */
	void Defends() const override;
	/** */
	int GetBaseStrength() const;
	/** */
	int GetCurrentStrength() const;
	/** */
	int GetBaseEfficiency() const;
	/** */
	int GetCurrentEfficiency() const;
	/** */
	bool InitRuntimeData();
	/** */
	GameCityItemRuntimeData* GetRuntimeData() { return RuntimeData; }

private:
	friend class GameCityItemFactory;
	const int				Id;
	int						CityTypeId;
	int						OwnerItemId;
	int						MapItemId;
	const ModelCityType*	CityType;
	const GameOwnerItem*	OwnerItem;
	const GameMapItem*		MapItem;
	QString					Name;
	int						SpezializedUnitTypeId;
	GameCityItemRuntimeData*RuntimeData;
};

#endif // GAMECITYTYPE_H
