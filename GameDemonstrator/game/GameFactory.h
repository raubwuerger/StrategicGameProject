#pragma once

class ModelTerrainType;
class MapView;
class ModelMapRepository;

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
	ModelMapRepository				*TheGameMap;
	MapView				*MapViewInstance;
};



