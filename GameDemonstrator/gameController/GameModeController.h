#ifndef GAMEMODECONTROLLER_H
#define GAMEMODECONTROLLER_H

class GameDemonstrator;
class GameMode;
class GameMainDialog;
class GameController;
class MapView;

/** Handles the differen GameModes */
class GameModeController : public QObject
{
	Q_OBJECT
public:
	/** */
	GameModeController();
	/** */
	bool Init(GameDemonstrator* gameDemonstrator);
public slots:
	/** */
	void LoadGame();
	/** */
	void CreateGame();
	/** */
	void SlotModeEditorActivated();
	/** */
	void SlotModeSinglePlayerActivated();
signals:
	/** */
	void LoadSavedGame();
	/** */
	void CreateNewGame();
private:
	/** */
	void CreateGameModes( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntryGameMode( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntryEditor( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntrySinglePlayer( GameDemonstrator* gameDemonstrator );
private:
	friend class GameFactory;
	GameMainDialog*		GameMainDialogObject;
	GameController*		GameControllerObject;
	MapView*			MapViewObject;
	GameMode*			CurrentGameMode;
	GameMode*			GameModeEditorObject;
	GameMode*			GameModeSinglePlayerObject;
	static QMenu*		GameModeChangeMenu;
};

#endif // GAMEMODECONTROLLER_H