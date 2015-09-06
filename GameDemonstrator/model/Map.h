#pragma once

namespace GDModel
{

#include "MapItem.h"

/** Repräsentiert die Karte im Speicher */
class CMap
{
public:
	CMap();
	~CMap();
private:
	QVector< QVector<GDModel::CMapItem*> >	MapItems;
};


}
