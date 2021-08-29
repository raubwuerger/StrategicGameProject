#include "stdafx.h"
#include "UnitTypeInfoDialog.h"

UnitTypeInfoDialog::UnitTypeInfoDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

UnitTypeInfoDialog::~UnitTypeInfoDialog()
{

}

void UnitTypeInfoDialog::SetId(const QString& id)
{
	ui.lineEditId->setText(id);
}

void UnitTypeInfoDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}

void UnitTypeInfoDialog::SetType(const QString& type)
{
	ui.lineEditType->setText(type);
}

void UnitTypeInfoDialog::SetMapItemId(const QString& mapItemId)
{
	ui.lineEditMapId->setText(mapItemId);
}

void UnitTypeInfoDialog::SetOwnerName(const QString& ownerName)
{
	ui.lineEditOwner->setText(ownerName);
}
