#pragma once

class ModelTerrainType;
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
	ModelTerrainType		*Type;
	ModelOwnerType		*Owner;
};
