#ifndef CONNECTORSAVEGAME_H
#define CONNECTORSAVEGAME_H

class GameDemonstrator;

class ConnectorSaveGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorSaveGame();
public slots :
	/** */
	void SlotSaveGame();
private:
	friend class GameDemonstrator;
	GameDemonstrator*	GameDemonstratorObject;

};

#endif // CONNECTORSAVEGAME_H