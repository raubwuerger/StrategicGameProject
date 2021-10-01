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
	void SetId(const QString& id);
	/** */
	void SetName(const QString& name);
	/** */
	void SetOwner(const QString& owner);
	/** */
	void SetOwnerColor( QColor ownerColor);
	/** */
	void SetEfficiency(const QString& efficiency);
	/** */
	void SetSpecialization(const QString& specialization);
	/** */
	void SetStrength(const QString& strength);
	/** */
	void SetProductionProgress(int productionPorgress);
	/** */
	void SetProductionText( const QString& productionText);
private:
	Ui::GameCityInfoDialog ui;
};

#endif // GAMECITYINFODIALOG_H