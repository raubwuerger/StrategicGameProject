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
	TerrainDomain(TerrainDomainEnum::NOT_DEFINED),
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

const TerrainDomainEnum& ModelUnitType::GetTerrainDomain() const
{
	return TerrainDomain;
}

int ModelUnitType::GetTransportCapacityUnitsLand() const
{
	return TransportCapacity[static_cast<int>(TerrainDomainEnum::LAND)];
}

int ModelUnitType::GetTransportCapacityUnitsAir() const
{
	return TransportCapacity[static_cast<int>(TerrainDomainEnum::AIR)];
}

int ModelUnitType::GetTransportCapacityUnitsSea() const
{
	return TransportCapacity[static_cast<int>(TerrainDomainEnum::SEA)];
}

int ModelUnitType::GetTransportCapacityByTerrainDomain(const TerrainDomainEnum& terrainDomain) const
{
	return TransportCapacity[static_cast<int>(terrainDomain)];
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

QString ModelUnitType::GetTransportDomainStupid() const
{
	if (GetTransportCapacityUnitsLand() > 0)
	{
		return ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_LAND;
	}

	if (GetTransportCapacityUnitsAir() > 0)
	{
		return ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_AIR;
	}

	if (GetTransportCapacityUnitsSea() > 0)
	{
		return ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_SEA;
	}

	Q_ASSERT(false);
	return INVALID_TERRAIN_DOMAIN;
}

bool ModelUnitType::IsTransporter() const
{
	return GetTransportCapacityStupid() > 0;
}

int ModelUnitType::GetDefenseValueByTerrainDomain(const QString& terrainDomain) const
{
	return DefenseValues[static_cast<int>(ModelTerrainDomain::GetModelTerrainDomainByName(terrainDomain))];
}

int ModelUnitType::GetAttackValueByTerrainDomain(const QString& terrainDomain) const
{
	return AttackValues[static_cast<int>(ModelTerrainDomain::GetModelTerrainDomainByName(terrainDomain))];
}

TerrainDomainEnum ModelUnitType::GetDomainEnumFromString(const QString& terrainDomain) const
{
	ModelTerrainDomain modelTerrainDomain;
	return modelTerrainDomain.GetModelTerrainDomainByName(terrainDomain);
}
