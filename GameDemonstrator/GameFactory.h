#pragma once

class ModelTerrainType;
class MapView;
class GameMap;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class GameFactory
{
public:
	/** */
	static GameFactory* GetInstance();
	/** */
	void Release();
	/** */
	void CreateNewGame();
	/** */
	void SetMapView( MapView* mapView );
private:
	/** */
	GameFactory();
	/** */
	~GameFactory();
private:
	static GameFactory	*Instance;
	GameMap				*TheGameMap;
	MapView				*MapViewInstance;
};



