#pragma once

#include "ModelMapItem.h"

/** Repräsentiert die Karte im Speicher */
class ModelMapRepository
{
public:
	/** */
	static ModelMapRepository* GetInstance();
	/** */
	void Release();
	/** Get MapItems */	
	const QVector< QVector<ModelMapItem*> >* GetMapItems() const;
	/** */
	void SetMapItems( const QVector< QVector<ModelMapItem*>>* mapItems );
	/** */
	int GetCols() const;
	/** */
	int GetRows() const;
	/** */
	const ModelMapItem* GetModelMapItem( unsigned int row, unsigned int col );
	/** */
	int GetModelMapItemId( unsigned int row, unsigned int col );
	/** */
	bool UpdateItem( const ModelMapItem* ItemToUpdate );
private:
	/** */
	ModelMapRepository();
	/** */
	~ModelMapRepository();
private:
	friend class ModelMapFactory;
	mutable const QVector< QVector<ModelMapItem*> >*	MapItems;
	static ModelMapRepository* Instance;
};
