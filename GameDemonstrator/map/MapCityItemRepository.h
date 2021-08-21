#ifndef MAPCITYITEMREPOSITORY_H
#define MAPCITYITEMREPOSITORY_H

class MapCityItem;

class MapCityItemRepository
{
public:
	/** */
	static MapCityItemRepository* GetInstance();
	/** */
	void Init();
	/** */
	QVector< QVector<MapCityItem*>>::const_iterator GetFirstIterator() const;
	/** */
	QVector< QVector<MapCityItem*>>::const_iterator GetLastIterator() const;
	/** */
	void SetMapCityItems(QVector< QVector<MapCityItem*> > MapCityItems);
	/** */
	const MapCityItem* GetMapCityItemById(int MapCityItemId) const;
	/** */
	MapCityItem* GetMapCityItemByIdNonConst(int MapCityItemId) const;
private:
	/** */
	MapCityItemRepository();
	/** */
	~MapCityItemRepository();
	/** */
	void CreateMapCityItemsById();
private:
	QVector< QVector<MapCityItem*> >	MapCityItems;
	QMap<int, MapCityItem*>				MapCityItemsById;
	static MapCityItemRepository*		Instance;
};

#endif // MAPCITYITEMREPOSITORY_H