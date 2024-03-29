#ifndef MAPHEXITEMREPOSITORY_H
#define MAPHEXITEMREPOSITORY_H

#include "BaseRepository.h"

class MapHexItem;

class MapHexItemRepository : public BaseRepository
{
public:
	/** */
	static MapHexItemRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	QVector< QVector<MapHexItem*>>::const_iterator GetFirstIterator() const;
	/** */
	QVector< QVector<MapHexItem*>>::const_iterator GetLastIterator() const;
	/** */
	void SetMapHexItems(QVector< QVector<MapHexItem*> > mapHexItems);
	/** */
	const MapHexItem* GetById(int mapHexItemId) const;
	/** */
	MapHexItem* GetByIdNonConst(int mapHexItemId) const;
	/** */
	MapHexItem* GetMapHexItemByRowCol(int row, int col);
	/** */
	void Release() override;
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