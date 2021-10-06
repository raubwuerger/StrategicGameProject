#include "stdafx.h"
#include "GameCityCreatorSimple.h"
#include "LogInterface.h"
#include "Game\GameMapTileRepository.h"
#include "Game\GameMapTile.h"
#include "Model\ModelTerrainTypeRepository.h"

bool GameCityCreatorSimple::Create()
{
	if (true == ValidTerrainTypesProcent.empty())
	{
		jha::GetLog()->Log_INFO("Member <ValidTerrainTypesProcent> is empty!");
		return false;
	}

	if (false == CreateTerrainTypeTiles())
	{
		return false;
	}

	if (false == PlaceCities())
	{
		return false;
	}
	return true;
}

bool GameCityCreatorSimple::AddValidTerrainTypeProcent(std::pair<int, double> validTerrainTypeProcent)
{
	if (0 != ValidTerrainTypesProcent.count(validTerrainTypeProcent.first))
	{
		jha::GetLog()->Log_INFO(QObject::tr("ValidTerrainTypesProcent pair already registered! [ModelMapTileId|Percentage]: %1|%2").arg(QString::number(validTerrainTypeProcent.first)).arg(QString::number(validTerrainTypeProcent.second)));
		return false;
	}
	ValidTerrainTypesProcent.insert(validTerrainTypeProcent);
	return true;
}

bool GameCityCreatorSimple::CreateTerrainTypeTiles() const
{
	const QVector< QVector<GameMapTile*> >* gameMapTiles = GameMapTileRepository::GetInstance()->GetMapTiles();
	if (true == gameMapTiles->isEmpty())
	{
		jha::GetLog()->Log_INFO(QObject::tr("GameMapTileRepository is empty!"));
		return false;
	}

	//TODO: Is this really more performant??
	int rows = gameMapTiles->count();
	int cols = gameMapTiles->at(0).count();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int colIndex = 0; colIndex < cols; colIndex++)
		{
			const GameMapTile* gameMapTile = gameMapTiles->at(rowIndex)[colIndex];
			int terrainTypeId = gameMapTile->GetModelTerrainTypeId();
			int gameMapId = gameMapTile->GetId();
			TerrainTypeTiles.insert(std::pair<int, int>(terrainTypeId, gameMapId));
		}
	}

	int terrainTypeCount = ModelTerrainTypeRepository::GetInstance()->GetCount();
	return TerrainTypeTiles.size() > 0;
}

bool GameCityCreatorSimple::PlaceCities()
{
	//TODO: Mininmale Anzahl der Städte sollte sich nach der Anzahl der Spieler richten!
	//TODO: Was ist zu tun wenn die minimale Anzahl der Städt größer als die zur Verfügung stehenden Felder ist -> Minimale Kartengröße erzwingen???

	//TODO: Aktuelle wird nur eine Geländeart unterschtützt!!!
	std::map<int, double>::iterator validTerrainTypeIterator = ValidTerrainTypesProcent.begin();
	int terrainTypeId = validTerrainTypeIterator->first;
	double terrainTypeIdProcent = validTerrainTypeIterator->second;

	int terrainTypeIdCount = TerrainTypeTiles.count(terrainTypeId);
	auto equalRange = TerrainTypeTiles.equal_range(terrainTypeId);
	auto first = equalRange.first;
	auto last = equalRange.second;
	for (auto it = first; it != last; it++)
	{

	}
	return false;
}
