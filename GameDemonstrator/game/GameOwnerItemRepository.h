#ifndef GAMEOWNERTYPEREPOSITORY_H
#define GAMEOWNERTYPEREPOSITORY_H

class GameOwnerItem;

#include "BaseRepository.h"

class GameOwnerItemRepository : public BaseRepository
{
public:
	/** */
	static GameOwnerItemRepository* GetInstance();
	/** */
	void Release() override;
	/** */
	bool Init() override;
	/** */
	bool RegisterItem(GameOwnerItem* item);
	/** */
	const GameOwnerItem* GetItemById( int id ) const;
	/** */
	QMap<int, GameOwnerItem*>::const_iterator GetFirstIterator() const;
	/** */
	QMap<int, GameOwnerItem*>::const_iterator GetLastIterator() const;
	/** */
	const GameOwnerItem* GetHuman() const;
	/** */
	int CreateNewId();
	/** */
	int GetItemCount() const;
	/** */
	const GameOwnerItem* GetDefaultOwnerType() const;
private:
	/** */
	GameOwnerItemRepository();
private:
	static GameOwnerItemRepository*	Instance;
	QMap<int, GameOwnerItem*>	GameOwnerItems;
	int		DefaultGameOwnerTypeId;

};

#endif // GAMEOWNERTYPEREPOSITORY_H