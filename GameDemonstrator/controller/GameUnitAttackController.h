#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnit;
class GameCity;

class GameUnitAttackController
{
public:
	/** */
	static bool IsUnitAttackable(const GameUnit* attacker, const GameUnit* defender);
	/** If attack was successful true will be returned, otherwise false */
	static bool AttackUnit(const GameUnit* attacker, const GameUnit* defender);
	/** */
	static bool IsCityOccupiable(const GameUnit* attacker);
	/** If attack was successful true will be returned, otherwise false */
	static bool AttackCity(const GameUnit* attacker, const GameCity* defender);
private:
	/** */
};

#endif // GAMEUNITATTACKCONTROLLER_H