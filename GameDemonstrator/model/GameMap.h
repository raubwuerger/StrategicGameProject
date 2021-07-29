#pragma once

#include "ModelMapItem.h"

/** Repr�sentiert die Karte im Speicher */
class ModelMapRepository
{
public:
	/** */
	ModelMapRepository();
	/** */
	~ModelMapRepository();
	/** */
	void Create();
	/** */
	void Init( int rows, int cols );
	/** */
	void Release();
	/** Get MapItems */	
	const QVector< QVector<ModelMapItem*> >& GetMapItems() const;
private:
	QVector< QVector<ModelMapItem*> >	MapItems;
	unsigned int Rows;
	unsigned int Cols;
};
