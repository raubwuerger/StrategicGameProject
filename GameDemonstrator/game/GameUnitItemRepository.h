#ifndef GAMEUNITITEMREPOSITORY_H
#define GAMEUNITITEMREPOSITORY_H

//#include "GameUnitItem.h"
class GameUnitItem;

/** Repräsentiert die Karte im Speicher */
class GameUnitItemRepository
{
public:
	/** */
	static GameUnitItemRepository* GetInstance();
	/** */
	void Init();
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
	/** */
	GameUnitItem* GetGameUnitItemById(int gameUnitItemId);
	/** */
	const GameUnitItem* GetGameUnitItemByGameMapItemId(int gameMapItemId);
	/** */
	int GetLastIndex() const;
	/** */
	int GetGameUnitItemsCountByGameMapItemId(int gameMapItemId) const;
	/** */
	GameUnitItem* RemoveGameUnitItemByGameMapItemId(int gameMapItemId);
	/** */
	bool UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* movedUnitItem, int oldMapId);
private:
	/** */
	GameUnitItemRepository();
	/** */
	~GameUnitItemRepository();
	/** */
	bool UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* gameUnitItem);
private:
	friend class GameUnitItemFactory;
	static GameUnitItemRepository*	Instance;
	QMap<int, GameUnitItem*>		GameUnitItems;
	QMap<int, int>					GameUnitItemsOnGameMapItem;
};

#endif // GAMEUNITITEMREPOSITORY_H
