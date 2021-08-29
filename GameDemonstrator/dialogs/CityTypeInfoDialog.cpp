#include "stdafx.h"
#include "CityTypeInfoDialog.h"

CityTypeInfoDialog::CityTypeInfoDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CityTypeInfoDialog::~CityTypeInfoDialog()
{

}

void CityTypeInfoDialog::SetId(const QString& id)
{
	ui.lineEditId->setText(id);
}

void CityTypeInfoDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}

void CityTypeInfoDialog::SetType(const QString& type)
{
	ui.lineEditType->setText(type);
}

void CityTypeInfoDialog::SetMapItemId(const QString& mapItemId)
{
	ui.lineEditMapId->setText(mapItemId);
}

void CityTypeInfoDialog::SetOwnerName(const QString& ownerName)
{
	ui.lineEditOwnerType->setText(ownerName);
}
