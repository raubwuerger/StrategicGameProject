#pragma once

class TerrainType;
class ModelOwnerType;

/** Game tile */
class ModelMapItem
{
public:
	/** */
	ModelMapItem( int row, int col );
	/** */
	~ModelMapItem();
private:
	QPoint			CenterPoint;
	int				Row;
	int				Col;
	TerrainType		*Type;
	ModelOwnerType		*Owner;
};
