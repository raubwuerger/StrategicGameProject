#ifndef GAMEUNITHELPER_H
#define GAMEUNITHELPER_H

class GameUnit;

class GameUnitHelper
{
public:
	/** */
	GameUnitHelper(GameUnit* gameUnit);
	/** */
	bool MoveToPosition(int mapId);
	/** */
	static bool IsEnemyOnDestinationMapTile(const GameUnit*	gameUnit, int gameMapItemId);
	/** */
	static bool IsOwnUnitOnDestinationMapTile(const GameUnit* gameUnit, int gameMapItemId);
	/** */
	static int GetMapHexItemId(const GameUnit* gameUnit);
	/** */
	static const GameUnit* GetEnemyGameUnit(int mapItemId);
	/** */
	static bool IsTransporter(const GameUnit* gameUnit);
private:
	/** Default Constructor forbidden */
	GameUnitHelper() {}
	/** */
	void SetNewMapId(int mapId);
	/** */
	void MoveTransportedUnits(int mapId);
private:
	GameUnit*	GameUnitObject;
};

#endif // GAMEUNITHELPER_H