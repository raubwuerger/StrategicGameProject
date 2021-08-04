#pragma once

class ModelGameXMLItems;

class GameDemonstratorFactory
{
public:
	/** */
	static GameDemonstratorFactory* GetInstance();
	/** */
	void Release();
	/** */
	bool Create();
	/** */
	ModelGameXMLItems* GetConfig();
private:
	/** */
	GameDemonstratorFactory();
	/** */
	~GameDemonstratorFactory();
	/** */
	bool OpenFile( QFile* file );
private:
	static GameDemonstratorFactory* Instance;
	ModelGameXMLItems* GameDemonstratorConfigInstance;
	QString GameDemonstratorConfigName;
};