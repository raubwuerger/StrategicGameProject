#include "stdafx.h"
#include "ModelTerrainDomain.h"

QMap<QString, TerrainDomainEnum>	ModelTerrainDomain::TerrainDomains;

void ModelTerrainDomain::Init()
{
	TerrainDomains.insert("land",TerrainDomainEnum::LAND);
	TerrainDomains.insert("air", TerrainDomainEnum::AIR);
	TerrainDomains.insert("sea", TerrainDomainEnum::SEA);
}

TerrainDomainEnum ModelTerrainDomain::GetModelTerrainDomainByName(const QString& terrainDomainName)
{
	QString lower = terrainDomainName.toLower();
	if (TerrainDomains.find(lower) == TerrainDomains.end())
	{
		return TerrainDomainEnum::NOT_DEFINED;
	}
	return TerrainDomains.value(lower);
}

const QString ModelTerrainDomain::GetModelTerrainDomainByInt(TerrainDomainEnum domainInt)
{
	if (domainInt >= static_cast<TerrainDomainEnum>(TerrainDomains.size()) )
	{
		return INVALID_TERRAIN_DOMAIN;
	}
	return TerrainDomains.key(domainInt);
}