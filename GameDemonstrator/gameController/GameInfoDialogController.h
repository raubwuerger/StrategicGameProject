#ifndef GAMEINFODIALOGCONTROLLER_H
#define GAMEINFODIALOGCONTROLLER_H

class MapView;
class GameTurnDialog;
class GameUnitInfoDialog;
class GameCityInfoDialog;
class GameUnitItem;
class GameDemonstrator;
class GameCityItem;

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
	/** */
	void SlotShowGameCityInfo(int gameCityId);
	/** */
	void SlotShowTurnInfoDialog();
private:
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	void CreateGameUnitInfoDialog();
	/** */
	void CreateGameCityInfoDialog();
	/** */
	QString CreateUnitMovementPoints(const GameUnitItem* gameUnit) const;
	/** */
	QString CreateUnitStrength(const GameUnitItem* gameUnit) const;
	/** */
	QString CreateCityEfficiency(const GameCityItem* gameCity) const;
	/** */
	QString CreateCityStrength(const GameCityItem* gameCity)  const;
	/** */
	QString GetSpecializedUnitName(const GameCityItem* gameCity);
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