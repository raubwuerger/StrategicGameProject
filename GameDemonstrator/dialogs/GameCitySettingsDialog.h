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
private:
	Ui::CityEditDialog ui;
};

#endif // MAPCITYSETTINGSDIALOG_H