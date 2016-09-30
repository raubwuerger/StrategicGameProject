#pragma once

class CTerrainType;
class MapView;
namespace GDModel { class CGameInitialisationData; }
namespace GDModel { class CMap; }

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
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
private:
	static 	GDModel::CMap *Map;
};



