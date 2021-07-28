#pragma once

#include "MapItem.h"

/** Repr�sentiert die Karte im Speicher */
class ModelMapConfig
{
public:
	/** */
	static ModelMapConfig* GetInstance();
	/** */
	void Release();
private:
	/** */
	ModelMapConfig();
	/** */
	~ModelMapConfig();
public:
	unsigned int Rows;
	unsigned int Cols;
private:
	static ModelMapConfig* Instance;
};
