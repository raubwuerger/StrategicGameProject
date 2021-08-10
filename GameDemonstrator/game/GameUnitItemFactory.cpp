#include "stdafx.h"
#include "GameUnitItemFactory.h"
#include <QtXml>

GameUnitItemFactory::GameUnitItemFactory()
{
}

GameUnitItemFactory::~GameUnitItemFactory()
{
}

bool GameUnitItemFactory::CreateGameUnitItemFromScratch()
{
	return false;
}

bool GameUnitItemFactory::CreateGameUnitItemsFromSaveGame( const QDomNode mapElements )
{
	QDomNode* unitItemElements = new QDomNode(mapElements);
	return false;
}
