#include "stdafx.h"
#include "MapHexItemFactory.h"
#include "MapHexItemHexagonData.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapTile.h"
#include "game/GameMapTileRepository.h"
#include "LogInterface.h"
#include "MapHexItem.h"
#include "MapHexItemRepository.h"
#include "MapView.h"
#include "HexagonFactory.h"

bool MapHexItemFactory::Create(MapView* mapView)
{
	bool showText = true;
	bool showHexBorder = true;

	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	mapView->Create();
	MapHexItemHexagonData hexagonTemplate(HexagonFactory::HEXAGON_DISTANCE_CENTER_CORNER);

	const QVector< QVector<GameMapTile*> >* gameMap = GameMapTileRepository::GetInstance()->GetMapTiles();
	if (nullptr == gameMap)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameMapRepository contains no items!"));
		return false;
	}

	QVector< QVector<MapHexItem*> > mapHexItems;
	int rows = gameMap->size();
	for (int currentRow = 0; currentRow < rows; currentRow++)
	{
		QVector<MapHexItem*> mapHexItemRow;
		QVector<GameMapTile*> row = gameMap->at(currentRow);
		int cols = row.size();
		for (int currentCol = 0; currentCol < cols; currentCol++)
		{
			GameMapTile* gameMapItem = row.at(currentCol);
			QPointF topLeftPosition;
			CreateTopLeftPosition(currentRow, currentCol, topLeftPosition);
			MapHexItem *mapItem = new MapHexItem(hexagonTemplate, topLeftPosition);
			mapItem->SetRowAndCol(currentRow, currentCol);
			mapItem->SetGameMapItemId(gameMapItem->GetId());
			mapItem->SetTerrainImage(GetImage(gameMapItem));
			mapItem->SetShowText(showText);
			mapItem->SetShowHexBorder(showHexBorder);
			mapView->AddMapHexItem(mapItem);
			mapHexItemRow.push_back(mapItem);
		}
		mapHexItems.push_back(mapHexItemRow);
	}

	MapHexItemRepository::GetInstance()->Init();
	MapHexItemRepository::GetInstance()->SetMapHexItems(mapHexItems);
	return true;
}

bool MapHexItemFactory::CreateTopLeftPosition(int row, int col, QPointF &topLeftPosition)
{
	MapHexItemHexagonData hexagonTemplate(HexagonFactory::HEXAGON_DISTANCE_CENTER_CORNER);

	double startX = 0.0;
	double offsetX = hexagonTemplate.Side + GLOBAL_HEXAGON_OFFSET;

	double startY = 0.0;
	double offsetY = hexagonTemplate.Height + GLOBAL_HEXAGON_OFFSET;

	double offsetYEvenCol = hexagonTemplate.Height / 2.0;
	double cordX = startX + col * offsetX;
	double cordY = startY + row * offsetY;
	if ((col % 2) == 1)
	{
		cordY += offsetYEvenCol;
	}

	topLeftPosition.setX(cordX);
	topLeftPosition.setY(cordY);
	return true;

}

const QImage* MapHexItemFactory::GetImage(const GameMapTile* modelMapItem)
{
	const ModelTerrainType* modelTerrainType = modelMapItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelTerrainType->GetImage();
}

