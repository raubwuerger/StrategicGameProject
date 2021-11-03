#ifndef MODELTERRAINDOMAIN_H
#define MODELTERRAINDOMAIN_H

#include <map>

class ModelTerrainDomain
{
public:
	/** */
	void Init();
	/** */
	int GetModelTerrainDomainByName(const std::string& terrainDomainName) const;
private:
	/** */
	std::string ToLowerCase(const std::string& stringToConvert) const;
	/** */
	std::string ToUpperCase(const std::string& stringToConvert) const;
public:
	static std::map<std::string,int>	TerrainDomains;
};

#endif //MODELTERRAINDOMAIN_H