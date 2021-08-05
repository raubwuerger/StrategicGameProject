#ifndef ModelMapRepository_H
#define ModelMapRepository_H

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
	void SetModelMapItems( const QVector< QVector<ModelMapItem*>>* mapItems );
	/** */
	int GetCols() const;
	/** */
	int GetRows() const;
	/** */
	ModelMapItem* GetModelMapItem( unsigned int row, unsigned int col );
	/** */
	int GetModelMapItemId( unsigned int row, unsigned int col );
	/** */
	bool UpdateItem( const ModelMapItem* ItemToUpdate );
	/** */
	ModelMapItem* GetModelMapItemById( unsigned int id );
private:
	/** */
	ModelMapRepository();
	/** */
	~ModelMapRepository();
	/** */
	void UpdateIdToModelMapItem();
private:
	friend class ModelMapFactory;
	mutable const QVector< QVector<ModelMapItem*> >*	MapItems;
	static ModelMapRepository*							Instance;
	QMap<int, ModelMapItem*>							IdToModelMapItem;
};

#endif
