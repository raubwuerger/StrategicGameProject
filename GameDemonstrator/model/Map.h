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
private:
	QVector< QVector<GDModel::CMapItem*> >	MapItems;
};


}
