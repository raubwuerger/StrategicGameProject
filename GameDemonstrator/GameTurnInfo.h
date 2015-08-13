#ifndef GAMETURNINFO_H
#define GAMETURNINFO_H

#include <QDialog>
#include "ui_GameTurnInfo.h"

class GameTurnInfo : public QDialog
{
	Q_OBJECT

public:
	GameTurnInfo(QWidget *parent = 0);
	~GameTurnInfo();

private:
	Ui::GameTurnInfo ui;
};

#endif // GAMETURNINFO_H
