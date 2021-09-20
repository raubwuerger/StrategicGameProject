#include "stdafx.h"
#include "ConfigurationLoader.h"
#include "model/ModelTerrainTypeFactory.h"
#include "model/ModelOwnerTypeFactory.h"
#include "model/ModelUnitTypeFactory.h"
#include "model/ModelCityTypeFactory.h"
#include "model/ModelMapTypeCreatorFactoryAbstract.h"

bool ConfigurationLoader::Load()
{
	if (false == LoadTerrainTypes())
	{
		return false;
	}

	if (false == LoadOwnerTypes())
	{
		return false;
	}

	if (false == LoadUnitTypes())
	{
		return false;
	}

	if (false == LoadCityTypes())
	{
		return false;
	}

	return LoadMapTypes();
}

bool ConfigurationLoader::LoadTerrainTypes()
{
	ModelTerrainTypeFactory factory;
	return factory.Create();
}

bool ConfigurationLoader::LoadOwnerTypes()
{
	ModelOwnerTypeFactory factory;
	return factory.Create();
}

bool ConfigurationLoader::LoadUnitTypes()
{
	ModelUnitTypeFactory factory;
	return factory.Create();
}

bool ConfigurationLoader::LoadCityTypes()
{
	ModelCityTypeFactory factory;
	return factory.Create();
}

bool ConfigurationLoader::LoadMapTypes()
{
	ModelMapTypeCreatorFactoryAbstract factory;
	return factory.Create();
}

