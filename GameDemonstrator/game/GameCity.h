#ifndef GAMECITYTYPE_H
#define GAMECITYTYPE_H

#include "GameObject.h"

class GameMapTile;
class GameOwner;
class ModelCityType;
class GameCityRuntimeData;
class GameUnitProduction;

/** Game unit tile */
class GameCity : public GameObject
{
public:
	/** */
	GameCity( int id );
	/** */
	~GameCity();
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameCity& rhs) const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name);
	/** */
	const GameOwner* GetGameOwner() const;
	/** */
	void SetGameOwner(const GameOwner* gameOwner);
	/** */
	void SetGameOwnerId(int gameOwnerId);
	/** */
	int GetGameOwnerId() const;
	/** */
	const GameMapTile* GetGameMapTile() const;
	/** */
	int GetGameMapTileId() const;
	/** */
	const ModelCityType* GetCityModelType() const;
	/** */
	int GetModelCityTypeId() const;
	/** */
	int GetSpezializedUnitTypeId() const;
	/** */
	bool HasSpezializedUnitType() const;
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
	GameCityRuntimeData* GetRuntimeData();
	/** */
	const GameUnitProduction* GetUnitProduction() const;
	/** */
	void SetGameUnitProduction(const GameUnitProduction* unitProduction);
private:
	/** */
	void ResetDefenceValue() const;
	/** */
	void UpdateUnitProduction() const;
private:
	friend class GameCityFactory;
	const int				Id;
	int						CityTypeId;
	int						GameOwnerId;
	int						GameMapTileId;
	const ModelCityType*	CityType;
	const GameOwner*		GameOwnerObject;
	const GameMapTile*		GameMapTileObject;
	QString					Name;
	int						SpezializedUnitTypeId;
	mutable GameCityRuntimeData*RuntimeData;
	const GameUnitProduction*	UnitProduction;
};

#endif // GAMECITYTYPE_H
