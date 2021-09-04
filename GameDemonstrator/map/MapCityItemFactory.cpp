#include "stdafx.h"
#include "MapCityItemFactory.h"
#include "MapHexItemHexagonData.h"
#include "game/GameMapItem.h"
#include "game/GameMapItemRepository.h"
#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
#include "LogInterface.h"
#include "MapCityItem.h"
#include "MapCityItemRepository.h"
#include "MapHexItemRepository.h"
#include "MapHexItem.h"
#include "MapView.h"
#include "model\ModelCityType.h"
#include "game\GameOwnerItem.h"

bool MapCityItemFactory::Create(MapView* mapView)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	MapHexItemHexagonData hexagonTemplate(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);

	const QVector< QVector<GameMapItem*> >* gameMap = GameMapItemRepository::GetInstance()->GetMapItems();
	if (nullptr == gameMap)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameMapRepository contains no items!"));
		return false;
	}

	MapCityItemRepository::GetInstance()->Init();
	QMap<int, MapCityItem*> mapCityItems;
	QMap<int, GameCityItem*>::const_iterator gameCityIterator = GameCityItemRepository::GetInstance()->GetFirstIterator();
	while (gameCityIterator != GameCityItemRepository::GetInstance()->GetLastIterator())
	{
		const GameCityItem* gameCityItem = *gameCityIterator;
		int gameMapId = gameCityItem->GetGameMapItemId();
		const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(gameMapId);
		if (nullptr == mapHexItem)
		{
			return false;
		}

		QPointF topLeftPosition = mapHexItem->GetTopLeftPoint();
		MapCityItem *mapItem = new MapCityItem(hexagonTemplate, topLeftPosition);
		mapItem->SetGameMapItemId(gameMapId);
		mapItem->SetTerrainImage(GetImage(gameCityItem));
		mapItem->MapCityItemId = gameCityItem->GetId();
		mapItem->Color = gameCityItem->GetGameOwnerItem()->GetColor();

		mapView->AddCity(mapItem);
		mapCityItems.insert(gameCityItem->GetId(), mapItem);

		gameCityIterator++;
	}

	MapCityItemRepository::GetInstance()->SetMapCityItems(mapCityItems);
	return true;
}

bool MapCityItemFactory::Create(MapView* mapView, const GameCityItem* gameCityItem)
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

	int gameMapId = gameCityItem->GetGameMapItemId();
	const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(gameMapId);
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
	mapItem->Color = gameCityItem->GetGameOwnerItem()->GetColor();

	mapView->AddCity(mapItem);
	return MapCityItemRepository::GetInstance()->Register(mapItem);
}

const QImage* MapCityItemFactory::GetImage(const GameCityItem* gameCityItem)
{
	const ModelCityType* modelCityType = gameCityItem->GetCityModelType();
	if (nullptr == modelCityType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelCityType->GetImage();
}

