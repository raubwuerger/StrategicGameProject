#pragma once

class CTerrainType;
class CMapView;
class CGameInitialisationData;
class GameMap;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class CGameFactory
{
public:
	/** */
	CGameFactory();
	/** */
	~CGameFactory();
	/** */
	void CreateNewGame();
	/** */
	void CreateNewGame( const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType );
	/** */
	void CreateGameFromSavegame( const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType ) {}
	/** */
	void CreateGameFromScenario( const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType ) {}
private:
	/** */
	void CreateModel( const CGameInitialisationData& data );
	/** */
	void CreateMap(  const CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType );
private:
	static 	GameMap *TheGameMap;
};



