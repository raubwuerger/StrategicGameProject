#pragma once

#include "MapItem.h"

namespace GDModel
{

/** Repr�sentiert die Karte im Speicher */
class CMap
{
public:
	/** */
	CMap();
	/** */
	~CMap();
	/** */
	void Init( int rows, int cols );
	/** */
	void Release();
	/** Get MapItems */	
	const QVector< QVector<GDModel::CMapItem*> >& GetMapItems() const;
private:
	QVector< QVector<GDModel::CMapItem*> >	MapItems;
};


}
