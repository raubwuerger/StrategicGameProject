#ifndef MAPCITYITEMREPOSITORY_H
#define MAPCITYITEMREPOSITORY_H

#include "BaseRepository.h"

class MapCityItem;
class GameCity;
class MapView;

class MapCityItemRepository : public BaseRepository
{
public:
	/** */
	static MapCityItemRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** */
	QMap<int, MapCityItem*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, MapCityItem*>::const_iterator GetLastIterator() const;
	/** */
	bool Register(MapCityItem* mapCityItem);
	/** */
	void SetMapCityItems(QMap<int, MapCityItem*> mapCityItems);
	/** */
	const MapCityItem* GetMapCityItemById(int mapCityItemId) const;
	/** */
	MapCityItem* GetMapCityItemByIdNonConst(int mapCityItemId) const;
	/** */
	MapCityItem* RemoveById(int mapCityItemId);
	/** */
	bool UpdateMapCityItemOwner(const GameCity* gameCityItem);
private:
	/** */
	MapCityItemRepository();
	/** */
	~MapCityItemRepository();
private:
	friend class GameDemonstrator;
	QMap<int, MapCityItem*>			MapCityItems;
	static MapCityItemRepository*	Instance;
	static MapView*					MapViewInstance;
};

#endif // MAPCITYITEMREPOSITORY_H