#ifndef CONNECTORLOADGAME_H
#define CONNECTORLOADGAME_H

class MapView;
class GameDemonstrator;

class ConnectorLoadGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorLoadGame();
public slots:
	/** */
	void SlotLoadSaveGame();
private:
	friend class GameDemonstrator;
	MapView*			MapViewObject;
	GameDemonstrator*	GameDemonstratorObject;

};

#endif // CONNECTORLOADGAME_H