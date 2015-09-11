#pragma once

class CTerrainType;
class MapView;
namespace GDModel { class CGameInitialisationData; }

/** Erstellt alle Komponenten die für ein neuen Spiel notwendig sind */
class CGameFactory
{
public:
	/** */
	CGameFactory();
	/** */
	~CGameFactory();
	/** */
	void CreateNewGame( const GDModel::CGameInitialisationData& data, MapView *mapView, const CTerrainType * defaultTerrainType );
private:
	/** */
	void CreateModel( const GDModel::CGameInitialisationData& data );
	/** */
	void CreateMap(  const GDModel::CGameInitialisationData& data, MapView *mapView, const CTerrainType * defaultTerrainType );
};

