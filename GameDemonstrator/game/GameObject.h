#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/** 
*	This class is responsible for turn actions. Restore movement points, hit points, build steps (cities)
*/

class GameObject
{
public:
	/** */
	virtual void UpdateTurn() = 0;
};

#endif // GAMEOBJECT_H