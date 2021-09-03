#ifndef GAMEUNITATTACKCONTROLLER_H
#define GAMEUNITATTACKCONTROLLER_H

class GameUnitItem;
class GameCityItem;

class GameUnitAttackController
{
public:
	/** */
	static bool IsUnitAttackable(const GameUnitItem* attacker, const GameUnitItem* defender);
	/** */
	static bool IsAttackUnitSuccessful(const GameUnitItem* attacker, const GameUnitItem* defender);
	/** */
	static bool IsCityOccupiable(const GameUnitItem* attacker);
	/** */
	static bool IsAttackCitySuccessful(const GameUnitItem* attacker, const GameCityItem* defender);
private:
	/** */
};

#endif // GAMEUNITATTACKCONTROLLER_H