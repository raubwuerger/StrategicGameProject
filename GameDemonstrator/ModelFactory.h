#pragma once

class GameMap;

class ModelFactory
{
public:
	/** */
	ModelFactory();
	/** */
	~ModelFactory();
	/** */
	void CreateEmptyMap( GameMap** gameMap );
};
