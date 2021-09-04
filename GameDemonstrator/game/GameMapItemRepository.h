#ifndef GAMEMAPREPOSITORY_H
#define GAMEMAPREPOSITORY_H

#include "BaseRepository.h"

class GameMapItem;

/** Repräsentiert die Karte im Speicher */
class GameMapItemRepository : public BaseRepository
{
public:
	/** */
	static GameMapItemRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** Get MapItems */	
	const QVector< QVector<GameMapItem*> >* GetMapItems() const;
	/** */
	void SetGameMapItems( QVector< QVector<GameMapItem*>>* mapItems );
	/** */
	int GetCols() const;
	/** */
	int GetRows() const;
	/** */
	GameMapItem* GetGameMapItem( unsigned int row, unsigned int col );
	/** */
	int GetGameMapItemId( unsigned int row, unsigned int col );
	/** */
	bool UpdateGameMapItem( const GameMapItem* ItemToUpdate );
	/** */
	GameMapItem* GetGameMapItemById( unsigned int id );
private:
	/** */
	GameMapItemRepository();
	/** */
	~GameMapItemRepository();
	/** */
	void UpdateIdToModelMapItem();
private:
	friend class GameMapItemFactory;
	QVector< QVector<GameMapItem*> >*	MapItems;
	static GameMapItemRepository*		Instance;
	QMap<int, GameMapItem*>				IdToModelMapItem;
};

#endif // GAMEMAPREPOSITORY_H
