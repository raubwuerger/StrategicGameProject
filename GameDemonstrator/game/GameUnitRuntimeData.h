#ifndef GAMEUNITRUNTIMEDATA_H
#define GAMEUNITRUNTIMEDATA_H

class GameUnit;

class GameUnitRuntimeData
{
public:
	int	BaseStrength;
	int CurrentStrength;
	int BaseMovementPoints;
	int CurrentMovementPoints;
	int TransportCapacity;
	QVector<GameUnit*>	TransportedGameUnitIds;
};

#endif GAMEUNITRUNTIMEDATA_H