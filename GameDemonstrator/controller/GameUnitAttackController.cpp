#include "stdafx.h"
#include "GameUnitAttackController.h"
#include "game/GameUnitItem.h"
#include "model/ModelUnitType.h"

void GameUnitAttackController::Attack(const GameUnitItem* attacker, const GameUnitItem* defender)
{
	if (nullptr == attacker)
	{
		Q_ASSERT(true);
		return;
	}

	if (nullptr == defender)
	{
		Q_ASSERT(true);
		return;
	}

	const ModelUnitType* modelAttacker = attacker->GetModelUnitType();
	if (nullptr == modelAttacker)
	{
		Q_ASSERT(true);
		return;
	}

	const ModelUnitType* modelDefender = defender->GetModelUnitType();
	if (nullptr == modelDefender)
	{
		Q_ASSERT(true);
		return;
	}


}
