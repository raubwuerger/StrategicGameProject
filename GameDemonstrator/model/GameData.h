#pragma once

class GameMapConfig;

/** This class holds all game objects */
class GameData
{
public:
	/** */
	GameData();
	/** */
	~GameData();
	/** */
	void Init();
	/** */
	void Release();
public:
	GameMapConfig* GetGameMapConfig();
private:
};
