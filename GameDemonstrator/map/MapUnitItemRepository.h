#ifndef  MAPUNITITEMREPOSITORY_H
#define MAPUNITITEMREPOSITORY_H

class MapUnitItem;

class MapUnitItemRepository
{
public:
	/** */
	static MapUnitItemRepository* GetInstance();
	/** */
	bool Init();
	/** */
	bool Register(MapUnitItem* mapUnitItem);
	/** */
	MapUnitItem* Remove(int gameUnitItemId);
private:
	/** */
	MapUnitItemRepository();
	/** */
	~MapUnitItemRepository();
private:
	static MapUnitItemRepository* Instance;
	QMap<int, MapUnitItem*> MapUnitItems;
};

#endif // MAPUNITITEMREPOSITORY_H
