#ifndef MAPCITYSETTINGSDIALOG_H
#define MAPCITYSETTINGSDIALOG_H

#include <QWidget>
#include "ui_MapCitySettingsDialog.h"


class GameCitySettingsDialog : public QWidget
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
private:
	Ui::CityEditDialog ui;
};

#endif // MAPCITYSETTINGSDIALOG_H