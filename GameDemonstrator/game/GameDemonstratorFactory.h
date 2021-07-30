#pragma once

class GameDemonstratorConfig;

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
	GameDemonstratorConfig* GetConfig();
private:
	/** */
	GameDemonstratorFactory();
	/** */
	~GameDemonstratorFactory();
	/** */
	bool OpenFile( QFile* file );
private:
	static GameDemonstratorFactory* Instance;
	GameDemonstratorConfig* GameDemonstratorConfigInstance;
	QString GameDemonstratorConfigName;
};