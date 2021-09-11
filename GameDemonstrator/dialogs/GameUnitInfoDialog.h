#ifndef GAMEUNITINFODIALOG_H
#define GAMEUNITINFODIALOG_H

#include <QtWidgets>
#include "ui_GameUnitInfoDialog.h"

class GameUnitInfoDialog : public QWidget
{
	Q_OBJECT
public:
	/** */
	GameUnitInfoDialog(QWidget *parent = 0);
	/** */
	void SetId(const QString& id);
	/** */
	void SetName(const QString& name);
	/** */
	void SetType(const QString& type);
	/** */
	void SetMovementPoints(const QString& movement);
	/** */
	void SetMovementPointsColor(const QColor& color);
	/** */
	void SetStrength(const QString& strength);
	/** */
	void SetStrengthColor(const QColor& color);
	/** */
	void SetOwner(const QString& owner);
	/** */
	void SetOwnerColor(const QColor& color);
private:
	Ui::GameUnitInfoDialog ui;
};

#endif // GAMEUNITINFODIALOG_H