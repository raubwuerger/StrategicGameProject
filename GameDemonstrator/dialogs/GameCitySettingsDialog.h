#ifndef GAMECITYSETTINGSDIALOG_H
#define GAMECITYSETTINGSDIALOG_H

#include <QWidget>
#include "ui_GameCitySettingsDialog.h"

class GameUnitProduction;
class ModelUnitType;

class GameCitySettingsDialog : public QDialog
{
	Q_OBJECT
public:
	/** */
	GameCitySettingsDialog(QWidget *parent = 0);
	/** */
	void SetName(const QString& name);
	/** */
	const QString GetName() const;
	/** */
	void SetEfficiency(const QString& efficiency) { ui.lineEditEfficiency->setText(efficiency); }
	/** */
	void SetStrength(const QString& strength) { ui.lineEditStrength->setText(strength); }
	/** */
	void SetSpecialization(const QString& specialization) { ui.lineEditSpecialization->setText(specialization); }
	/** */
	void SetGameUnitProduction(const GameUnitProduction* gameUnitProduction);
	/** */
	GameUnitProduction* GetChangedGameUnitProduction() const;
	/** */
	bool GetHasProductionChanged() const { return ProductionChanged; }
	/** */
	bool GetHaseNameChanged() const { return NameHasChanged; }
signals:
	/** */
	void SignalUnitProductionChanged(int unitTypeId);
public slots:
	/** */
	virtual void accept();
	/** */
	void SlotButtonPressedEfficiency();
	/** */
	void SlotButtonPressedInfantry();
	/** */
	void SlotButtonPressedTank();
	/** */
	void SlotButtonPressedArtillery();
	/** */
	void SlotButtonPressedFighter();
	/** */
	void SlotButtonPressedBomber();
	/** */
	void SlotButtonPressedDestroyer();
	/** */
	void SlotButtonPressedCruiser();
	/** */
	void SlotButtonPressedBattleship();
	/** */
	void SlotButtonPressedCarrier();
	/** */
	void SlotButtonPressedSubmarine();
	/** */
	void SlotButtonPressedTransport();
	/** */
	void SlotNameEdited(const QString & text);
private:
	/** */
	void InitProductionItems();
	/** */
	void ResetProductionItems();
	/** */
	void InitConnections();
	/** */
	void InitDialog();
	/** */
	void SetProductionHasChanged(int unitTypeId);
	/** */
	void SetGameUnitProduction(int unitTypeId);
	/** */
	void SetProductionProgress(const GameUnitProduction* gameUnitProduction);
	/** */
	int GetOriginalUnitTypeId() const;
	/** */
	int CreateProductionItemId(const GameUnitProduction* gameUnitProduction) const;
	/** */
	void ShowProductionItem(int unitTypeId);
	/** */
	void ShowProductionItem(int unitTypeId, QGridLayout* layout);
	/** */
	const QString& GetImagePathFromUnitItem(int unitTypeId) const;
	/** */
	const QString& GetImagePathFromCityItem() const;
	/** */
	void SetNameHasChanged();
private:
	/** */
	const ModelUnitType* GetModelUnitTypeFromGameUnitId(int gameUnitId) const;
	/** */
	QString GetImagePathFromItemId(int itemId) const;
	/** */
	void FillModelUnitTypeStatsWidget(const ModelUnitType* modelUnitType);
	/** */
	void CreateModelUnitTypeStatsWidget();
private:
	Ui::CityEditDialog ui;
	QVector<QProgressBar*>		ProductionItems;
	QVector<QGroupBox*>			ProductionItemGroups;
	const GameUnitProduction*	OriginalGameUnitProduction;
	GameUnitProduction*			ChangedGameUnitProduction;
	bool						ProductionChanged;
	bool						NameHasChanged;
	QString						OriginalName;
private:
	QLabel*						LabelUnitImage;
	QLabel*						LabelUnitType;
	QLineEdit*					lineEditName;
	QLabel*						LabelProductionCost;
	QLineEdit*					lineEditCost;
	QLabel*						LabelMovementPoints;
	QLineEdit*					lineEditMovement;
	QLabel*						LabelStrength;
	QLineEdit*					lineEditStrength;
	QLabel*						LabelRange;
	QLineEdit*					lineEditRange;
	QLabel*						LabelOccupyCity;
	QCheckBox*					occupyCity;
	QLabel*						LabelCounterattack;
	QCheckBox*					counterAttack;
};

#endif // GAMECITYSETTINGSDIALOG_H