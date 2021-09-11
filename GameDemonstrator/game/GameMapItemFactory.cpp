#include "stdafx.h"
#include "GameMapItemFactory.h"
#include "GameMapItemRepository.h"
#include "GameMapItem.h"
#include "model\ModelTerrainTypeRepository.h"
#include <QtXml>
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "game\GameConfig.h"
#include "LogInterface.h"
#include "mapCreator\GameMapCreatorSimple.h"

GameMapItemFactory::GameMapItemFactory()
{
}

GameMapItemFactory::~GameMapItemFactory()
{
}

bool GameMapItemFactory::Create()
{
	GameMapCreatorSimple gameMapItemCreatorSimple;
	return gameMapItemCreatorSimple.CreateMap();
}

bool GameMapItemFactory::Create(const QDomNode mapElements)
{
	GameMapItemRepository::GetInstance()->Init();
	DomNodeFinder domNodeFinder(mapElements);

	if (false == InitializeMap(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAP_SETTINGS)))
	{
		return false;
	}

	if (false == CreateGameMapItems(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAP_MAPITEMS)))
	{
		return false;
	}
	return true;
}


bool GameMapItemFactory::Validate(const GameMapParameterObject& obj) const
{
	return false;
}

bool GameMapItemFactory::InitializeMap(const QDomNode& settings)
{
	QDomNodeList settingsNodeList = settings.childNodes();
	if (true == settingsNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(settings.nodeName()));
		return false;
	}

	bool allElementsExtracted = true;
	DomValueExtractor domNodeListValueExtractor(settings);
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_SETTINGS_ROWS, GameConfig::MapRows);
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_SETTINGS_COLS, GameConfig::MapCols);

	return allElementsExtracted;
}

const ModelTerrainType* GameMapItemFactory::GetModelTerrainType(const GameMapParameterObject& obj) const
{
	return nullptr;
}

bool GameMapItemFactory::CreateGameMapItems(const QDomNode& mapItems)
{
	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if (true == mapItemNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(mapItems.nodeName()));
		return false;
	}

	QVector<GameMapItem*> mapItemsUnsorted;
	for (int nodeIndex = 0; nodeIndex < mapItemNodeList.count(); nodeIndex++)
	{
		GameMapItem* created = CreateGameMapItem(mapItemNodeList.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(mapItemNodeList.at(nodeIndex).columnNumber())));
			return false;
		}
		mapItemsUnsorted.push_back(created);
	}

	int mapItemsUnsortedIndex = 0;
	QVector< QVector<GameMapItem*> >* gameMap = new QVector< QVector<GameMapItem*> >();
	for (int rowIndex = 0; rowIndex < GameConfig::MapRows; rowIndex++)
	{
		QVector<GameMapItem*> row;
		row.reserve(GameConfig::MapCols);
		for (int colIndex = 0; colIndex < GameConfig::MapCols; colIndex++)
		{
			row.append(mapItemsUnsorted.at(mapItemsUnsortedIndex++));
		}
		gameMap->append(row);
	}

	GameMapItemRepository::GetInstance()->SetGameMapItems(gameMap);
	return true;
}

GameMapItem* GameMapItemFactory::CreateGameMapItem(const QDomNode& node)
{
	QDomNodeList mapNodes = node.childNodes();
	if (true == mapNodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	bool allElementsExtracted = true;
	int currentId = -1;
	DomValueExtractor domNodeListValueExtractor(node);
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_ID, currentId);

	int currentRow = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_ROW, currentRow);

	int currentCol = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_COL, currentCol);

	int currentTerrainTyp = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::MAP_TERRAINTYPE, currentTerrainTyp);

	if (false == allElementsExtracted)
	{
		Q_ASSERT(allElementsExtracted);
		return nullptr;
	}

	GameMapItem *newModelMapItem = new GameMapItem(currentRow, currentCol, currentId);
	newModelMapItem->SetModelTerrainType(ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById(currentTerrainTyp));
	newModelMapItem->ModelTerrainTypeId = currentTerrainTyp;
	return newModelMapItem;
}
