#pragma once

#include "MapItem.h"

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
	const QVector< QVector<CMapItem*> >& GetMapItems() const;
private:
	QVector< QVector<CMapItem*> >	MapItems;
	unsigned int Rows;
	unsigned int Cols;
};
