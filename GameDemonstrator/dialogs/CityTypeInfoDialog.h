#ifndef CITYTYPEINFODIALOG_H
#define CITYTYPEINFODIALOG_H

#include <QWidget>
#include "ui_CityTypeInfoDialog.h"

class CityTypeInfoDialog : public QWidget
{
	Q_OBJECT

public:
	/** */
	CityTypeInfoDialog(QWidget *parent = 0);
	/** */
	~CityTypeInfoDialog();
	/** */
	void SetId(const QString& id);
	/** */
	void SetName(const QString& name);
	/** */
	void SetType(const QString& type);
	/** */
	void SetMapItemId(const QString& mapItemId);
private:
	Ui::CityTypeInfoDialog ui;
};


#endif // CITYTYPEINFODIALOG_H