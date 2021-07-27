#pragma once

class TerrainType;
class MapView;
class GameInitialisationData;
class GameMap;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class GameFactory
{
public:
	/** */
	GameFactory();
	/** */
	~GameFactory();
	/** */
	void CreateNewGame();
	/** */
	void CreateNewGame( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType );
	/** */
	void CreateGameFromSavegame( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType ) {}
	/** */
	void CreateGameFromScenario( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType ) {}
private:
	/** */
	void CreateModel( const GameInitialisationData& data );
	/** */
	void CreateMap(  const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType );
private:
	static 	GameMap *TheGameMap;
};



