#ifndef GAMEUNITINFODIALOG_H
#define GAMEUNITINFODIALOG_H

#include <QtWidgets>
#include "ui_GameUnitInfoDialog.h"

class GameUnitInfoDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	GameUnitInfoDialog(QWidget *parent);
	/** */
	void SetId(const QString& id) { ui.lineEditId->setText(id); }
	/** */
	void SetName(const QString& name) { ui.lineEditName->setText(name); }
	/** */
	void SetType(const QString& type) { ui.lineEditType->setText(type); }
	/** */
	void SetMovement(const QString& movement) { ui.lineEditTypeMovement->setText(movement); }
	/** */
	void SetStrength(const QString& strength) { ui.lineEditStrength->setText(strength); }
private:
	Ui::GameUnitInfoDialog ui;
};

#endif // GAMEUNITINFODIALOG_H