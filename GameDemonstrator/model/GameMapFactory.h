#pragma once

/** This class holds all game settings */

/** Repr�sentiert die Karte im Speicher */
class GameMapFactory : public QObject
{
public:
	/** */
	GameMapFactory();
	/** */
	~GameMapFactory();
	/** */
	void Create();
	/** */
	void Release();
public slots:
	void CreateMap();
private:
};
