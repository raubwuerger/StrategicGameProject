#pragma once

/** This class holds all game settings */

class GameSettings
{
public:
	/** */
	GameSettings();
	/** */
	~GameSettings();
public:
	QString SaveGamePath;
	QString DifficultyLevel;
	QString PlayerCount;
	QVector<QString> Players;

};
