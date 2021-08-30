#ifndef GAMEMAINDIALOG_H
#define GAMEMAINDIALOG_H

#include <QtWidgets>
#include "ui_GameMainDialog.h"

class GameDemonstrator;

class GameMainDialog: public QDialog
{
public:
	/** */
	GameMainDialog(QWidget *parent = 0);
	/** */
	void Init(GameDemonstrator* gameDemonstrator);
public:
	Ui::GameMainDialog ui;
private:
	GameDemonstrator* GameDemonstratorObject;
};

#endif // GAMEMAINDIALOG_H
