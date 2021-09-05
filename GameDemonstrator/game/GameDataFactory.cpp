#include "stdafx.h"
#include "GameDataFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "game/GameConfig.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "GameOwnerItemRepository.h"
#include "DomNodeListValueExtractor.h"


bool GameDataFactory::Init()
{
	return true;
}

bool GameDataFactory::Create()
{
	return true;
}

bool GameDataFactory::CreateGameDataFromSaveGame(const QDomNode& node)
{
	QDomNodeList nodes = node.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(node.nodeName()));
		return false;
	}

	bool allElementsExtracted = true;

	DomValueExtractor extractor(node);

	int versionMajor = NOT_INITIALIZED_INT;
	int versionMinor = NOT_INITIALIZED_INT;
	int versionRevision = NOT_INITIALIZED_INT;
	int playerId = NOT_INITIALIZED_INT;
	int playerCount = NOT_INITIALIZED_INT;
	int gameTurn = NOT_INITIALIZED_INT;
	int difficultyLevel = NOT_INITIALIZED_INT;

	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_VERSION_MAJOR, versionMajor);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_VERSION_MINOR, versionMinor);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_VERSION_REVISION, versionRevision);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_PLAYER, playerId);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_PLAYERCOUNT, playerCount);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_GAMETURN, gameTurn);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::GAME_DIFFICULTYLEVEL, difficultyLevel);

	if (false == allElementsExtracted)
	{
		return false;
	}

	GameConfig::VersionMajor = versionMajor;
	GameConfig::VersionMinor = versionMinor;
	GameConfig::VersionRevision = versionRevision;
	GameConfig::PlayerId = playerId;
	GameConfig::PlayerCount = playerCount;
	GameConfig::CurrentTurn = gameTurn;
	GameConfig::DifficultyLevel = difficultyLevel;
	return true;
}
