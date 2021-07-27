#pragma once

class CGameInitialisationData;

class GameMap;

class CModelFactory
{
public:
	/** */
	CModelFactory();
	/** */
	~CModelFactory();
	/** */
	void CreateEmptyMap( const CGameInitialisationData& data, GameMap** gameMap );
};
