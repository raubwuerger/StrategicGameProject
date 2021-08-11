#ifndef MAPHEXITEMREPOSITORY_H
#define MAPHEXITEMREPOSITORY_H

class MapHexItem;

class MapHexItemRepository
{
public:
	/** */
	static MapHexItemRepository* GetInstance();
	/** */
	bool RegisterMapHexItem(MapHexItem* mapHexItem);
	/** */
	QVector< QVector<MapHexItem*>>::const_iterator GetFirstIterator() const;
	/** */
	QVector< QVector<MapHexItem*>>::const_iterator GetLastIterator() const;
	/** */
	void SetMapHexItems(QVector< QVector<MapHexItem*> > mapHexItems);
	/** */
	MapHexItem* GetMapHexItemById(int mapHexItemId);
private:
	/** */
	MapHexItemRepository();
	/** */
	~MapHexItemRepository();
private:
	QVector< QVector<MapHexItem*> >	MapHexItems;
	static MapHexItemRepository* Instance;
};

#endif // MAPHEXITEMREPOSITORY_H