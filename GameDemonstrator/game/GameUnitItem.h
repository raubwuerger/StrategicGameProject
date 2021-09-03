#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

#include "GameObject.h"

class ModelUnitType;
class GameMapItem;
class ModelOwnerType;
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
	const ModelOwnerType* GetModelOwnerType() const;
	/** */
	const GameMapItem* GetGameMapItem() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnitItem& rhs) const;
	/** */
	const QString& GetName() const;
	/** */
	void SetName( const QString& name);
	/** */
	int GetModelUnitTypeId() const;
	/** */
	int GetModelOwnerTypeId() const;
	/** */
	int GetGameMapItemId() const;
	/** */
	bool CanOccupieCity() const;
	/** */
	void UpdateTurn() override;
	/** */
	bool CanMove() const;
	/** */
	bool Moved() override;
	/** */
	void Attacks() override;
	/** */
	void Defends() override;
	/** */
	int GetStrength() const;
	/** */
	bool InitRuntimeData();
	/** */
	GameUnitItemRuntimeData* GetRuntimeData() { return RuntimeData; }
private:
	friend class GameUnitItemFactory;
	const int				Id;
	int						UnitTypeId;
	int						OwnerTypeId;
	int						MapItemId;
	const ModelUnitType*	UnitType;
	const ModelOwnerType*	OwnerType;
	const GameMapItem*		MapItem;
	QString					Name;
	GameUnitItemRuntimeData*RuntimeData;
};

#endif // GAMEUNITTYPE_H
