#include "stdafx.h"
#include "DialogProvinceDetails.h"
#include "ProvinceItem.h"

DialogProvinceDetails::DialogProvinceDetails(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

DialogProvinceDetails::~DialogProvinceDetails()
{

}

void DialogProvinceDetails::SetProvinceItem( ProvinceItem * val )
{
	if( val == nullptr )
	{
		return;
	}
	
	ui.lineEdit->setText( val->m_Name );

	ui.listWidget->setSortingEnabled(true);
	ui.listWidget->setRowCount( val->GetItemMap().size() );
	ui.listWidget->setColumnCount( 2 );

	QHeaderView *verticalHeader = ui.listWidget->verticalHeader();
	verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader->setDefaultSectionSize(20);

	int columnIndex = 0;
	ui.listWidget->verticalHeader()->setVisible(false);
	ui.listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	QTableWidgetItem *id = new QTableWidgetItem("Name");
	id->setBackground(Qt::lightGray);
	ui.listWidget->setHorizontalHeaderItem( columnIndex++, id );

	QTableWidgetItem *provinces = new QTableWidgetItem("Wert");
	provinces->setBackground(Qt::lightGray);
	ui.listWidget->setHorizontalHeaderItem( columnIndex++, provinces );

	int rowIndex = 0;
	QMap<QString,ItemData>::ConstIterator iter;
	for( iter = val->GetItemMap().constBegin(); iter != val->GetItemMap().constEnd(); iter++ )
	{
		int columnIndex = 0;
		ui.listWidget->setItem(rowIndex, columnIndex++, new QTableWidgetItem(iter->GetName()) );
		ui.listWidget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);

		ui.listWidget->setItem(rowIndex, columnIndex++, new QTableWidgetItem( iter->GetData().type() == QVariant::StringList ? iter->GetData().toStringList().join(",") : iter->GetData().toString() ) );

		rowIndex++;
	}
}

void DialogProvinceDetails::UpdateProvinceItem( ProvinceItem * val )
{
	if( val == nullptr )
	{
		return;
	}
	int rowCount = ui.listWidget->rowCount();
	for( int i=0; i < rowCount; i++ )
	{
		QString valueName = ui.listWidget->item(i,0)->text();
		ItemData toUpdate = val->FindItem(valueName);
		if( toUpdate.IsNull() == true )
		{
			continue;
		}
		if( toUpdate.GetData().type() == QVariant::StringList )
		{
			QStringList list = ui.listWidget->item(i,1)->text().split(",",QString::SkipEmptyParts);
			val->SetItem(valueName,list);
		}
		else
		{
			QString value = ui.listWidget->item(i,1)->text();
			val->SetItem(valueName,value);
		}
	}
}
