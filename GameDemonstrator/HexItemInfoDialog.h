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
private:
	friend class CMapEventManager;
	Ui::HexItemInfoDialog ui;
};

#endif // HEXITEMINFODIALOG_H
