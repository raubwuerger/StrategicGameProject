#ifndef GAMECITYINFODIALOG_H
#define GAMECITYINFODIALOG_H

#include <QtWidgets>
#include "ui_GameCityInfoDialog.h"


class GameCityInfoDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	GameCityInfoDialog(QWidget *parent = 0);
	/** */
	void SetId(const QString& id) { ui.lineEditId->setText(id);  }
	/** */
	void SetName(const QString& name) { ui.lineEditName->setText(name); }
	/** */
	void SetOwner(const QString& owner) { ui.lineEditOwner->setText(owner); }
	/** */
	void SetOwnerColor( QColor ownerColor);
	/** */
	void SetEfficiency(const QString& efficiency) { ui.lineEditEfficiency->setText(efficiency); }
	/** */
	void SetSpecialization(const QString& specialization) { ui.lineEditSpecialization->setText(specialization); }
	/** */
	void SetStrength(const QString& strength) { ui.lineEditStrength->setText(strength); }
private:
	Ui::GameCityInfoDialog ui;
};

#endif // GAMECITYINFODIALOG_H