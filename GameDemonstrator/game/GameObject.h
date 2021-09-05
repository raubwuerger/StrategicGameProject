#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObjectController;

/** 
*	This class is responsible for turn actions. Restore movement points, hit points, build steps (cities)
*/

class GameObject
{
public:
	/** */
	GameObject();
	/** */
	virtual void UpdateTurn() const = 0;
	/** */
	virtual bool Move() const = 0;
	/** */
	virtual void Attacks() const = 0;
	/** */
	virtual void Defends() const = 0;
	/** */
	virtual void SetUID(int uid);
	/** */
	bool operator==(const GameObject& rhs) const;
private:
	friend class GameObjectController;
	int	UID;
};

#endif // GAMEOBJECT_H