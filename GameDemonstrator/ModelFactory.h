#pragma once

class CGameInitialisationData;

namespace GDModel
{

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

}