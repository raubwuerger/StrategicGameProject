#include "stdafx.h"
#include "ModelUnitType.h"
#include "ModelUnitTypeXMLItems.h"
#include "ModelTerrainDomain.h"

ModelUnitType::ModelUnitType(int id)
	:Id(id),
	Name(NOT_INITIALIZED_STRING),
	PictureName(NOT_INITIALIZED_STRING),
	Image(nullptr),
	Strength(NOT_INITIALIZED_INT),
	Range(NOT_INITIALIZED_INT),
	MovementPointsPerTurn(NOT_INITIALIZED_INT),
	MovementPointsOverall(NOT_INITIALIZED_INT),
	CanOccupieCity(NOT_INITIALIZED_BOOL),
	ReceiveCounterattack(NOT_INITIALIZED_BOOL),
	ProductionCost(NOT_INITIALIZED_INT),
	TerrainDomain(NOT_INITIALIZED_STRING),
	CanUnitBeTransported(NOT_INITIALIZED_BOOL)
{
}

int ModelUnitType::GetId() const
{
	return Id;
}

void ModelUnitType::SetName(const QString& name)
{
	Name = name;
}

const QImage* ModelUnitType::GetImage() const
{
	return Image;
}

const QString& ModelUnitType::GetName() const
{
	return Name;
}

const QString& ModelUnitType::GetPictureName() const
{
	return PictureName;
}

bool ModelUnitType::IsTerrainTypeAccessible(int terrainTypeId) const
{
	return AccessibleTerrainTypes.contains(terrainTypeId);
}

bool ModelUnitType::IsUnitTypeRecognisable(int modelUnitTypeId) const
{
	return RecognisableUnitTypes.contains(modelUnitTypeId);
}

bool ModelUnitType::IsUnitTypeAttackable(int modelUnitTypeId) const
{
	return AttackableUnitTypes.contains(modelUnitTypeId);
}

bool ModelUnitType::GetCanOccupieCity() const
{
	return CanOccupieCity;
}

int ModelUnitType::GetTerrainDomain() const
{
	ModelTerrainDomain modelTerrainDomain;
	return  modelTerrainDomain.GetModelTerrainDomainByName(TerrainDomain.toStdString());
}

int ModelUnitType::GetTransportCapacityUnitsLand() const
{
	return TransportCapacity[0];
}

int ModelUnitType::GetTransportCapacityUnitsAir() const
{
	return TransportCapacity[1];
}

int ModelUnitType::GetTransportCapacityUnitsSea() const
{
	return TransportCapacity[2];
}

int ModelUnitType::GetTransportCapacityByTerrainDomain(const QString& terrainDomain) const
{
	if (terrainDomain == ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_LAND)
	{
		return GetTransportCapacityUnitsLand();
	}

	if (terrainDomain == ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_AIR)
	{
		return GetTransportCapacityUnitsAir();
	}

	if (terrainDomain == ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_SEA)
	{
		return GetTransportCapacityUnitsSea();
	}

	Q_ASSERT(false);
	return NOT_INITIALIZED_INT;
}

int ModelUnitType::GetTransportCapacityStupid() const
{
	for (int i = 0; i < TransportCapacity.size();i++)
	{
		int transportCapacity = TransportCapacity[i];
		if ( 0 >= transportCapacity)
		{
			continue;
		}
		return transportCapacity;
	}
	return NOT_INITIALIZED_INT;
}

bool ModelUnitType::GetCanUnitBeTransported() const
{
	return CanUnitBeTransported;
}
