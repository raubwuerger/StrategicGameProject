#include "stdafx.h"
#include "GameUnitAttackHelper.h"

GameUnitAttackHelper::GameUnitAttackHelper(GameUnit *attacker)
	: Attacker(attacker)
{
	Q_ASSERT(attacker);
}

bool GameUnitAttackHelper::Attack(GameUnit* defender)
{
	if (nullptr == defender)
	{
		Q_ASSERT(defender);
		return false;
	}
}
