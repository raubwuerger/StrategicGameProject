#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class GameOwnerItem;

class GameConfig
{
public:
	static QString			CurrentSaveGameName;
	static QString			CurrentTurn;
	static QString			DifficultyLevel;
	static QString			PlayerCount;
	static QString			MapType;
	static GameOwnerItem*	Player;
	static int				MapRows;
	static int				MapCols;
};

#endif // GAMECONFIG_H