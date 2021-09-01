#ifndef CONNECTORLOADCREATEGAME_H
#define CONNECTORLOADCREATEGAME_H

class MapView;
class GameDemonstrator;

/** Erstellt alle Komponenten die für ein neues Spiel notwendig sind */
class ConnectorLoadCreateGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorLoadCreateGame();
	/** */
	~ConnectorLoadCreateGame();
	/** */
	void Release();
public slots:
	/** */
	void SlotCreateNewGame();
	/** */
	void SlotLoadSaveGame();
private:
	friend class GameDemonstrator;
	MapView*			MapViewObject;
	GameDemonstrator*	GameDemonstratorObject;
};

#endif // CONNECTORLOADCREATEGAME_H



