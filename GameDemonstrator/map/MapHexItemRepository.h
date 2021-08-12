#ifndef MAPHEXITEMREPOSITORY_H
#define MAPHEXITEMREPOSITORY_H

class MapHexItem;

class MapHexItemRepository
{
public:
	/** */
	static MapHexItemRepository* GetInstance();
	/** */
	void Init();
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
	/** */
	void CreateMapHexItemsById();
private:
	QVector< QVector<MapHexItem*> >	MapHexItems;
	QMap<int, MapHexItem*>			MapHexItemsById;
	static MapHexItemRepository*	Instance;
};

#endif // MAPHEXITEMREPOSITORY_H