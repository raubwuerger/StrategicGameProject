#pragma once

class ISerializeGameInterface
{
public:
	/** */
	virtual bool SaveGame() = 0;
	/** */
	virtual bool LoadGame() = 0;
};