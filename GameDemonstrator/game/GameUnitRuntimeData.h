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
	int TransportCapacity;
	QVector<GameUnit*>	TransportedGameUnits;
};

#endif GAMEUNITRUNTIMEDATA_H