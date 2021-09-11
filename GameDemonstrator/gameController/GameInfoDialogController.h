#ifndef GAMEINFODIALOGCONTROLLER_H
#define GAMEINFODIALOGCONTROLLER_H

class MapView;
class GameTurnDialog;
class GameUnitInfoDialog;
class GameCityInfoDialog;
class GameUnitItem;
class GameDemonstrator;
class GameCity;
class GameCitySettingsDialog;
class GameUnitSettingsDialog;

/** Controlls and connects all game info dialogs */
class GameInfoDialogController : public QObject
{
	Q_OBJECT
public:
	/** */
	GameInfoDialogController();
	/** */
	~GameInfoDialogController();
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
	/** */
	void SlotShowGameCitySettingsDialog(int gameCityId);
	/** */
	void SlotShowGameItemSettinsDialog(int gameItemId);
private:
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	void CreateGameUnitInfoDialog();
	/** */
	void CreateGameCityInfoDialog();
	/** */
	void CreateGameCitySettingsDialog();
	/** */
	QColor CreateMovementColor(const GameUnitItem* gameUnit) const;
	/** */
	QColor CreateStrengthColor(const GameUnitItem* gameUnit) const;
	/** */
	QString CreateCityEfficiency(const GameCity* gameCity) const;
	/** */
	QString CreateCityStrength(const GameCity* gameCity)  const;
	/** */
	QString GetSpecializedUnitName(const GameCity* gameCity);
	/** */
	QString GetUnitType(int id);
	/** */
	QString GetProducedUnitName(int gameUnitId) const;
	/** */
	void CreateGameUnitSettingsDialog();
private:
	friend class GameFactory;
	QVector<QDockWidget*>	DockWidgets;
	MapView*				MapViewObject;
	GameDemonstrator*		GameDemonstratorObject;
	GameTurnDialog*			GameTurnDialogObject;
	GameUnitInfoDialog*		GameUnitInfoDialogObject;
	GameCityInfoDialog*		GameCityInfoDialogObject;
	GameCitySettingsDialog*	GameCitySettingsDialogObject;
	GameUnitSettingsDialog*	GameUnitSettingsDialogObject;
};

#endif // GAMEINFODIALOGCONTROLLER_H