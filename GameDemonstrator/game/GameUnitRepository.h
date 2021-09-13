#ifndef GAMEUNITREPOSITORY_H
#define GAMEUNITREPOSITORY_H

#include "BaseRepository.h"
class GameUnit;

/** Repr�sentiert die Karte im Speicher */
class GameUnitRepository : public BaseRepository
{
public:
	/** */
	static GameUnitRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** */
	bool Register(GameUnit* gameUnit);
	/** */
	int GetCount() const;
	/** */
	QMap<int, GameUnit*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameUnit*>::const_iterator GetLastIterator() const;
	/** */
	GameUnit* GetById(int id);
	/** */
	const GameUnit* GetByGameMapTileId(int gameMapTileId);
	/** */
	int CreateNewId() const;
	/** */
	bool IsGameUnitOnGameMapTile(int gameMapTileId) const;
	/** */
	GameUnit* RemoveGameUnitByGameMapTileId(int gameMapTileId);
	/** */
	GameUnit* RemoveGameUnit(const GameUnit* gameUnit);
	/** */
	bool UpdateGameUnitOnGameMapTile(const GameUnit* movedUnit, int oldMapId);
private:
	/** */
	GameUnitRepository();
	/** */
	~GameUnitRepository();
	/** */
	bool UpdateGameUnitOnGameMapTile(const GameUnit* gameUnit);
	/** */
	int GenerateUID(const GameUnit*gameUnit);
public:
	const int						UID;
private:
	friend class GameUnitFactory;
	static GameUnitRepository*	Instance;
	QMap<int, GameUnit*>		GameUnits;
	QMap<int, int>				GameUnitsOnGameMapTile;
};

#endif // GAMEUNITREPOSITORY_H