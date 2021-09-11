#ifndef GAMECONFIG_H
#define GAMECONFIG_H

class GameOwner;

class GameConfig
{
public:
	static QString			CurrentSaveGameName;
	static int				VersionMajor;
	static int				VersionMinor;
	static int				VersionRevision;
	static int				PlayerId;
	static int				PlayerCount;
	static int				CurrentTurn;
	static GameOwner*	Player;
	static int				DifficultyLevel;
	static QString			MapType;
	static int				MapRows;
	static int				MapCols;
};

#endif // GAMECONFIG_H