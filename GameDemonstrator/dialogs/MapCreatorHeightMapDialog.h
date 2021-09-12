#ifndef MAPCREATORHEIGHTMAPDIALOG_H
#define MAPCREATORHEIGHTMAPDIALOG_H

#include <QWidget>
#include "ui_MapCreatorHeightMapDialog.h"

class MapCreatorHeightMapDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	MapCreatorHeightMapDialog(QWidget *parent = 0);
private:
	Ui::MapCreatorHeightMapDialog ui;
};

#endif // MAPCREATORHEIGHTMAPDIALOG_H