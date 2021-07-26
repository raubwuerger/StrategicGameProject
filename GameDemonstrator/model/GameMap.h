#pragma once

#include "MapItem.h"

namespace GDModel
{

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
	const QVector< QVector<GDModel::CMapItem*> >& GetMapItems() const;
private:
	QVector< QVector<GDModel::CMapItem*> >	MapItems;
	unsigned int Rows;
	unsigned int Cols;
};


}
