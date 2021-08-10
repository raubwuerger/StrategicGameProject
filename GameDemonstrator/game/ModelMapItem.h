#ifndef ModelMapItem_H
#define ModelMapItem_H

class ModelTerrainType;
class ModelOwnerType;

/** Game tile */
class ModelMapItem
{
public:
	/** */
	ModelMapItem( int row, int col, int id );
	/** */
	~ModelMapItem();
	/** */
	void SetModelTerrainType( const ModelTerrainType *type );
	/** */
	const ModelTerrainType* GetTerrainType() const;
	/** */
	const int GetId() const;
	/** */
	const int GetRow() const;
	/** */
	const int GetCol() const;
	/** */
	bool operator < (const ModelMapItem& rhs) const;
private:
	QPoint			CenterPoint;
	const int		Row;
	const int		Col;
	const int		Id;
	const ModelTerrainType	*TerrainType;
	const ModelOwnerType	*OwnerType;
};

#endif
