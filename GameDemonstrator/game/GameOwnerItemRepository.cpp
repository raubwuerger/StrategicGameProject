#include "stdafx.h"
#include "GameOwnerItemRepository.h"
#include "GameOwnerItem.h"
#include "LogInterface.h"

GameOwnerItemRepository* GameOwnerItemRepository::Instance = nullptr;

GameOwnerItemRepository::GameOwnerItemRepository()
	: BaseRepository(),
	DefaultGameOwnerTypeId(NOT_INITIALIZED_INT)
{

}

GameOwnerItemRepository* GameOwnerItemRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new GameOwnerItemRepository();
	return Instance;
}

void GameOwnerItemRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool GameOwnerItemRepository::Init()
{
	GameOwnerItems.clear();
	return true;
}

bool GameOwnerItemRepository::RegisterItem(GameOwnerItem* item)
{
	if (nullptr == item)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <GameOwnerItem> parameter is null!"));
		return false;
	}
	if (true == GameOwnerItems.contains(item->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameOwnerItem with id=%1 already exists!").arg(item->GetId()));
		return false;
	}
	if (0 == GetItemCount())
	{
		DefaultGameOwnerTypeId = item->GetId();
	}
	GameOwnerItems.insert(item->GetId(), item);
	return true;
}

const GameOwnerItem* GameOwnerItemRepository::GetItemById(int id) const
{
	if (false == GameOwnerItems.contains(id))
	{
		return nullptr;
	}
	return GameOwnerItems.value(id);
}

QMap<int, GameOwnerItem*>::const_iterator GameOwnerItemRepository::GetFirstIterator() const
{
	return GameOwnerItems.cbegin();
}

QMap<int, GameOwnerItem*>::const_iterator GameOwnerItemRepository::GetLastIterator() const
{
	return GameOwnerItems.cend();
}

const GameOwnerItem* GameOwnerItemRepository::GetHuman() const
{
	QMapIterator<int, GameOwnerItem*> iterator(GameOwnerItems);
	while (iterator.hasNext()) 
	{
		if (false == iterator.next().value()->GetIsHuman())
		{
			continue;
		}
		return iterator.value();
	}
	return nullptr;
}

int GameOwnerItemRepository::CreateNewId()
{
	//TODO: Gefährlich da beim laden diese Id schon vorhanden sein könnte!
	//TODO: Testen ob die erzeugte id schon in der map ist!!
	int newId = GameOwnerItems.size();
	return ++newId;
}

int GameOwnerItemRepository::GetItemCount() const
{
	return GameOwnerItems.size();
}

const GameOwnerItem* GameOwnerItemRepository::GetDefaultOwnerType() const
{
	return GameOwnerItems.value(DefaultGameOwnerTypeId);
}
