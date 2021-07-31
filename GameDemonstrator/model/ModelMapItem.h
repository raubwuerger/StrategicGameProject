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
	/** */
	void SetModelTerrainType( const ModelTerrainType *type );
	/** */
	const ModelTerrainType* GetTerrainType() const;
private:
	QPoint			CenterPoint;
	const int		Row;
	const int		Col;
	const int		Id;
	const ModelTerrainType	*TerrainType;
	const ModelOwnerType	*OwnerType;
};
