#include "stdafx.h"
#include "MapCreatorHeightMapDialog.h"
#include "helper\StringToNumberConverter.h"
#include "LogInterface.h"

MapCreatorHeightMapDialog::MapCreatorHeightMapDialog(QWidget *parent /*= 0*/)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonCreate, &QPushButton::clicked, this, &MapCreatorHeightMapDialog::UpdateAndSendCreationData);
	InitCreationData();
}

void MapCreatorHeightMapDialog::UpdateAndSendCreationData()
{
	GameMapCreatorHeightMapData	creationData;
	bool conversionOk = true;
	conversionOk &= StringToNumberConverter::Convert(ui.lineEdiMapSizeX->text(), creationData.MapSizeX);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEdiMapSizeY->text(), creationData.MapSizeY);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditXBoundLower->text(), creationData.LowerXBound);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditXBoundUpper->text(), creationData.UpperXBound);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditZBoundLower->text(), creationData.LowerZBound);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditZBoundUpper->text(), creationData.UpperZBound);

	conversionOk &= StringToNumberConverter::Convert(ui.lineEditOctaveCount->text(), creationData.OctaveCount);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditFrequency->text(), creationData.Frequency);
	conversionOk &= StringToNumberConverter::Convert(ui.lineEditPersistence->text(), creationData.Persistence);

	if (false == conversionOk)
	{
		Q_ASSERT(conversionOk);
		jha::GetLog()->Log_DEBUG(tr("Getting HeightMap values from dialog failed!"));
		return;
	}

	emit SignalGameMapCreationData(creationData);

}

void MapCreatorHeightMapDialog::InitCreationData()
{
	ui.lineEdiMapSizeX->setText("120");
	ui.lineEdiMapSizeY->setText("60");
	ui.lineEditXBoundLower->setText("6.0");
	ui.lineEditXBoundUpper->setText("10.0");
	ui.lineEditZBoundLower->setText("1.0");
	ui.lineEditZBoundUpper->setText("5.0");
	ui.lineEditOctaveCount->setText("6");
	ui.lineEditFrequency->setText("2.0");
	ui.lineEditPersistence->setText("0.5");
}
