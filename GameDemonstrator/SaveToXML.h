#pragma once

#include "ISerializeGameInterface.h"

class CSaveToXML : public ISerializeGameInterface
{
public:
/** */
	CSaveToXML();
/** */
	~CSaveToXML();
public:
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();

};

