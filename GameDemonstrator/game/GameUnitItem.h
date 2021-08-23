#ifndef GAMEUNITTYPE_H
#define GAMEUNITTYPE_H

#include "GameObject.h"

class ModelUnitType;
class GameMapItem;
class ModelOwnerType;

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
	void UpdateTurn() override;
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
};

#endif // GAMEUNITTYPE_H
