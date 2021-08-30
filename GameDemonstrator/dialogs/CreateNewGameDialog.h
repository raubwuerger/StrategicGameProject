#ifndef CREATENEWMAPDIALOG_H
#define CREATENEWMAPDIALOG_H

#include <QWidget>
#include "ui_CreateNewMapDialog.h"

/** @stereotype BorlandFormclass*/
class CreateNewGameDialog : public QDialog
{
	Q_OBJECT

public:
	/** */
	CreateNewGameDialog(QWidget *parent = 0);
	/** */
	~CreateNewGameDialog();
	/** */
	int GetTilesRows() const;
	/** */
	int GetTilesCols() const;
	/** */
	int GetOwnerTypeId() const;
	/** */
	int GetOpponentCount() const;
	/** */
	int GetDifficultyLevel() const;
private:
	Ui::CreateNewMapDialog ui;
};

#endif // CREATENEWMAPDIALOG_H
