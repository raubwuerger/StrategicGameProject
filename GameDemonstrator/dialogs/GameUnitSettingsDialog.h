#ifndef GAMEUNITSETTINGSDIALOG_H
#define GAMEUNITSETTINGSDIALOG_H

#include <QWidget>
#include "ui_GameUnitSettingsDialog.h"

class ModelUnitTypeStatistics;
class ModelUnitType;

class GameUnitSettingsDialog : public QDialog
{
	Q_OBJECT
public:
	/** */
	GameUnitSettingsDialog(QWidget *parent = 0);
	/** */
	void SetName(const QString& name);
	/** */
	void SetStrength(const QString& strength);
	/** */
	void SetStrengthColor(const QColor& color);
	/** */
	void SetMovementPoints(const QString& movement);
	/** */
	void SetMovementPointsColor(const QColor& color);
	/** */
	void SetOwner(const QString& owner);
	/** */
	void SetOwnerColor(const QColor& color);
	/** */
	bool GetNameChanged() const;
	/** */
	QString GetName() const;
	/** */
	void SetModelUnitType(const ModelUnitType* modelUnitType);
private:
	/** */
	QColor GetAdjustedTextColor(const QColor& color);
private:
	Ui::GameUnitSettingsDialog	ui;
	QString						OriginalName;
	ModelUnitTypeStatistics*	ModelUnitTypeStatisticsObject;
};

#endif // GAMEUNITSETTINGSDIALOG_H