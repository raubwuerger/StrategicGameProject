#ifndef MODELUNIT_H
#define MODELUNIT_H

#include "ModelTerrainDomain.h"

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
	/** */
	bool GetCanOccupieCity() const;
	/** */
	int GetStrength() const { return Strength; }
	/** */
	int GetMovementPoints() const { return MovementPointsPerTurn; }
	/** */
	int GetProductionCost() const { return ProductionCost; }
	/** */
	int GetRange() const { return Range; }
	/** */
	bool GetReceiveCounterattack() const { return ReceiveCounterattack; }
	/** */
	const TerrainDomainEnum& GetTerrainDomain() const;
	/** */
	int GetTransportCapacityUnitsLand() const;
	/** */
	int GetTransportCapacityUnitsAir() const;
	/** */
	int GetTransportCapacityUnitsSea() const;
	/** */
	int GetTransportCapacityByTerrainDomain(const TerrainDomainEnum& terrainDomain) const;
	/** Stupid. Gets first transport capacity greater one. At the moment no problem because there are no transporter units which can load different domain type units! */
	int GetTransportCapacityStupid() const;
	/** */
	bool GetCanUnitBeTransported() const;
	/** Stupid. Gets first transport capacity domain greater one. At the moment no problem because there are no transporter units which can load different domain type units! */
	QString GetTransportDomainStupid() const;
	/** */
	bool IsTransporter() const;
	/** */
	int GetAttackValueByTerrainDomain(const QString& terrainDomain) const;
	/** */
	int GetDefenseValueByTerrainDomain(const QString& terrainDomain) const;
private:
	/** */
	TerrainDomainEnum GetDomainEnumFromString(const QString& terrainDomain) const;
private:
	friend class ModelUnitTypeFactory;
	const int			Id;
	QString				Name;
	QString				PictureName;
	const QImage		*Image;
	int					Strength;
	QVector<int>		AttackValues;
	QVector<int>		DefenseValues;
	int					Range;
	int					MovementPointsPerTurn;
	int					MovementPointsOverall;
	QVector<int>		AccessibleTerrainTypes;
	QVector<int>		AttackableUnitTypes;
	QVector<int>		RecognisableUnitTypes;
	QVector<int>		TransportCapacity;
	bool				CanOccupieCity;
	bool				ReceiveCounterattack;
	int					ProductionCost;
	TerrainDomainEnum	TerrainDomain;
	bool				CanUnitBeTransported;
};

#endif