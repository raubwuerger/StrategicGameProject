#pragma once

#include "ISerializeGameInterface.h"

class SaveToXML : public ISerializeGameInterface
{
public:
/** */
	SaveToXML();
/** */
	~SaveToXML();
public:
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();

};

