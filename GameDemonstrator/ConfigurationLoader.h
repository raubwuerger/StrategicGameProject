#ifndef CONFIGURATIONLOADER_H
#define CONFIGURATIONLOADER_H

class ConfigurationLoader
{
public:
	/** Loads default configuration */
	bool Load();
private:
	/** */
	bool LoadTerrainTypes();
	/** */
	bool LoadOwnerTypes();
	/** */
	bool LoadUnitTypes();
	/** */
	bool LoadCityTypes();
};

#endif // CONFIGURATIONLOADER_H