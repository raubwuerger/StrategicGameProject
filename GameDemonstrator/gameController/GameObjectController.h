#ifndef GAMEOBJECTCONTROLLER_H
#define GAMEOBJECTCONTROLLER_H

class GameObject;

#include "BaseRepository.h"

class GameObjectController : public QObject
{
	Q_OBJECT
public:
	/** */
	static GameObjectController* GetInstance();
	/** */
	bool RegisterObject(const GameObject* object);
	/** */
	bool UnregisterObject(const GameObject* object);
	/** */
	bool Init();
	/** */
	void Release();
public slots:
	/** */
	void SlotDoUpdateTurn();
private:
	/** */
	GameObjectController();
	/** */
	bool CheckIfGameObjectIsOfTypeGameCity(const GameObject* object) const;
private:
	static GameObjectController*	Instance;
	QMap<int,const GameObject*>		GameObjects;
};

#endif // GAMEOBJECTCONTROLLER_H