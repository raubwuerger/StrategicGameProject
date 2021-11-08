#ifndef MODELTERRAINDOMAIN_H
#define MODELTERRAINDOMAIN_H

#include <map>

enum class TerrainDomainEnum
{
	NOT_DEFINED = -1,
	LAND = 0,
	AIR = 1,
	SEA = 2
};

class ModelTerrainDomain
{
public:
	/** */
	void Init();
	/** */
	static TerrainDomainEnum GetModelTerrainDomainByName(const QString& terrainDomainName);
	/** */
	static const QString GetModelTerrainDomainByInt(TerrainDomainEnum domainInt);
public:
	static QMap<QString, TerrainDomainEnum>	TerrainDomains;
};

#endif //MODELTERRAINDOMAIN_H