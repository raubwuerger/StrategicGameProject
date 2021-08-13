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
	int GetLastIndex() const;
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
