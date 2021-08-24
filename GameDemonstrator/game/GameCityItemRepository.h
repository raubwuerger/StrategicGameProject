#ifndef GAMECITYITEMREPOSITORY_H
#define GAMECITYITEMREPOSITORY_H

#include "BaseRepository.h"

class GameCityItem;

/** Repräsentiert die Karte im Speicher */
class GameCityItemRepository : public BaseRepository
{
public:
	/** */
	static GameCityItemRepository* GetInstance();
	/** */
	void Init();
	/** */
	void Release() override;
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
	GameCityItem* RemoveCityItemById(int cityItemId);
	/** */
	GameCityItem* RemoveCityItemByGameMapItemId(int mapItemId);
	/** */
	int CreateNewId() const;
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
