#ifndef GAMEUNITRUNTIMEDATA_H
#define GAMEUNITRUNTIMEDATA_H

class GameUnit;

class GameUnitRuntimeData
{
public:
	/** */
	GameUnitRuntimeData();
public:
	int	BaseStrength;
	int CurrentStrength;
	int BaseMovementPoints;
	int CurrentMovementPoints;
};

#endif GAMEUNITRUNTIMEDATA_H