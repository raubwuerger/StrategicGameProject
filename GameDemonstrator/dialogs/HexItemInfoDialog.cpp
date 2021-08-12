#include "stdafx.h"
#include "HexItemInfoDialog.h"

HexItemInfoDialog::HexItemInfoDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

HexItemInfoDialog::~HexItemInfoDialog()
{

}

void HexItemInfoDialog::SetId(const QString& id)
{
	ui.lineEditID->setText(id);
}

void HexItemInfoDialog::SetRow(const QString& row)
{
	ui.lineEditRow->setText(row);
}

void HexItemInfoDialog::SetCol(const QString& col)
{
	ui.lineEditCol->setText(col);
}

void HexItemInfoDialog::SetTerrainName(const QString& terrainTypeName)
{
	ui.lineEditType->setText(terrainTypeName);
}
