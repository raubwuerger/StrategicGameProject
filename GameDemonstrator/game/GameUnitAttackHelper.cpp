#include "stdafx.h"
#include "GameUnitAttackHelper.h"

GameUnitAttackHelper::GameUnitAttackHelper(GameUnit *attacker)
	: Attacker(attacker)
{
	Q_ASSERT(attacker);
}

int GameUnitAttackHelper::GetDefensValue(GameUnit* defender)
{
	return -1;
}

bool GameUnitAttackHelper::Attack(GameUnit* defender)
{
	if (nullptr == defender)
	{
		Q_ASSERT(defender);
		return false;
	}
}
