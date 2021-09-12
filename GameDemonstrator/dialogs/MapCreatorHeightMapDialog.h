#ifndef MAPCREATORHEIGHTMAPDIALOG_H
#define MAPCREATORHEIGHTMAPDIALOG_H

#include <QWidget>
#include "ui_MapCreatorHeightMapDialog.h"
#include "mapCreator\GameMapCreatorHeightMapData.h"

class MapCreatorHeightMapDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	MapCreatorHeightMapDialog(QWidget *parent = 0);
signals:
	/** */
	void SignalGameMapCreationData(GameMapCreatorHeightMapData creationData);
private:
	/** */
	void UpdateAndSendCreationData();
	/** */
	void InitCreationData();
private:
	Ui::MapCreatorHeightMapDialog ui;
};

#endif // MAPCREATORHEIGHTMAPDIALOG_H