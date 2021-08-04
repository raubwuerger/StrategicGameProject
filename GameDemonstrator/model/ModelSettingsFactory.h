#pragma once

class ModelSettings;
class QFile;

/** This class holds all game settings */
class ModelSettingsFactory
{
public:
	/** */
	static ModelSettingsFactory* GetInstance();
	/** */
	void Release();
	/** */
	ModelSettings* Create();
private:
	/** */
	ModelSettingsFactory();
	/** */
	~ModelSettingsFactory();
	/** */
	/** */
	bool OpenFile( QFile* file );
private:
	ModelSettings* TheGameSettings;
	static ModelSettingsFactory* Instance;
};
