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
	const ModelMapItem* GetModelMapItem( const unsigned int row, const unsigned int col );
	/** */
	int GetModelMapItemId( const unsigned int row, const unsigned int col );
private:
	/** */
	ModelMapRepository();
	/** */
	~ModelMapRepository();
private:
	friend class ModelMapFactory;
	const QVector< QVector<ModelMapItem*> >*	MapItems;
	static ModelMapRepository* Instance;
};
