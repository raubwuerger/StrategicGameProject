#pragma once

class ModelProgramSettings;

class ModelProgramFactory
{
public:
	/** */
	static ModelProgramFactory* GetInstance();
	/** */
	void Release();
	/** */
	bool Create();
	/** */
	ModelProgramSettings* GetConfig();
private:
	/** */
	ModelProgramFactory();
	/** */
	~ModelProgramFactory();
	/** */
	bool OpenFile( QFile* file );
private:
	static ModelProgramFactory* Instance;
	ModelProgramSettings*		ModelProgramSettingsInstance;
};