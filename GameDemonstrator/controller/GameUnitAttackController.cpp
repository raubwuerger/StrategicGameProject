#include "stdafx.h"
#include "GameUnitAttackController.h"
#include "game/GameUnit.h"
#include "model/ModelUnitType.h"

bool GameUnitAttackController::IsUnitAttackable(const GameUnit* attacker, const GameUnit* defender)
{
	if (nullptr == attacker)
	{
		Q_ASSERT(true);
		return false;
	}

	if (nullptr == defender)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelAttacker = attacker->GetModelUnitType();
	if (nullptr == modelAttacker)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelDefender = defender->GetModelUnitType();
	if (nullptr == modelDefender)
	{
		Q_ASSERT(true);
		return false;
	}

	return modelAttacker->IsUnitTypeAttackable(modelDefender->GetId());
}

bool GameUnitAttackController::AttackUnit(const GameUnit* attacker, const GameUnit* defender)
{
	if (nullptr == attacker)
	{
		Q_ASSERT(true);
		return false;
	}

	if (nullptr == defender)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelAttacker = attacker->GetModelUnitType();
	if (nullptr == modelAttacker)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelDefender = defender->GetModelUnitType();
	if (nullptr == modelDefender)
	{
		Q_ASSERT(true);
		return false;
	}

	if (false == modelAttacker->IsUnitTypeAttackable(modelDefender->GetId()))
	{
		return false;
	}

	attacker->GetCurrentStrength();

	//TODO: Hier muss das Kampfergebnis berechnet und zurückgegeben werden. Aktuell wird jeder Kampf gewonnen!
	const_cast<GameUnit*>(attacker)->Move();
	return true;
}

bool GameUnitAttackController::AttackCity(const GameUnit* attacker, const GameCity* defender)
{
	if (nullptr == attacker)
	{
		Q_ASSERT(true);
		return false;
	}

	if (nullptr == defender)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelAttacker = attacker->GetModelUnitType();
	if (nullptr == modelAttacker)
	{
		Q_ASSERT(true);
		return false;
	}

	if (false == modelAttacker->GetCanOccupieCity())
	{
		return false;
	}

	//TODO: Hier muss das Kampfergebnis berechnet und zurückgegeben werden. Aktuell wird jeder Kampf gewonnen!
	const_cast<GameUnit*>(attacker)->Move();
	return true;
}

bool GameUnitAttackController::IsCityOccupiable(const GameUnit* attacker)
{
	if (nullptr == attacker)
	{
		Q_ASSERT(true);
		return false;
	}

	const ModelUnitType* modelAttacker = attacker->GetModelUnitType();
	if (nullptr == modelAttacker)
	{
		Q_ASSERT(true);
		return false;
	}

	return modelAttacker->GetCanOccupieCity();
}
