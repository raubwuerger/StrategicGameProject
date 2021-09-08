#ifndef GAMEUNITITEMREPOSITORY_H
#define GAMEUNITITEMREPOSITORY_H

#include "BaseRepository.h"
class GameUnitItem;

/** Repräsentiert die Karte im Speicher */
class GameUnitItemRepository : public BaseRepository
{
public:
	/** */
	static GameUnitItemRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** */
	bool RegisterItem(GameUnitItem* gameUnitItem);
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
	int CreateNewId() const;
	/** */
	bool IsGameUnitItemOnGameMapItem(int gameMapItemId) const;
	/** */
	GameUnitItem* RemoveGameUnitItemByGameMapItemId(int gameMapItemId);
	/** */
	GameUnitItem* RemoveGameUnitItem(const GameUnitItem* gameUnitItem);
	/** */
	bool UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* movedUnitItem, int oldMapId);
private:
	/** */
	GameUnitItemRepository();
	/** */
	~GameUnitItemRepository();
	/** */
	bool UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* gameUnitItem);
	/** */
	int GenerateUID(const GameUnitItem* item);
public:
	const int						UID;
private:
	friend class GameUnitItemFactory;
	static GameUnitItemRepository*	Instance;
	QMap<int, GameUnitItem*>		GameUnitItems;
	QMap<int, int>					GameUnitItemsOnGameMapItem;
};

#endif // GAMEUNITITEMREPOSITORY_H
