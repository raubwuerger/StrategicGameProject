#ifndef HEXITEMINFODIALOG_H
#define HEXITEMINFODIALOG_H

#include <QWidget>
#include "ui_HexItemInfoDialog.h"

/** @stereotype BorlandFormclass*/
class HexItemInfoDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	HexItemInfoDialog(QWidget *parent = 0);
	/** */
	~HexItemInfoDialog();
	/** */
	void SetId(const QString& id);
	/** */
	void SetRow(const QString& row);
	/** */
	void SetCol(const QString& col);
	/** */
	void SetTerrainName(const QString& terrainTypeName);
private:
	Ui::HexItemInfoDialog ui;
};

#endif // HEXITEMINFODIALOG_H
