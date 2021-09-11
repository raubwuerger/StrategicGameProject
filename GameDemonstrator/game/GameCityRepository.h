#ifndef GAMECITYREPOSITORY_H
#define GAMECITYREPOSITORY_H

#include "BaseRepository.h"

class GameCity;
class GameOwner;

/** Repräsentiert die Karte im Speicher */
class GameCityRepository : public BaseRepository
{
public:
	/** */
	static GameCityRepository* GetInstance();
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** */
	bool Register(GameCity* gameCity);
	/** */
	int GetCount() const;
	/** */
	QMap<int, GameCity*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameCity*>::const_iterator GetLastIterator() const;
	/** */
	GameCity* GetById(int id);
	/** */
	GameCity* RemoveById(int id);
	/** */
	GameCity* RemoveByGameMapTileId(int mapTileId);
	/** */
	bool IsCityOnGameMapTileId(int mapTileId) const;
	/** */
	GameCity* GetGameCityByGameMapTileId(int mapTileId);
	/** */
	int CreateNewId() const;
	/** */
	bool ChangeOwner(const GameCity* gameCity, const GameOwner* gameOwner);
private:
	/** */
	GameCityRepository();
	/** */
	~GameCityRepository();
	/** */
	bool UpdateGameCitysOnGameMapTile(const GameCity* gameUnit);
	/** */
	int GenerateUID(GameCity* gameCity);
public:
	const int						UID;
private:
	friend class GameCityFactory;
	static GameCityRepository*	Instance;
	QMap<int, GameCity*>		GameCitys;
	QMap<int, int>				GameCitysOnGameMapTile;
};

#endif // GAMECITYREPOSITORY_H
