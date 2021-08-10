#ifndef MODELUNITTYPE_H
#define MODELUNITTYPE_H

class ModelUnitType;

/** Game unit tile */
class GameUnitItem
{
public:
	/** */
	GameUnitItem( int gameUnitId );
	/** */
	~GameUnitItem();
	/** */
	void SetModelUnitType( const ModelUnitType *type );
	/** */
	const ModelUnitType* GetModelUnitType() const;
	/** */
	const int GetId() const;
	/** */
	bool operator < (const GameUnitItem& rhs) const;
private:
	const int		Id;
	int				GameMapItemId;
	const ModelUnitType	*UnitType;
};

#endif // MODELUNITTYPE_H
