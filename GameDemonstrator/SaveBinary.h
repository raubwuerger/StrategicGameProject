#pragma once

#include "ISerializeGameInterface.h"

class CSaveBinary : public ISerializeGameInterface
{
public:
	/** */
	CSaveBinary();
	/** */
	~CSaveBinary();
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
};

