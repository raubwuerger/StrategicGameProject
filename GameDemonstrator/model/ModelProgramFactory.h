#pragma once

class ModelGameXMLItems;

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
	ModelGameXMLItems* GetConfig();
private:
	/** */
	ModelProgramFactory();
	/** */
	~ModelProgramFactory();
	/** */
	bool OpenFile( QFile* file );
private:
	static ModelProgramFactory* Instance;
	ModelGameXMLItems* GameDemonstratorConfigInstance;
	QString GameDemonstratorConfigName;
};