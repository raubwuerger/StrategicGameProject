#pragma once

class ModelTerrainXMLItems
{
public:
	ModelTerrainXMLItems();
private:
	friend class ModelTerrainTypeFactory;
	static QString ConfigFilePath;
	static QString Version;
	static QString VersionNumber;
	static QString RootName;
	static QString ElementName;
	static QString SubelementId;
	static QString SubelementName;
	static QString SubelementPicturePath;
	static QString SubelementInfrastructure;
	static QString SubelementOil;
	static QString SubelementTimber;
	static QString SubelementStone;
	static QString SubelementMovementModifier;
	static QString SubelementDefenseModifier;
	static QString SubelementAttackModifier;
};