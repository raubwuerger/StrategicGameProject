#ifndef GAMEUNITATTACKHELPER_H
#define GAMEUNITATTACKHELPER_H

class GameUnit;

class GameUnitAttackHelper
{
public:
	/** */
	GameUnitAttackHelper(GameUnit* attacker);
	/** */
	bool Attack(GameUnit* defender);
private:
	/** */
	GameUnitAttackHelper() {}
private:
	GameUnit*	Attacker;
};

#endif // GAMEUNITATTACKHELPER_H