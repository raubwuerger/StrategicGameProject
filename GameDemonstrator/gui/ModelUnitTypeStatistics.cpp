#include "stdafx.h"
#include "ModelUnitTypeStatistics.h"
#include "model\ModelUnitType.h"

ModelUnitTypeStatistics::ModelUnitTypeStatistics(QWidget* parent /*= 0*/)
	: QWidget(parent)
{
	Create();
}

void ModelUnitTypeStatistics::Fill(const ModelUnitType* modelUnitType)
{
	Q_ASSERT(modelUnitType);
	LabelUnitImage->setPixmap(QPixmap(modelUnitType->GetPictureName()));
	LineEditUnitType->setText(modelUnitType->GetName());
	LineEditUnitProductionCost->setText(QString::number(modelUnitType->GetProductionCost()));
	LineEditUnitMovementPoints->setText(QString::number(modelUnitType->GetMovementPoints()));
	LineEditUnitStrength->setText(QString::number(modelUnitType->GetStrength()));
	LineEditUnitRange->setText(QString::number(modelUnitType->GetRange()));
	CheckBoxUnitOccupyCity->setCheckState(modelUnitType->GetCanOccupieCity() ? Qt::Checked : Qt::Unchecked);
	CheckBoxUnitGetCounterAttack->setCheckState(modelUnitType->GetReceiveCounterattack() ? Qt::Checked : Qt::Unchecked);
}

void ModelUnitTypeStatistics::Clear()
{
	QString clear("---");
	LabelUnitImage->setPixmap(QPixmap());
	LineEditUnitType->setText(clear);
	LineEditUnitProductionCost->setText(clear);
	LineEditUnitMovementPoints->setText(clear);
	LineEditUnitStrength->setText(clear);
	LineEditUnitRange->setText(clear);
	CheckBoxUnitOccupyCity->setCheckState(Qt::Unchecked);
	CheckBoxUnitGetCounterAttack->setCheckState(Qt::Unchecked);
}

void ModelUnitTypeStatistics::Create()
{
	GroupBoxUnitStatistics = new QGroupBox("Unit statistics", this);
	GroupBoxUnitStatistics->setFixedSize(356, 561);
//	GroupBoxUnitStatistics->move(380, 120);
	GridLayoutUnitStatistics = new QGridLayout;
	LabelUnitImage = new QLabel();
	QPixmap unitPixmap;
	LabelUnitImage->setPixmap(unitPixmap);

	LabelUnitType = new QLabel("Unit type:");
	LineEditUnitType = new QLineEdit();
	LineEditUnitType->setEnabled(false);

	LabelProductionCost = new QLabel("Production cost:");
	LineEditUnitProductionCost = new QLineEdit();
	LineEditUnitProductionCost->setEnabled(false);

	LabelMovementPoints = new QLabel("Movement points:");
	LineEditUnitMovementPoints = new QLineEdit();
	LineEditUnitMovementPoints->setEnabled(false);

	LabelStrength = new QLabel("Strength:");
	LineEditUnitStrength = new QLineEdit();
	LineEditUnitStrength->setEnabled(false);

	LabelRange = new QLabel("Range:");
	LineEditUnitRange = new QLineEdit();
	LineEditUnitRange->setEnabled(false);

	LabelOccupyCity = new QLabel("Occupy city:");
	CheckBoxUnitOccupyCity = new QCheckBox();
	CheckBoxUnitOccupyCity->setEnabled(false);

	LabelCounterattack = new QLabel("Counterattack:");
	CheckBoxUnitGetCounterAttack = new QCheckBox();
	CheckBoxUnitGetCounterAttack->setEnabled(false);

	int rowIndex = 0;
	GridLayoutUnitStatistics->addWidget(LabelUnitImage, 0, 0);

	GridLayoutUnitStatistics->addWidget(LabelUnitType, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitType, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelProductionCost, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitProductionCost, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelMovementPoints, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitMovementPoints, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelStrength, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitStrength, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelRange, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitRange, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelOccupyCity, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(CheckBoxUnitOccupyCity, rowIndex, 2);

	GridLayoutUnitStatistics->addWidget(LabelCounterattack, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(CheckBoxUnitGetCounterAttack, rowIndex, 2);

	GroupBoxUnitStatistics->setLayout(GridLayoutUnitStatistics);
}
