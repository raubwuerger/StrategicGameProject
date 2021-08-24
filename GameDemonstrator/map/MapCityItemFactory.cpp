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

		mapView->AddCity(mapItem);
		mapCityItems.insert(gameCityItem->GetId(), mapItem);

		gameCityIterator++;
	}

	MapCityItemRepository::GetInstance()->SetMapCityItems(mapCityItems);
	return true;
}

const QImage* MapCityItemFactory::GetImage(const GameCityItem* gameCityItem)
{
	const ModelCityType* modelCityType = gameCityItem->GetCityType();
	if (nullptr == modelCityType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelCityType->GetImage();
}
