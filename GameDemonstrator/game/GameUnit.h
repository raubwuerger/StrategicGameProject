#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

#include "GameObject.h"

class ModelUnitType;
class GameMapTile;
class GameOwner;
class GameUnitRuntimeData;
class GameUnitHelper;
class GameUnitTransportContainer;

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
	bool operator == (const GameUnit& rhs) const;
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
	/** */
	GameUnit* GetIsEmbarkedOn() const;
	/** */
	bool GetIsEmbarked() const;
	/** */
	void SetEmbarked(GameUnit* embarkedOn);
	/** */
	void SetDismbarked();
	/** */
	bool GetIsTransporter() const;
	/** */
	int GetCountTransportedUnits() const;
	/** */
	GameUnitTransportContainer* GetUnitTransportContainerNonConst();
	/** */
	GameUnitTransportContainer* GetUnitTransportContainer() const;
	/** */
	bool SetGameUnitTransportContainer(GameUnitTransportContainer* transportContainer);
	/** */
	const GameUnit* GetTransportedUnitAt(int index);
	/** */
	void DisembarkUnit( GameUnit* toDisembark);
private:
	friend class			GameUnitFactory;
	friend class			GameUnitHelper;
	const int				Id;
	int						UnitTypeId;
	int						GameOwnerId;
	int						MapTileId;
	const ModelUnitType*	UnitType;
	const GameOwner*		GameOwnerObject;
	const GameMapTile*		GameMapTileObject;
	mutable QString			Name;
	GameUnitRuntimeData*	RuntimeData;
	GameUnit*				IsEmbarkedOn;
	mutable bool			StartEmbarking;
	bool					IsTransportUnit;
	GameUnitTransportContainer*	UnitTransportContainer;
};

#endif // GAMEUNITTYPE_H
