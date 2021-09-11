#include "stdafx.h"
#include "GameOwnerRepository.h"
#include "GameOwner.h"
#include "LogInterface.h"

GameOwnerRepository* GameOwnerRepository::Instance = nullptr;

GameOwnerRepository::GameOwnerRepository()
	: BaseRepository(),
	DefaultGameOwnerTypeId(NOT_INITIALIZED_INT)
{

}

GameOwnerRepository* GameOwnerRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new GameOwnerRepository();
	return Instance;
}

void GameOwnerRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool GameOwnerRepository::Init()
{
	GameOwners.clear();
	return true;
}

bool GameOwnerRepository::Register(GameOwner* gameOwner)
{
	if (nullptr == gameOwner)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <GameOwner> parameter is null!"));
		return false;
	}
	if (true == GameOwners.contains(gameOwner->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameOwner with id=%1 already exists!").arg(gameOwner->GetId()));
		return false;
	}
	if (0 == GetCount())
	{
		DefaultGameOwnerTypeId = gameOwner->GetId();
	}
	GameOwners.insert(gameOwner->GetId(), gameOwner);
	return true;
}

const GameOwner* GameOwnerRepository::GetById(int id) const
{
	if (false == GameOwners.contains(id))
	{
		return nullptr;
	}
	return GameOwners.value(id);
}

QMap<int, GameOwner*>::const_iterator GameOwnerRepository::GetFirstIterator() const
{
	return GameOwners.cbegin();
}

QMap<int, GameOwner*>::const_iterator GameOwnerRepository::GetLastIterator() const
{
	return GameOwners.cend();
}

const GameOwner* GameOwnerRepository::GetHuman() const
{
	QMapIterator<int, GameOwner*> iterator(GameOwners);
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

int GameOwnerRepository::CreateNewId()
{
	//TODO: Gefährlich da beim laden diese Id schon vorhanden sein könnte!
	//TODO: Testen ob die erzeugte id schon in der map ist!!
	int newId = GameOwners.size();
	return ++newId;
}

int GameOwnerRepository::GetCount() const
{
	return GameOwners.size();
}

const GameOwner* GameOwnerRepository::GetDefaultOwnerType() const
{
	return GameOwners.value(DefaultGameOwnerTypeId);
}
