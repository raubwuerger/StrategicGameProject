#pragma once

/** This class holds all game settings */

class ModelSettings
{
public:
	/** */
	ModelSettings();
	/** */
	~ModelSettings();
public:
	QString SaveGamePath;
	QString DifficultyLevel;
	QString PlayerCount;
	QString CurrentSaveGameFileName;
	QVector<QString> Players;

};
