#include "stdafx.h"
#include "GameConfig.h"

QString			GameConfig::CurrentSaveGameName = ".\\savegames\\PlayerName_1900_01.xml";
int				GameConfig::VersionMajor = NOT_INITIALIZED_INT;
int				GameConfig::VersionMinor = NOT_INITIALIZED_INT;
int				GameConfig::VersionRevision = NOT_INITIALIZED_INT;
int				GameConfig::PlayerId = NOT_INITIALIZED_INT;
int				GameConfig::CurrentTurn = NOT_INITIALIZED_INT;
int				GameConfig::DifficultyLevel = NOT_INITIALIZED_INT;
int				GameConfig::PlayerCount = NOT_INITIALIZED_INT;
QString			GameConfig::MapType = NOT_INITIALIZED_STRING;
GameOwner*		GameConfig::Player = nullptr;
int				GameConfig::MapRows = 3;
int				GameConfig::MapCols = 3;



