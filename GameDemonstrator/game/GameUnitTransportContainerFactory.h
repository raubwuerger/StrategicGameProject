#ifndef GAMEUNITTRANSPORTCONTAINERFACTORY_H
#define GAMEUNITTRANSPORTCONTAINERFACTORY_H

class GameUnitTransportContainer;
class GameUnit;

class GameUnitTransportContainerFactory
{
public:
	/** */
	GameUnitTransportContainer* Create(const GameUnit* transporter);
private:
	/** */
	int FindCapacity(const GameUnit* transporter);
	/** */
	QString FindDomain(const GameUnit* transporter);
};

#endif // GAMEUNITTRANSPORTCONTAINERFACTORY_H