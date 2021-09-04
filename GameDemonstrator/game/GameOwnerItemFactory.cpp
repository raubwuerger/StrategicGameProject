#include "stdafx.h"
#include "GameOwnerItem.h"
#include "GameOwnerItemFactory.h"
#include "GameOwnerItemRepository.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelOwnerTypeRepository.h"

bool GameOwnerItemFactory::CreateItemsFromSaveGame(const QDomNode node)
{
	QDomNodeList nodes = node.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(node.nodeName()));
		return false;
	}

	GameOwnerItemRepository::GetInstance()->Init();

	for (int nodeIndex = 0; nodeIndex < nodes.count(); nodeIndex++)
	{
		GameOwnerItem* created = CreateItemFromXML(nodes.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameOwnerItem from save game line number: %1").arg(QString::number(nodes.at(nodeIndex).columnNumber())));
			continue;
		}
		GameOwnerItemRepository::GetInstance()->RegisterItem(created);
	}

	return true;

}

GameOwnerItem* GameOwnerItemFactory::CreateItemFromXML(const QDomNode& node)
{
	QDomNodeList nodes = node.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	bool allElementsExtracted = true;
	DomValueExtractor extractor(node);
	
	int id = NOT_INITIALIZED_INT;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::PLAYER_ID, id);

	int ownerTypeId = NOT_INITIALIZED_INT;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::PLAYER_OWNERTYPEID, ownerTypeId);

	QString name = NOT_INITIALIZED_STRING;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::PLAYER_NAME, name);

	bool isHuman = NOT_INITIALIZED_BOOL;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::PLAYER_HUMAN, isHuman);

	if (false == allElementsExtracted)
	{
		Q_ASSERT(allElementsExtracted);
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameOwnerType from save game!"));
		return nullptr;
	}

	GameOwnerItem* item = new GameOwnerItem(id);
	item->IsHuman = isHuman;
	item->ModelOwnerTypeId = ownerTypeId;
	item->Name = name;
	item->ModelOwnerTypeObject = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);

	Q_ASSERT(item->ModelOwnerTypeObject);
	return item;
}
