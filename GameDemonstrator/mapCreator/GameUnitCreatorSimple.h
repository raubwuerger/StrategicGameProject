#ifndef GAMEUNITCREATORSIMPLE_H
#define GAMEUNITCREATORSIMPLE_H

#include "GameUnitCreatorInterface.h"
class GameUnitParameterObject;

class GameUnitCreatorSimple : public GameUnitCreatorInterface
{
public:
	/** */
	GameUnitCreatorSimple();
	/** */
	~GameUnitCreatorSimple();
	/** */
	bool Create() override;
private:
	/** */
	GameUnitParameterObject* CreateDefaultGameUnitParameterObject( int mapTileId, int ownerTypeId ) const;
private:
	GameUnitParameterObject*  GameUnitParameterObjectTemporary;
};

#endif // GAMEUNITCREATORSIMPLE_H