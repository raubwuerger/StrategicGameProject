#pragma once

#include "MapItem.h"

/** Repr�sentiert die Karte im Speicher */
class GameMapConfig
{
public:
	/** */
	static GameMapConfig* GetInstance();
	/** */
	void Release();
private:
	/** */
	GameMapConfig();
	/** */
	~GameMapConfig();
public:
	unsigned int Rows;
	unsigned int Cols;
private:
	static GameMapConfig* Instance;
};
