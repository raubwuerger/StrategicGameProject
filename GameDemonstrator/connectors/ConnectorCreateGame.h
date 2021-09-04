#ifndef CONNECTORCREATEGAME_H
#define CONNECTORCREATEGAME_H

class MapView;
class CreateNewGameDialog;

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
	/** */
	void GetGameCreationData(const CreateNewGameDialog* dialog);
private:
	friend class GameDemonstrator;
	MapView*			MapViewObject;
};

#endif // CONNECTORCREATEGAME_H



