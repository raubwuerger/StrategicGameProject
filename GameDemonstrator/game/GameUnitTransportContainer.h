#ifndef GAMEUNITTRANSPORTCONTAINER_H
#define GAMEUNITTRANSPORTCONTAINER_H

class GameUnit;
class GameUnitTransportContainerFactory;

class GameUnitTransportContainer
{
public:
	/** */
	GameUnitTransportContainer();
	/** */
	GameUnitTransportContainer(const GameUnit* transporter);
	/** */
	bool GetIsValid() const;
	/** */
	int GetCount() const;
	/** */
	int GetCapacity() const;
	/** */
	const QString& GetDomain() const;
	/** */
	bool EmbarkUnit(GameUnit* toEmbark);
	/** */
	bool DisembarkUnit(GameUnit* toDisembark);
	/** */
	bool GetFreeCapacity() const;
	/** */
	GameUnit* GetAt(int index);
	/** */
	GameUnit* GetSelectedUnit() { return nullptr; }
	/** */
	void SelectNextUnit() {}
public:
	friend class GameUnitTransportContainerFactory;
	const GameUnit*		Transporter;
	int					Capacity;
	QString				Domain;
	QVector<GameUnit*>	TransportedUnits;
//	QList<GameUnit*>	
};

#endif // GAMEUNITTRANSPORTCONTAINER_H