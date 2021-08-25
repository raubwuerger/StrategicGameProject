#ifndef MODELUNIT_H
#define MODELUNIT_H

class ModelUnitType
{
public:
	/** */
	ModelUnitType(int id);
	/** */
	int GetId() const;
	/** */
	void SetName(const QString& name);
	/** */
	const QString& GetName() const;
	/** */
	const QImage* GetImage() const;
	/** */
	const QString& GetPictureName() const;
	/** */
	bool IsTerrainTypeAccessible(int terrainTypeId) const;
	/** */
	bool IsUnitTypeRecognisable(int modelUnitTypeId) const;
	/** */
	bool IsUnitTypeAttackable(int modelUnitTypeId) const;
private:
	friend class ModelUnitTypeFactory;
	const int		Id;
	QString			Name;
	QString			PictureName;
	const QImage	*Image;
	int				Strength;
	QVector<int>	AttackValues;
	QVector<int>	DefenseValues;
	int				Range;
	int				MovementPoints;
	QVector<int>	AccessibleTerrainTypes;
	QVector<int>	AttackableUnitTypes;
	QVector<int>	RecognisableUnitTypes;
	bool			CanOccupieCity;
	bool			GetCounterattack;
};

#endif