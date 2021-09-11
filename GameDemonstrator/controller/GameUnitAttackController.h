#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnitItem;
class GameCity;

class GameUnitAttackController
{
public:
	/** */
	static bool IsUnitAttackable(const GameUnitItem* attacker, const GameUnitItem* defender);
	/** If attack was successful true will be returned, otherwise false */
	static bool AttackUnit(const GameUnitItem* attacker, const GameUnitItem* defender);
	/** */
	static bool IsCityOccupiable(const GameUnitItem* attacker);
	/** If attack was successful true will be returned, otherwise false */
	static bool AttackCity(const GameUnitItem* attacker, const GameCity* defender);
private:
	/** */
};

#endif // GAMEUNITATTACKCONTROLLER_H