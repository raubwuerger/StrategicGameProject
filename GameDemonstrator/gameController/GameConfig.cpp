#include "stdafx.h"
#include "GameConfig.h"

QString			GameConfig::CurrentSaveGameName = ".\\savegames\\PlayerName_1900_01.xml";
QString			GameConfig::CurrentTurn = "";
QString			GameConfig::DifficultyLevel = "1";
QString			GameConfig::PlayerCount = "2";
QString			GameConfig::MapType = "1";
GameOwnerItem*	GameConfig::Player = nullptr;
int				GameConfig::MapRows = 3;
int				GameConfig::MapCols = 3;



