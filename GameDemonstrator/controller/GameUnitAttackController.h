#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnitItem;
class GameCityItem;

class GameUnitAttackController
{
public:
	/** */
	static bool IsAttackSuccessful(const GameUnitItem* attacker, const GameUnitItem* defender);
	/** */
	static bool IsAttackSuccessful(const GameUnitItem* attacker, const GameCityItem* defender);
private:
	/** */
};

#endif // GAMEUNITATTACKCONTROLLER_H