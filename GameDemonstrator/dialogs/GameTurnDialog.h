#ifndef GAMETURNDIALOG_H
#define GAMETURNDIALOG_H

#include <QWidget>
#include "ui_GameTurnDialog.h"

/** @stereotype BorlandFormclass*/
class GameTurnDialog : public QWidget
{
	Q_OBJECT

public:
	/** */
	GameTurnDialog(QWidget *parent = 0);
	/** */
	~GameTurnDialog();
	/** */
	void SetGameTurn(const QString& gameTurn);
	/** */
	void SetPlayerName(const QString& playerName);
	/** */
	void SetPlayerColor(QColor color);
private:
	/** */
	void SetPlayerTextColor(QColor color);
private:
	Ui::GameTurnDialog ui;
};

#endif // GAMETURNDIALOG_H
