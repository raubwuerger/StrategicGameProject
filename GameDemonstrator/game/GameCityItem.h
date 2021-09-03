#ifndef GAMECITYTYPE_H
#define GAMECITYTYPE_H

#include "GameObject.h"

class GameMapItem;
class ModelOwnerType;
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
	const ModelOwnerType* GetModelOwnerType() const;
	/** */
	void SetModelOwnerType(const ModelOwnerType* modelOwnerType);
	/** */
	void SetModelOwnerTypeId(int modelOwnerTypeId);
	/** */
	int GetModelOwnerTypeId() const;
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
	void UpdateTurn() override;
	/** */
	bool Move() override;
	/** */
	void Attacks() override;
	/** */
	void Defends() override;
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
	int						OwnerTypeId;
	int						MapItemId;
	const ModelCityType*	CityType;
	const ModelOwnerType*	OwnerType;
	const GameMapItem*		MapItem;
	QString					Name;
	int						SpezializedUnitTypeId;
	GameCityItemRuntimeData*RuntimeData;
};

#endif // GAMECITYTYPE_H
