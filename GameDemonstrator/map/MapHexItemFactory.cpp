#include "stdafx.h"
#include "MapHexItemFactory.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapTile.h"
#include "game/GameMapTileRepository.h"
#include "LogInterface.h"
#include "MapHexItem.h"
#include "MapHexItemRepository.h"
#include "MapView.h"
#include "HexagonFactory.h"
#include "HexagonItem.h"

bool MapHexItemFactory::Create(MapView* mapView)
{
	HexagonFactory hexagonFactory;
	HexagonItem* polygon = hexagonFactory.CreateFlatTopped();

	bool showText = true;
	bool showHexBorder = true;

	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	mapView->Create();

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
			MapHexItem *mapItem = new MapHexItem(topLeftPosition, *polygon);
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
	HexagonFactory hexagonFactory;
	HexagonItem* polygon = hexagonFactory.CreateFlatTopped();

	//TODO: These values are fixed for the game!!!
	//TODO: Refactor!!!
	double Side_ToBeReplaced = 3.0 / 2.0 * polygon->GetSideLength();

	double startX = 0.0;
	double offsetX = Side_ToBeReplaced + GLOBAL_HEXAGON_OFFSET;

	//TODO: Refactor!!!
	double Height_ToBeReplaced = SQUARE_ROOT_THREE * polygon->GetSideLength();
	double startY = 0.0;
	double offsetY = Height_ToBeReplaced + GLOBAL_HEXAGON_OFFSET;

	double offsetYEvenCol = Height_ToBeReplaced / 2.0;
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

