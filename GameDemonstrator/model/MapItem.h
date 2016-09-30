#pragma once

class CTerrainType;
class COwnerType;

namespace GDModel
{
/** Kartenteil im Speicher */
class CMapItem
{
public:
	/** */
	CMapItem( int row, int col );
	/** */
	~CMapItem();
private:
	QPoint			CenterPoint;
	int				Row;
	int				Col;
	CTerrainType	*Type;
	COwnerType		*Owner;
};

}
