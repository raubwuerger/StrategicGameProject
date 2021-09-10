#ifndef MODELUNITTYPESTATISTICS_H
#define MODELUNITTYPESTATISTICS_H

#include <QWidget>

class ModelUnitType;

class ModelUnitTypeStatistics : public QWidget
{
	Q_OBJECT
public:
	/** */
	ModelUnitTypeStatistics(QWidget* parent = 0);
	/** */
	void Fill(const ModelUnitType* modelUnitType);
	/** */
	void Clear();
private:
	/** */
	void Create();
public:
	QGroupBox*					GroupBoxUnitStatistics;
	QGridLayout*				GridLayoutUnitStatistics;
	QLabel*						LabelUnitImage;
	QLabel*						LabelUnitType;
	QLineEdit*					LineEditUnitType;
	QLabel*						LabelProductionCost;
	QLineEdit*					LineEditUnitProductionCost;
	QLabel*						LabelMovementPoints;
	QLineEdit*					LineEditUnitMovementPoints;
	QLabel*						LabelStrength;
	QLineEdit*					LineEditUnitStrength;
	QLabel*						LabelRange;
	QLineEdit*					LineEditUnitRange;
	QLabel*						LabelOccupyCity;
	QCheckBox*					CheckBoxUnitOccupyCity;
	QLabel*						LabelCounterattack;
	QCheckBox*					CheckBoxUnitGetCounterAttack;
};

#endif // MODELUNITTYPESTATISTICS_H