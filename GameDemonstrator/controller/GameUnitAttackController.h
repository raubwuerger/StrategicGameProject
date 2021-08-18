#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnitItem;

class GameUnitAttackController
{
public:
	static void Attack(const GameUnitItem* attacker, const GameUnitItem* defender);
};

#endif // GAMEUNITATTACKCONTROLLER_H