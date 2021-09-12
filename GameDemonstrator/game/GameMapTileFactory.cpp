#include "stdafx.h"
#include "GameMapTileFactory.h"
#include "GameMapTileRepository.h"
#include "GameMapTile.h"
#include "model\ModelTerrainTypeRepository.h"
#include <QtXml>
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "game\GameConfig.h"
#include "LogInterface.h"
#include "mapCreator\GameMapCreatorSimple.h"
#include "mapCreator\GameMapCreatorHeightMap.h"
#include "GameConfig.h"

GameMapTileFactory::GameMapTileFactory()
{
}

GameMapTileFactory::~GameMapTileFactory()
{
}

//TODO: Revise concept -> XML map creation- MapTypes.xml
bool GameMapTileFactory::Create()
{
	if (GameConfig::MapType == "Flat")
	{
		GameMapCreatorSimple mapCreator;
		return mapCreator.CreateMap();
	}
	if (GameConfig::MapType == "HeightMap")
	{
		GameMapCreatorHeightMap mapCreator;
		return mapCreator.CreateMap();
	}
	return false;
}

bool GameMapTileFactory::Create(const QDomNode mapElements)
{
	GameMapTileRepository::GetInstance()->Init();
	DomNodeFinder domNodeFinder(mapElements);

	if (false == InitializeMap(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAP_SETTINGS)))
	{
		return false;
	}

	if (false == CreateGameMapTiles(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAP_MAPITEMS)))
	{
		return false;
	}
	return true;
}


bool GameMapTileFactory::Validate(const GameMapParameterObject& obj) const
{
	return false;
}

bool GameMapTileFactory::InitializeMap(const QDomNode& settings)
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

const ModelTerrainType* GameMapTileFactory::GetModelTerrainType(const GameMapParameterObject& obj) const
{
	return nullptr;
}

bool GameMapTileFactory::CreateGameMapTiles(const QDomNode& node)
{
	QDomNodeList nodes = node.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(node.nodeName()));
		return false;
	}

	QVector<GameMapTile*> gameMapTilesUnsorted;
	for (int nodeIndex = 0; nodeIndex < nodes.count(); nodeIndex++)
	{
		GameMapTile* created = CreateGameMapTile(nodes.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameMapTile from save game line number: %1").arg(QString::number(nodes.at(nodeIndex).columnNumber())));
			return false;
		}
		gameMapTilesUnsorted.push_back(created);
	}

	int gameMapTilesUnsortedIndex = 0;
	QVector< QVector<GameMapTile*> >* gameMap = new QVector< QVector<GameMapTile*> >();
	for (int rowIndex = 0; rowIndex < GameConfig::MapRows; rowIndex++)
	{
		QVector<GameMapTile*> row;
		row.reserve(GameConfig::MapCols);
		for (int colIndex = 0; colIndex < GameConfig::MapCols; colIndex++)
		{
			row.append(gameMapTilesUnsorted.at(gameMapTilesUnsortedIndex++));
		}
		gameMap->append(row);
	}

	GameMapTileRepository::GetInstance()->SetGameMapTiles(gameMap);
	return true;
}

GameMapTile* GameMapTileFactory::CreateGameMapTile(const QDomNode& node)
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

	GameMapTile *newModelMapTile = new GameMapTile(currentRow, currentCol, currentId);
	newModelMapTile->SetModelTerrainType(ModelTerrainTypeRepository::GetInstance()->FindTerrainTypeById(currentTerrainTyp));
	newModelMapTile->ModelTerrainTypeId = currentTerrainTyp;
	return newModelMapTile;
}
