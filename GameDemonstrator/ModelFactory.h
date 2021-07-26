#pragma once

namespace GDModel
{

class GameMap;
class CGameInitialisationData;

class CModelFactory
{
public:
	/** */
	CModelFactory();
	/** */
	~CModelFactory();
	/** */
	void CreateEmptyMap( const GDModel::CGameInitialisationData& data, GameMap** gameMap );
};

}