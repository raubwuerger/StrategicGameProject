#ifndef MAPUNITITEMREPOSITORY_H
#define MAPUNITITEMREPOSITORY_H

#include "BaseRepository.h"

class MapUnitItem;
class MapView;

class MapUnitItemRepository : BaseRepository
{
public:
	/** */
	static MapUnitItemRepository* GetInstance();
	/** */
	bool Init();
	/** */
	bool Register(MapUnitItem* mapUnitItem);
	/** Removes mapUnitItem from registry and from MapView */
	MapUnitItem* Remove(int gameUnitItemId);
	/** Removes mapUnitItem from registry and from MapView */
	MapUnitItem* RemoveFromMap(int gameUnitItemId);
	/** */
	void Release() override;
	/** */
	MapUnitItem* GetById(int id);
private:
	/** */
	MapUnitItemRepository();
	/** */
	~MapUnitItemRepository();
private:
	friend class GameDemonstrator;
	static MapUnitItemRepository*	Instance;
	static MapView*					MapViewInstance;
	QMap<int, MapUnitItem*>			MapUnitItems;
};

#endif // MAPUNITITEMREPOSITORY_H
