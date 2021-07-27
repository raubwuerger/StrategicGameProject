#pragma once

/** Enthält alle notwendigen Daten zum Erstellen eines neuen Spiels */

//TODO: Should be removed!!!

class GameInitialisationData
{
public:
	GameInitialisationData();
public:
	int		Rows;
	int		Cols;
	int		Oponents;
	int		Diffculty;
	int		DefaultMapTileTerrainId;
};
