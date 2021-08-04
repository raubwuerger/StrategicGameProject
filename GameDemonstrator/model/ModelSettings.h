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
	//Theese attributes couldn't be read from config file. Bootstrapping!!!
	QString	RootName;
	QString ModelSettingsFileName;
public:
	QString SaveGamePath;
	QString DifficultyLevel;
	QString PlayerCount;
	QString CurrentSaveGameFileName;
	QString DefaultMapRows;
	QString DefaultMapCols;
	QVector<QString> Players;

};
