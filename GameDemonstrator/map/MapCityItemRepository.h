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
	void SetMapCityItems(QMap<int, MapCityItem*> mapCityItems);
	/** */
	const MapCityItem* GetMapCityItemById(int MapCityItemId) const;
	/** */
	MapCityItem* GetMapCityItemByIdNonConst(int MapCityItemId) const;
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