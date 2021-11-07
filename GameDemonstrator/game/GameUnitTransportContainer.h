#ifndef GAMEUNITTRANSPORTCONTAINER_H
#define GAMEUNITTRANSPORTCONTAINER_H

class GameUnit;
class GameUnitTransportContainerFactory;
class GameUnitStackingHelper;

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
	const GameUnit* GetAt(int index);
	/** */
	const GameUnit* GetSelectedUnit();
	/** */
	const GameUnit* SelectNextUnit();
	/** */
	const QVector<const GameUnit*> GetNotSelectedUnits();
private:
	/** */
	void UpdateStackingHelper();
public:
	friend class GameUnitTransportContainerFactory;
	const GameUnit*				Transporter;
	int							Capacity;
	QString						Domain;
	QVector<const GameUnit*>	TransportedUnits;

	GameUnitStackingHelper*	GameUnitStackingHelperObject;
};

#endif // GAMEUNITTRANSPORTCONTAINER_H