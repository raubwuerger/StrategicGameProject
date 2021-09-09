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
	QVector<QGroupBox*>	ProductionItemGroups;
};

#endif // MAPCITYSETTINGSDIALOG_H