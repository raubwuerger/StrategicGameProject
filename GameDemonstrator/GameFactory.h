#pragma once

class CTerrainType;
class CMapView;
namespace GDModel { class CGameInitialisationData; }
namespace GDModel { class GameMap; }

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class CGameFactory
{
public:
	/** */
	CGameFactory();
	/** */
	~CGameFactory();
	/** */
	void CreateNewGame( const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType );
private:
	/** */
	void CreateModel( const GDModel::CGameInitialisationData& data );
	/** */
	void CreateMap(  const GDModel::CGameInitialisationData& data, CMapView *mapView, const CTerrainType * defaultTerrainType );
private:
	static 	GDModel::GameMap *TheGameMap;
};



