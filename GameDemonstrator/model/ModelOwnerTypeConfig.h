#pragma once

class ModelOwnerTypeConfig
{
public:
	ModelOwnerTypeConfig();
private:
	friend class ModelOwnerTypeFactory;
	static QString ConfigFilePath;
	static QString RootName;
	static QString ElementName;
	static QString SubelementId;
	static QString SubelementName;
	static QString SubelementPicturePath;
	static QString SubelementColor;
};