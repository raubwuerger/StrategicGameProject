#ifndef GAMEUNITSTACKINGHELPER_H
#define GAMEUNITSTACKINGHELPER_H

class GameUnit;

class GameUnitStackingHelper
{
public:
	/** */
	GameUnitStackingHelper();
	/** Add a bunch of GameUnits. Typically the transported units */
	void AddGameUnits(const QVector<const GameUnit*>& gameUnits);
	/** Add a single GameUnit. Typically the transporter */
	void AddGameUnit(const GameUnit* gameUnit);
	/** */
	void Clear();
	/** */
	const GameUnit*	GetSelected() const;
	/** */
	void SetSelected(const GameUnit* selected);
	/** */
	const QVector<const GameUnit*>	GetNotSelected();
	/** */
	const GameUnit* Next();
private:
	/** */
private:
	QVector<const GameUnit*>	GameUnits;
	const GameUnit*				Selected;
};

#endif // GAMEUNITSTACKINGHELPER_H