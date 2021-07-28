#pragma once

class GameMapConfig;

/** This class holds all game objects */
class ModelDataOverall
{
public:
	/** */
	ModelDataOverall();
	/** */
	~ModelDataOverall();
	/** */
	void Init();
	/** */
	void Release();
public:
	GameMapConfig* GetGameMapConfig();
private:
};
