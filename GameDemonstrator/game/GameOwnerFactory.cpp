#include "stdafx.h"
#include "GameOwner.h"
#include "GameOwnerFactory.h"
#include "GameOwnerRepository.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelOwnerTypeRepository.h"
#include "model\ModelOwnerType.h"

bool GameOwnerFactory::Create()
{
	GameOwnerRepository::GetInstance()->Init();

	QMap<int, const ModelOwnerType*>::const_iterator iterator = ModelOwnerTypeRepository::GetInstance()->GetFirstIterator();
	while (iterator != ModelOwnerTypeRepository::GetInstance()->GetLastIterator())
	{ 
		GameOwnerRepository::GetInstance()->Register(CreateGameOwner(iterator.value()));
		iterator++;
	}

	return GameOwnerRepository::GetInstance()->GetCount() > 0;
}

GameOwner* GameOwnerFactory::CreateGameOwner(const ModelOwnerType* model)
{
	GameOwner* gameOwner = new GameOwner(GameOwnerRepository::GetInstance()->CreateNewId());
	gameOwner->Name = model->GetName();
	gameOwner->ModelOwnerTypeId = model->GetId();
	gameOwner->ModelOwnerTypeObject = model;
	return gameOwner;
}

bool GameOwnerFactory::Create(const QDomNode node)
{
	GameOwnerRepository::GetInstance()->Init();
	QDomNodeList nodes = node.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(node.nodeName()));
		return false;
	}

	for (int nodeIndex = 0; nodeIndex < nodes.count(); nodeIndex++)
	{
		GameOwner* created = CreateFromXML(nodes.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameOwner from save game line number: %1").arg(QString::number(nodes.at(nodeIndex).columnNumber())));
			continue;
		}
		GameOwnerRepository::GetInstance()->Register(created);
	}

	return true;

}

GameOwner* GameOwnerFactory::CreateFromXML(const QDomNode& node)
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

	GameOwner* newGameOwner = new GameOwner(id);
	newGameOwner->IsHuman = isHuman;
	newGameOwner->ModelOwnerTypeId = ownerTypeId;
	newGameOwner->Name = name;
	newGameOwner->ModelOwnerTypeObject = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);

	Q_ASSERT(newGameOwner->ModelOwnerTypeObject);
	return newGameOwner;
}
