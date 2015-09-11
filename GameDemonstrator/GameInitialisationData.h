#pragma once

namespace GDModel
{

/** Enthält alle notwendigen Daten zum Erstellen eines neuen Spiels */

class CGameInitialisationData
{
public:
	CGameInitialisationData();
public:
	int		Rows;
	int		Cols;
	int		Oponents;
	int		Diffculty;
	int		DefaultMapTileTerrainId;
};

}