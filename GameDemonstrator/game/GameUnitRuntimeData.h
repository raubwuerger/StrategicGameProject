#ifndef GAMEUNITRUNTIMEDATA_H
#define GAMEUNITRUNTIMEDATA_H

class GameUnitRuntimeData
{
public:
	int	BaseStrength;
	int CurrentStrength;
	int BaseMovementPoints;
	int CurrentMovementPoints;
	int TransportCapacity;
	QVector<int>	TransportedGameUnitIds;
};

#endif GAMEUNITRUNTIMEDATA_H