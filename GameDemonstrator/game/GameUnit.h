#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

#include "GameObject.h"

class ModelUnitType;
class GameMapTile;
class GameOwner;
class GameUnitRuntimeData;

/** Game unit tile */
class GameUnit : public GameObject
{
public:
	/** */
	GameUnit( int gameUnitId );
	/** */
	~GameUnit();
	/** */
	const ModelUnitType* GetModelUnitType() const;
	/** */
	const GameOwner* GetGameOwner() const;
	/** */
	const GameMapTile* GetGameMapTile() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnit& rhs) const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name) const;
	/** */
	int GetModelUnitTypeId() const;
	/** */
	int GetModelOwnerTypeId() const;
	/** */
	int GetGameTileId() const;
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
	GameUnitRuntimeData* GetRuntimeData();
	/** */
	QString CreatStrengthString() const;
	/** */
	QString CreateMovementPointsString() const;
private:
	friend class GameUnitFactory;
	const int				Id;
	int						UnitTypeId;
	int						GameOwnerId;
	int						MapTileId;
	const ModelUnitType*	UnitType;
	const GameOwner*		GameOwnerObject;
	const GameMapTile*		GameMapTileObject;
	mutable QString			Name;
	GameUnitRuntimeData*RuntimeData;
};

#endif // GAMEUNITTYPE_H
