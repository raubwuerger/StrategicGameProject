#ifndef CREATENEWMAPDIALOG_H
#define CREATENEWMAPDIALOG_H

#include <QWidget>
#include "ui_CreateNewMapDialog.h"

/** @stereotype BorlandFormclass*/
class CreateNewMapDialog : public QDialog
{
	Q_OBJECT

public:
	/** */
	CreateNewMapDialog(QWidget *parent = 0);
	/** */
	~CreateNewMapDialog();
	/** */
	int GetTilesX() const;
	/** */
	int GetTilesY() const;
private:
	Ui::CreateNewMapDialog ui;
};

#endif // CREATENEWMAPDIALOG_H
