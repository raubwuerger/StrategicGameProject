#ifndef GAMECITYITEMREPOSITORY_H
#define GAMECITYITEMREPOSITORY_H

class GameCityItem;

/** Repr�sentiert die Karte im Speicher */
class GameCityItemRepository
{
public:
	/** */
	static GameCityItemRepository* GetInstance();
	/** */
	void Init();
	/** */
	void Release();
	/** */
	bool RegisterItem(GameCityItem* gameUnitItem);
	/** */
	int GetCount() const;
	/** */
	QMap<int, GameCityItem*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameCityItem*>::const_iterator GetLastIterator() const;
	/** */
	GameCityItem* GetGameCityItemById(int itemId);
	/** */
	const GameCityItem* GetGameUnitItemByGameMapItemId(int gameMapItemId);
	/** */
	int GetLastIndex() const;
private:
	/** */
	GameCityItemRepository();
	/** */
	~GameCityItemRepository();
	/** */
	bool UpdateGameCityItemsOnGameMapItem(const GameCityItem* gameUnitItem);
private:
	friend class GameCityItemFactory;
	static GameCityItemRepository*	Instance;
	QMap<int, GameCityItem*>		GameCityItems;
	QMap<int, int>					GameCityItemsOnGameMapItem;
};

#endif // GAMECITYITEMREPOSITORY_H