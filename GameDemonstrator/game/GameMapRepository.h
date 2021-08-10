#ifndef ModelMapRepository_H
#define ModelMapRepository_H

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
	void SetModelMapItems( const QVector< QVector<GameMapItem*>>* mapItems );
	/** */
	int GetCols() const;
	/** */
	int GetRows() const;
	/** */
	GameMapItem* GetModelMapItem( unsigned int row, unsigned int col );
	/** */
	int GetModelMapItemId( unsigned int row, unsigned int col );
	/** */
	bool UpdateItem( const GameMapItem* ItemToUpdate );
	/** */
	GameMapItem* GetModelMapItemById( unsigned int id );
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
	static GameMapRepository*							Instance;
	QMap<int, GameMapItem*>							IdToModelMapItem;
};

#endif
