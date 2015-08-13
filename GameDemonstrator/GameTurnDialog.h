#ifndef GAMETURNDIALOG_H
#define GAMETURNDIALOG_H

#include <QWidget>
#include "ui_GameTurnDialog.h"

class GameTurnDialog : public QWidget
{
	Q_OBJECT

public:
	/** */
	GameTurnDialog(QWidget *parent = 0);
	/** */
	~GameTurnDialog();
public slots:
	void UpdateGameTurnInfo( QDate date );
private:
	Ui::GameTurnDialog ui;
};

#endif // GAMETURNDIALOG_H
