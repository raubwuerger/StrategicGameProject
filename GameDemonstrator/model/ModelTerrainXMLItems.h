#pragma once

class ModelTerrainXMLItems
{
public:
	ModelTerrainXMLItems();
private:
	friend class ModelTerrainTypeFactory;
	const static QString CONFIG_FILE_NAME;
	const static QString Version;
	const static QString VersionNumber;
	const static QString ROOT_NAME;
	const static QString ELEMENT_NAME;
	const static QString SUBELEMENT_ID;
	const static QString SUBELEMENT_NAME;
	const static QString SUBELEMENT_PICTURENAME;
	const static QString SUBELEMENT_INFRASTRUCTURE;
	const static QString SUBELEMENT_OIL;
	const static QString SUBELEMENT_TIMBER;
	const static QString SUBELEMENT_STONE;
	const static QString SUBELEMENT_MOVEMENT_MODIFIER;
	const static QString SUBELEMENT_DEFENSE_MODIFIER;
	const static QString SUBELEMENT_ATTACK_MODIFIER;
};