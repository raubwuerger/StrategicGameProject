#ifndef MAPCITYSETTINGSDIALOG_H
#define MAPCITYSETTINGSDIALOG_H

#include <QWidget>
#include "ui_MapCitySettingsDialog.h"

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
	void SetProductionProgress(const GameUnitProduction* gameUnitProduction);
signals:
	/** */
	void SignalUnitProductionChanged(int unitTypeId);
public slots:
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
private:
	Ui::CityEditDialog ui;
	QVector<QProgressBar*>	ProductionItems;
	QVector<QGroupBox*>		ProductionItemGroups;
	QMap<QPushButton*, int>	ProductionChange;
};

#endif // MAPCITYSETTINGSDIALOG_H