#include "stdafx.h"
#include "GameUnitAttackController.h"
#include "game/GameUnitItem.h"
#include "model/ModelUnitType.h"

bool GameUnitAttackController::IsUnitAttackable(const GameUnitItem* attacker, const GameUnitItem* defender)
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

bool GameUnitAttackController::IsAttackSuccessful(const GameUnitItem* attacker, const GameUnitItem* defender)
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

	//TODO: Hier muss das Kampfergebnis berechnet und zurückgegeben werden. Aktuell wird jeder Kampf gewonnen!
	return true;
}

bool GameUnitAttackController::IsAttackSuccessful(const GameUnitItem* attacker, const GameCityItem* defender)
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
	return true;
}

bool GameUnitAttackController::IsCityOccupiable(const GameUnitItem* attacker)
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
