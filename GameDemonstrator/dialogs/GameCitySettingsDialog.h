#ifndef GAMECITYSETTINGSDIALOG_H
#define GAMECITYSETTINGSDIALOG_H

#include <QWidget>
#include "ui_GameCitySettingsDialog.h"

class GameUnitProduction;

class GameCitySettingsDialog : public QDialog
{
	Q_OBJECT
public:
	/** */
	GameCitySettingsDialog(QWidget *parent = 0);
	/** */
	void SetName(const QString& name);
	/** */
	void SetEfficiency(const QString& efficiency) { ui.lineEditEfficiency->setText(efficiency); }
	/** */
	void SetStrength(const QString& strength) { ui.lineEditStrength->setText(strength); }
	/** */
	void SetSpecialization(const QString& specialization) { ui.lineEditSpecialization->setText(specialization); }
	/** */
	void SetGameUnitProduction(const GameUnitProduction* gameUnitProduction);
	/** */
	GameUnitProduction* GetGameUnitProduction() const;
	/** */
	bool GetHasProductionChanged() const { return HasProductionChanged; }
signals:
	/** */
	void SignalUnitProductionChanged(int unitTypeId);
public slots:
	/** */
	void SlotButtonPressedEfficiency();
	/** */
	void SlotButtonPressedInfantry();
	/** */
	void SlotButtonPressedTank();
	/** */
	void SlotButtonPressedArtillery();
	/** */
	void SlotButtonPressedFighter();
	/** */
	void SlotButtonPressedBomber();
	/** */
	void SlotButtonPressedDestroyer();
	/** */
	void SlotButtonPressedCruiser();
	/** */
	void SlotButtonPressedBattleship();
	/** */
	void SlotButtonPressedCarrier();
	/** */
	void SlotButtonPressedSubmarine();
	/** */
	void SlotButtonPressedTransport();
private:
	/** */
	void InitProductionItems();
	/** */
	void ResetProductionItems();
	/** */
	void InitConnections();
	/** */
	void InitDialog();
	/** */
	void SetProductionHasChanged(int unitTypeId);
	/** */
	void SetGameUnitProduction(int unitTypeId);
	/** */
	void SetProductionProgress(const GameUnitProduction* gameUnitProduction);
	/** */
	int GetOriginalUnitTypeId() const;
	/** */
	int CreateProductionItemId(const GameUnitProduction* gameUnitProduction) const;
private:
	Ui::CityEditDialog ui;
	QVector<QProgressBar*>		ProductionItems;
	QVector<QGroupBox*>			ProductionItemGroups;
	const GameUnitProduction*	OriginalGameUnitProduction;
	GameUnitProduction*			ChangedGameUnitProduction;
	bool						HasProductionChanged;
};

#endif // GAMECITYSETTINGSDIALOG_H