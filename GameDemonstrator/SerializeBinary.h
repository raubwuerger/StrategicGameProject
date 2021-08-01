#pragma once

#include "ISerializeGameInterface.h"

class SerializeBinary : public ISerializeGameInterface
{
public:
	/** */
	SerializeBinary();
	/** */
	~SerializeBinary();
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
};

