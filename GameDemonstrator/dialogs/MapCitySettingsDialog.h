#ifndef MAPCITYSETTINGSDIALOG_H
#define MAPCITYSETTINGSDIALOG_H

#include <QWidget>
#include "ui_MapCitySettingsDialog.h"


class MapCitySettingsDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	MapCitySettingsDialog(QWidget *parent = 0);
private:
	Ui::CityEditDialog ui;
};

#endif // MAPCITYSETTINGSDIALOG_H