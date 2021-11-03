#include "stdafx.h"
#include "ModelTerrainDomain.h"

std::map<std::string,int>	ModelTerrainDomain::TerrainDomains;

void ModelTerrainDomain::Init()
{
	TerrainDomains.insert(std::pair<std::string, int>("land",0));
	TerrainDomains.insert(std::pair<std::string, int>("air",1));
	TerrainDomains.insert(std::pair<std::string, int>("sea",2));
}

int ModelTerrainDomain::GetModelTerrainDomainByName(const std::string& terrainDomainName) const
{
	std::string lowerCase = ToLowerCase(terrainDomainName);
	if (TerrainDomains.find(lowerCase) == TerrainDomains.end())
	{
		return -1;
	}
	return TerrainDomains[lowerCase];
}

std::string ModelTerrainDomain::ToLowerCase(const std::string& stringToConvert) const
{
	std::string converted = stringToConvert;
	std::for_each(converted.begin(), converted.end(), [](char & c){	c = ::tolower(c);});
	return converted;
}

std::string ModelTerrainDomain::ToUpperCase(const std::string& stringToConvert) const
{
	std::string converted = stringToConvert;
	std::for_each(converted.begin(), converted.end(), [](char & c){	c = ::toupper(c);});
	return converted;
}
