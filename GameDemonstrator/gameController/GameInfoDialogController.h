#ifndef GAMEINFODIALOGCONTROLLER_H
#define GAMEINFODIALOGCONTROLLER_H

class MapView;
class GameTurnDialog;
class GameUnitInfoDialog;
class GameCityInfoDialog;
class GameUnitItem;
class GameDemonstrator;
class GameCityItem;
class GameCitySettingsDialog;
class CityUnitProductionController;

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
	void CreateGameCityConnections();
	/** */
	void CreateControllerCityGameUnitProduction();
	/** */
	QString CreateUnitMovementPoints(const GameUnitItem* gameUnit) const;
	/** */
	QColor CreateMovementColor(const GameUnitItem* gameUnit) const;
	/** */
	QString CreateUnitStrength(const GameUnitItem* gameUnit) const;
	/** */
	QColor CreateStrengthColor(const GameUnitItem* gameUnit) const;
	/** */
	QString CreateCityEfficiency(const GameCityItem* gameCity) const;
	/** */
	QString CreateCityStrength(const GameCityItem* gameCity)  const;
	/** */
	QString GetSpecializedUnitName(const GameCityItem* gameCity);
	/** */
	QString GetUnitType(int id);
	/** */
	QString GetProducedUnitName(int gameUnitId) const;
private:
	friend class GameFactory;
	QVector<QDockWidget*>	DockWidgets;
	MapView*				MapViewObject;
	GameDemonstrator*		GameDemonstratorObject;
	GameTurnDialog*			GameTurnDialogObject;
	GameUnitInfoDialog*		GameUnitInfoDialogObject;
	GameCityInfoDialog*		GameCityInfoDialogObject;
	GameCitySettingsDialog*	GameCitySettingsDialogObject;
	CityUnitProductionController*	ControllerCityGameUnitProductionObject;
	QColor					LightRed;
	QColor					LightYellow;
	QColor					LightGreen;
};

#endif // GAMEINFODIALOGCONTROLLER_H