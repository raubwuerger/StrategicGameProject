#ifndef GAMEUNITITEMREPOSITORY_H
#define GAMEUNITITEMREPOSITORY_H

#include "GameUnitItem.h"

/** Repräsentiert die Karte im Speicher */
class GameUnitItemRepository
{
public:
	/** */
	static GameUnitItemRepository* GetInstance();
	/** */
	void Release();
	/** */
	bool RegisterGameUnitItem(GameUnitItem* gameUnitItem);
	/** */
	int GetCount() const;
	/** */
	QMap<int, GameUnitItem*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameUnitItem*>::const_iterator GetLastIterator() const;
private:
	/** */
	GameUnitItemRepository();
	/** */
	~GameUnitItemRepository();
private:
	friend class GameUnitItemFactory;
	static GameUnitItemRepository*		Instance;
	QMap<int, GameUnitItem*>			GameUnitItems;
};

#endif // GAMEUNITITEMREPOSITORY_H
