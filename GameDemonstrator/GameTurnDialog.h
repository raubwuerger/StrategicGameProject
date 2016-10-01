#ifndef GAMETURNDIALOG_H
#define GAMETURNDIALOG_H

#include <QWidget>
#include "ui_GameTurnDialog.h"

/** @stereotype BorlandFormclass*/
class CGameTurnDialog : public QWidget
{
	Q_OBJECT

public:
	/** */
	CGameTurnDialog(QWidget *parent = 0);
	/** */
	~CGameTurnDialog();
public slots:
	void UpdateGameTurnInfo( QDate date );
private:
	Ui::GameTurnDialog ui;
};

#endif // GAMETURNDIALOG_H
