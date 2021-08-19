#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnitItem;

class GameUnitAttackController
{
public:
	/** */
	static bool IsAttackSuccessful(const GameUnitItem* attacker, const GameUnitItem* defender);
private:
	/** */
};

#endif // GAMEUNITATTACKCONTROLLER_H