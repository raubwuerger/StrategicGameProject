#include "stdafx.h"
#include "GameObjectController.h"
#include "Game\GameObject.h"
#include "game\GameCityItem.h"
#include "game\GameUnitProductionController.h"

GameObjectController::GameObjectController()
{

}

bool GameObjectController::CheckIfGameObjectIsOfTypeGameCity(const GameObject* object) const
{
	if (object->UID >= 20000)
	{
		return false;
	}

	if (object->UID < 10000)
	{
		return false;
	}
	return true;
}

GameObjectController*	GameObjectController::Instance = nullptr;

GameObjectController* GameObjectController::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new GameObjectController();
	return Instance;
}

bool GameObjectController::RegisterObject(const GameObject* object)
{
	Q_ASSERT(object);
	if (true == GameObjects.contains(object->UID) )
	{
		return false;
	}

	if (true == CheckIfGameObjectIsOfTypeGameCity(object))
	{
		GameUnitProductionController::GetInstance()->RegisterGameUnitProduction(reinterpret_cast<const GameCityItem*>(object)->GetUnitProduction());
	}
	
	GameObjects.insert(object->UID,object);
	return true;
}

bool GameObjectController::UnregisterObject(const GameObject* object)
{
	Q_ASSERT(object);
	if (false == GameObjects.contains(object->UID))
	{
		return false;
	}
	GameObjects.remove(object->UID);
	return true;
}

bool GameObjectController::Init()
{
	GameObjects.clear();
	return true;
}

void GameObjectController::Release()
{
	delete Instance;
	Instance = nullptr;
}

void GameObjectController::SlotDoUpdateTurn()
{
	QMapIterator<int, const GameObject*> iterator(GameObjects);
	while (iterator.hasNext())
	{
		iterator.next().value()->UpdateTurn();
	}

	GameUnitProductionController::GetInstance()->UpdateTurn();
}
