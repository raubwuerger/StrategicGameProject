#ifndef GAMEOWNERTYPEREPOSITORY_H
#define GAMEOWNERTYPEREPOSITORY_H

class GameOwner;

#include "BaseRepository.h"

class GameOwnerRepository : public BaseRepository
{
public:
	/** */
	static GameOwnerRepository* GetInstance();
	/** */
	void Release() override;
	/** */
	bool Init() override;
	/** */
	bool Register(GameOwner* gameOwner);
	/** */
	const GameOwner* GetById( int id ) const;
	/** */
	QMap<int, GameOwner*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameOwner*>::const_iterator GetLastIterator() const;
	/** */
	const GameOwner* GetHuman() const;
	/** */
	int CreateNewId();
	/** */
	int GetCount() const;
	/** */
	const GameOwner* GetDefaultOwnerType() const;
private:
	/** */
	GameOwnerRepository();
private:
	static GameOwnerRepository*	Instance;
	QMap<int, GameOwner*>	GameOwners;
	int		DefaultGameOwnerTypeId;

};

#endif // GAMEOWNERTYPEREPOSITORY_H