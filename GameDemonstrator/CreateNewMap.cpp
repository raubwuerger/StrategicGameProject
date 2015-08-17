#include "stdafx.h"
#include "CreateNewMap.h"
#include "CreateNewMapDialog.h"

CreateNewMap::CreateNewMap(QObject *parent)
	: QObject(parent)
{

}

CreateNewMap::~CreateNewMap()
{

}

void CreateNewMap::DoCreateNewMap()
{
	CreateNewMapDialog dialog(nullptr);
	if( dialog.exec() == QDialog::Rejected )
	{
		return;
	}
}
