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
	void SetMapHexItemId(const QString& id);
	/** */
	void SetMapHexItemRow(const QString& row);
	/** */
	void SetMapHexItemCol(const QString& col);
	/** */
	void SetMapHexItemTerrainId(const QString& terrainTypeId);
private:
	Ui::HexItemInfoDialog ui;
};

#endif // HEXITEMINFODIALOG_H
