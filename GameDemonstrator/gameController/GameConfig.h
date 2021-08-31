#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class ModelOwnerType;

class GameConfig
{
public:
	static QString			CurrentSaveGameName;
	static QString			CurrentTurn;
	static QString			DifficultyLevel;
	static QString			PlayerCount;
	static QString			MapType;
	static QString			PlayerId;
	static ModelOwnerType*	OwnerType;
};

#endif // GAMECONFIG_H