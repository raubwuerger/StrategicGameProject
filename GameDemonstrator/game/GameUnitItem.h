#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

#include "GameObject.h"

class ModelUnitType;
class GameMapItem;
class GameOwnerItem;
class GameUnitItemRuntimeData;

/** Game unit tile */
class GameUnitItem : public GameObject
{
public:
	/** */
	GameUnitItem( int gameUnitId );
	/** */
	~GameUnitItem();
	/** */
	const ModelUnitType* GetModelUnitType() const;
	/** */
	const GameOwnerItem* GetGameOwnerItem() const;
	/** */
	const GameMapItem* GetGameMapItem() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnitItem& rhs) const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name) const;
	/** */
	int GetModelUnitTypeId() const;
	/** */
	int GetModelOwnerTypeId() const;
	/** */
	int GetGameMapItemId() const;
	/** */
	bool CanOccupieCity() const;
	/** */
	void UpdateTurn() const override;
	/** */
	bool CanMove() const;
	/** */
	bool Move() const override;
	/** */
	void Attacks() const override;
	/** */
	void Defends() const override;
	/** */
	int GetCurrentStrength() const;
	/** */
	int GetBaseStrength() const;
	/** */
	int GetCurrentMovementPoints() const;
	/** */
	int GetBaseMovementPoints() const;
	/** */
	bool InitRuntimeData();
	/** */
	GameUnitItemRuntimeData* GetRuntimeData();
	/** */
	QString CreatStrengthString() const;
	/** */
	QString CreateMovementPointsString() const;
private:
	friend class GameUnitItemFactory;
	const int				Id;
	int						UnitTypeId;
	int						OwnerItemId;
	int						MapItemId;
	const ModelUnitType*	UnitType;
	const GameOwnerItem*	OwnerItem;
	const GameMapItem*		MapItem;
	mutable QString			Name;
	GameUnitItemRuntimeData*RuntimeData;
};

#endif // GAMEUNITTYPE_H
