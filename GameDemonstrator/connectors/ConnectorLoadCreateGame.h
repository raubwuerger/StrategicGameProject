#ifndef CONNECTORLOADCREATEGAME_H
#define CONNECTORLOADCREATEGAME_H

class MapView;

/** K�mmert sich um das Erstellen eines neuen Spiels */
class ConnectorLoadCreateGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorLoadCreateGame();
public slots:
	/** */
	void SlotCreateNewGame();
private:
	friend class GameDemonstrator;
	MapView*			MapViewObject;
};

#endif // CONNECTORLOADCREATEGAME_H



