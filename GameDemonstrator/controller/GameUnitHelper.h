#ifndef GAMEUNITHELPER_H
#define GAMEUNITHELPER_H

class GameUnit;
class GameOwner;

class GameUnitHelper
{
public:
	/** */
	static bool IsEnemyOnDestinationMapTile(const GameUnit*	gameUnit, int gameMapItemId);
	/** */
	static bool IsOwnUnitOnDestinationMapTile(const GameUnit*	gameUnit, int gameMapItemId);
	/** */
	static const GameUnit* GetEnemyGameUnit(int mapItemId);
};

#endif // GAMEUNITHELPER_H