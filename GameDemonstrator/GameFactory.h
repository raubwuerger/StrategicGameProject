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
	static GameFactory* GetInstance();
	/** */
	void CreateNewGame();
	/** */
	void CreateNewGame( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType );
	/** */
	void CreateGameFromSavegame( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType ) {}
	/** */
	void CreateGameFromScenario( const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType ) {}
	/** */
	void SetMapView( MapView* mapView ) { MapViewInstance = mapView; }
private:
	/** */
	void CreateModel( const GameInitialisationData& data );
	/** */
	void CreateMap(  const GameInitialisationData& data, MapView *mapView, const TerrainType * defaultTerrainType );
	/** */
	GameFactory();
	/** */
	~GameFactory();
private:
	static GameFactory* Instance;
	static 	GameMap *TheGameMap;
	MapView		*MapViewInstance;
};



