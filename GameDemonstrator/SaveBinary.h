#pragma once

#include "ISerializeGameInterface.h"

class SaveBinary : public ISerializeGameInterface
{
public:
	/** */
	SaveBinary();
	/** */
	~SaveBinary();
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
};

