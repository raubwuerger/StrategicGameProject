#pragma once

class GameInitialisationData;

class GameMap;

class ModelFactory
{
public:
	/** */
	ModelFactory();
	/** */
	~ModelFactory();
	/** */
	void CreateEmptyMap( const GameInitialisationData& data, GameMap** gameMap );
	/** */
	void CreateEmptyMap( GameMap** gameMap );
};
