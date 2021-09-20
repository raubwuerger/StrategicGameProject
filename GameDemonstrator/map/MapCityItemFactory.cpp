#include "stdafx.h"
#include "MapCityItemFactory.h"
#include "MapHexItemHexagonData.h"
#include "game/GameMapTile.h"
#include "game/GameMapTileRepository.h"
#include "game/GameCityRepository.h"
#include "game/GameCity.h"
#include "LogInterface.h"
#include "MapCityItem.h"
#include "MapCityItemRepository.h"
#include "MapHexItemRepository.h"
#include "MapHexItem.h"
#include "MapView.h"
#include "model\ModelCityType.h"
#include "game\GameOwner.h"

bool MapCityItemFactory::Create(MapView* mapView)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	MapHexItemHexagonData hexagonTemplate(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);

	const QVector< QVector<GameMapTile*> >* gameMap = GameMapTileRepository::GetInstance()->GetMapTiles();
	if (nullptr == gameMap)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameMapRepository contains no items!"));
		return false;
	}

	MapCityItemRepository::GetInstance()->Init();
	QMap<int, MapCityItem*> mapCityItems;
	QMap<int, GameCity*>::const_iterator gameCityIterator = GameCityRepository::GetInstance()->GetFirstIterator();
	while (gameCityIterator != GameCityRepository::GetInstance()->GetLastIterator())
	{
		const GameCity* gameCityItem = *gameCityIterator;
		int gameMapId = gameCityItem->GetGameMapTileId();
		const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetById(gameMapId);
		if (nullptr == mapHexItem)
		{
			return false;
		}

		QPointF topLeftPosition = mapHexItem->GetTopLeftPoint();
		MapCityItem *mapItem = new MapCityItem(hexagonTemplate, topLeftPosition);
		mapItem->SetGameMapItemId(gameMapId);
		mapItem->SetTerrainImage(GetImage(gameCityItem));
		mapItem->MapCityItemId = gameCityItem->GetId();
		mapItem->Color = gameCityItem->GetGameOwner()->GetColor();

		mapView->AddCity(mapItem);
		mapCityItems.insert(gameCityItem->GetId(), mapItem);

		gameCityIterator++;
	}

	MapCityItemRepository::GetInstance()->SetMapCityItems(mapCityItems);
	return true;
}

bool MapCityItemFactory::Create(MapView* mapView, const GameCity* gameCityItem)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	if (nullptr == gameCityItem)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <gameCityItem> must not be null!"));
		return false;
	}

	int gameMapId = gameCityItem->GetGameMapTileId();
	const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetById(gameMapId);
	if (nullptr == mapHexItem)
	{
		return false;
	}

	MapHexItemHexagonData hexagonTemplate(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);
	QPointF topLeftPosition = mapHexItem->GetTopLeftPoint();
	MapCityItem *mapItem = new MapCityItem(hexagonTemplate, topLeftPosition);
	mapItem->SetGameMapItemId(gameMapId);
	mapItem->SetTerrainImage(GetImage(gameCityItem));
	mapItem->MapCityItemId = gameCityItem->GetId();
	mapItem->Color = gameCityItem->GetGameOwner()->GetColor();

	mapView->AddCity(mapItem);
	return MapCityItemRepository::GetInstance()->Register(mapItem);
}

const QImage* MapCityItemFactory::GetImage(const GameCity* gameCityItem)
{
	const ModelCityType* modelCityType = gameCityItem->GetCityModelType();
	if (nullptr == modelCityType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelCityType->GetImage();
}

