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

void HexItemInfoDialog::SetMapHexItemId(const QString& id)
{
	ui.lineEditID->setText(id);
}

void HexItemInfoDialog::SetMapHexItemRow(const QString& row)
{
	ui.lineEditRow->setText(row);
}

void HexItemInfoDialog::SetMapHexItemCol(const QString& col)
{
	ui.lineEditCol->setText(col);
}

void HexItemInfoDialog::SetMapHexItemTerrainId(const QString& terrainTypeId)
{
	ui.lineEditType->setText(terrainTypeId);
}
