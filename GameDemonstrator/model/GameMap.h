#pragma once

#include "ModelMapItem.h"

/** Repräsentiert die Karte im Speicher */
class GameMap
{
public:
	/** */
	GameMap();
	/** */
	~GameMap();
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
