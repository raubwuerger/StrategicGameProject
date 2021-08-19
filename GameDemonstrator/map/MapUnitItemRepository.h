#ifndef MAPUNITITEMREPOSITORY_H
#define MAPUNITITEMREPOSITORY_H

class MapUnitItem;
class MapView;

class MapUnitItemRepository
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
private:
	/** */
	MapUnitItemRepository();
	/** */
	~MapUnitItemRepository();
private:
	friend class GameDemonstrator;
	static MapUnitItemRepository*	Instance;
	static MapView*					MapViewInstance;
	QMap<int, MapUnitItem*> MapUnitItems;
};

#endif // MAPUNITITEMREPOSITORY_H
