#ifndef MODELMAPREPOSITORY_H
#define MODELMAPREPOSITORY_H

#include "GameMapItem.h"

/** Repräsentiert die Karte im Speicher */
class GameMapRepository
{
public:
	/** */
	static GameMapRepository* GetInstance();
	/** */
	void Release();
	/** Get MapItems */	
	const QVector< QVector<GameMapItem*> >* GetMapItems() const;
	/** */
	void SetGameMapItems( const QVector< QVector<GameMapItem*>>* mapItems );
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
	GameMapRepository();
	/** */
	~GameMapRepository();
	/** */
	void UpdateIdToModelMapItem();
private:
	friend class GameMapFactory;
	mutable const QVector< QVector<GameMapItem*> >*	MapItems;
	static GameMapRepository*						Instance;
	QMap<int, GameMapItem*>							IdToModelMapItem;
};

#endif // MODELMAPREPOSITORY_H
