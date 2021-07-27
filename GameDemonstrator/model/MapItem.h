#pragma once

class TerrainType;
class OwnerType;

/** Kartenteil im Speicher */
class MapItem
{
public:
	/** */
	MapItem( int row, int col );
	/** */
	~MapItem();
private:
	QPoint			CenterPoint;
	int				Row;
	int				Col;
	TerrainType	*Type;
	OwnerType		*Owner;
};
