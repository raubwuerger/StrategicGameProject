#pragma once

class ModelProgramXMLItems;

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
	ModelProgramXMLItems* GetConfig();
private:
	/** */
	ModelProgramFactory();
	/** */
	~ModelProgramFactory();
	/** */
	bool OpenFile( QFile* file );
private:
	static ModelProgramFactory* Instance;
	ModelProgramXMLItems* GameDemonstratorConfigInstance;
	QString GameDemonstratorConfigName;
};