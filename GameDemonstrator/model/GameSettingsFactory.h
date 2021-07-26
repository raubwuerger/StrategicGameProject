#pragma once

/** This class holds all game settings */

namespace GDModel
{

/** Repr�sentiert die Karte im Speicher */
class GameSettingsFactory
{
public:
	/** */
	GameSettingsFactory();
	/** */
	~GameSettingsFactory();
	/** */
	void Create();
	/** */
	void Release();
};


}
