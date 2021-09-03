#ifndef GAMEINFODIALOGCONTROLLER_H
#define GAMEINFODIALOGCONTROLLER_H

class MapView;
class GameTurnDialog;
class GameUnitInfoDialog;
class GameCityInfoDialog;
class GameUnitItem;
class GameDemonstrator;

/** Controlls and connects all game info dialogs */
class GameInfoDialogController : public QObject
{
	Q_OBJECT
public:
	/** */
	GameInfoDialogController();
	/** */
	void Init();
	/** */
	void ShowDockWidgets();
	/** */
	void HideDockWidgets();
public slots:
	/** */
	void SlotShowGameUnitInfo(int gameUnitId);
private:
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	void CreateGameUnitInfoDialog();
	/** */
	QString CreateMovement(const GameUnitItem* gameUnit);
	/** */
	QString CreateStrength(const GameUnitItem* gameUnit);
private:
	friend class GameFactory;
	QVector<QDockWidget*>	DockWidgets;
	MapView*				MapViewObject;
	GameDemonstrator*		GameDemonstratorObject;
	GameTurnDialog*			GameTurnDialogObject;
	GameUnitInfoDialog*		GameUnitInfoDialogObject;
	GameCityInfoDialog*		GameCityInfoDialogObject;
};

#endif // GAMEINFODIALOGCONTROLLER_H