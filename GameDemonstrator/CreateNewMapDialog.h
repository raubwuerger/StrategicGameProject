#ifndef CREATENEWMAPDIALOG_H
#define CREATENEWMAPDIALOG_H

#include <QWidget>
#include "ui_CreateNewMapDialog.h"

class CreateNewMapDialog : public QDialog
{
	Q_OBJECT

public:
	CreateNewMapDialog(QWidget *parent = 0);
	~CreateNewMapDialog();

private:
	Ui::CreateNewMapDialog ui;
};

#endif // CREATENEWMAPDIALOG_H
