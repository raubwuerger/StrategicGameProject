#ifndef GAMEMODECONTROLLER_H
#define GAMEMODECONTROLLER_H

class GameDemonstrator;
class GameMode;
class GameMainDialog;
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
signals:
	/** */
	void LoadSavedGame();
	/** */
	void CreateNewGame();
private:
	/** */
	void CreateGameModes( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntries( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntryEditor( GameDemonstrator* gameDemonstrator );
	/** */
	void CreateMenuEntrySinglePlayer( GameDemonstrator* gameDemonstrator );
private:
	friend class GameDemonstrator;
	GameMainDialog*		GameMainDialogObject;
	MapView*			MapViewObject;
	GameMode*			CurrentGameMode;
	GameMode*			GameModeEditorObject;
	GameMode*			GameModeSinglePlayerObject;
	static QMenu*		GameModeChangeMenu;
};

#endif // GAMEMODECONTROLLER_H