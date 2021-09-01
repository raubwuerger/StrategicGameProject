#ifndef CONNECTORCREATEGAME_H
#define CONNECTORCREATEGAME_H

class MapView;

/** Kümmert sich um das Erstellen eines neuen Spiels */
class ConnectorCreateGame : public QObject
{
	Q_OBJECT
public:
	/** */
	ConnectorCreateGame();
public slots:
	/** */
	void SlotCreateNewGame();
private:
	friend class GameDemonstrator;
	MapView*			MapViewObject;
};

#endif // CONNECTORCREATEGAME_H



