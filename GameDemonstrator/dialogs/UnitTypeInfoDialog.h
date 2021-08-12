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
	/** */
	void SetId(const QString& id);
	/** */
	void SetName(const QString& name);
	/** */
	void SetType(const QString& type);
private:
	Ui::UnitTypeInfoDialog ui;
};


#endif // UNITTYPEINFODIALOG_H