#ifndef HEXITEMINFODIALOG_H
#define HEXITEMINFODIALOG_H

#include <QWidget>
#include "ui_HexItemInfoDialog.h"

/** @stereotype BorlandFormclass*/
class CHexItemInfoDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	CHexItemInfoDialog(QWidget *parent = 0);
	/** */
	~CHexItemInfoDialog();
	/** */
private:
	friend class CMapEventManager;
	Ui::HexItemInfoDialog ui;
};

#endif // HEXITEMINFODIALOG_H
