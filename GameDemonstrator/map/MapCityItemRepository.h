#ifndef MAPCITYITEMREPOSITORY_H
#define MAPCITYITEMREPOSITORY_H

#include "BaseRepository.h"

class MapCityItem;

class MapCityItemRepository : public BaseRepository
{
public:
	/** */
	static MapCityItemRepository* GetInstance();
	/** */
	void Init();
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
	void Release() override;
private:
	/** */
	MapCityItemRepository();
	/** */
	~MapCityItemRepository();
private:
	QMap<int, MapCityItem*>			MapCityItems;
	static MapCityItemRepository*	Instance;
};

#endif // MAPCITYITEMREPOSITORY_H