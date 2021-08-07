#ifndef UNITTYPEINFODIALOG_H
#define UNITTYPEINFODIALOG_H

#include <QWidget>
#include "ui_UnitTypeInfoDialog.h"

class UnitTypeInfoDialog : public QWidget
{
	Q_OBJECT

public:
	/** */
	UnitTypeInfoDialog(QWidget *parent = 0);
	/** */
	~UnitTypeInfoDialog();
private:
	Ui::UnitTypeInfoDialog ui;
};


#endif // UNITTYPEINFODIALOG_H