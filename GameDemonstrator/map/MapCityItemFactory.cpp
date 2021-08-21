#include "stdafx.h"
#include "MapCityItemFactory.h"
#include "MapHexItemHexagonData.h"
#include "game/GameMapItem.h"
#include "game/GameMapItemRepository.h"
#include "LogInterface.h"
#include "MapCityItem.h"
#include "MapCityItemRepository.h"
#include "MapView.h"

bool MapCityItemFactory::Create(MapView* mapView)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	mapView->Create();
	MapHexItemHexagonData hexagonTemplate(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);

	const QVector< QVector<GameMapItem*> >* gameMap = GameMapItemRepository::GetInstance()->GetMapItems();
	if (nullptr == gameMap)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameMapRepository contains no items!"));
		return false;
	}

	QVector< QVector<MapCityItem*> > MapCityItems;
	int rows = gameMap->size();
	for (int currentRow = 0; currentRow < rows; currentRow++)
	{
		QVector<MapCityItem*> MapCityItemRow;
		QVector<GameMapItem*> row = gameMap->at(currentRow);
		int cols = row.size();
		for (int currentCol = 0; currentCol < cols; currentCol++)
		{
			GameMapItem* gameMapItem = row.at(currentCol);
			QPointF topLeftPosition;
/*			CreateTopLeftPosition(currentRow, currentCol, topLeftPosition);
			MapCityItem *mapItem = new MapCityItem(hexagonTemplate, topLeftPosition);
			mapItem->SetRowAndCol(currentRow, currentCol);
			mapItem->SetGameMapItemId(gameMapItem->GetId());
			mapItem->SetTerrainImage(GetImage(gameMapItem));
			mapView->AddMapCityItem(mapItem);
			MapCityItemRow.push_back(mapItem);*/
		}
		MapCityItems.push_back(MapCityItemRow);
	}

	MapCityItemRepository::GetInstance()->Init();
	MapCityItemRepository::GetInstance()->SetMapCityItems(MapCityItems);
	return true;
}

const QImage* MapCityItemFactory::GetImage(const GameCityItem* gameCityItem)
{
	return nullptr;
/*	const GameCityItem* modelCityType = gameCityItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return gameCityItem->GetImage();*/
}

