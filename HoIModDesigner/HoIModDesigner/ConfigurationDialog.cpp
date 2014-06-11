#include "stdafx.h"
#include "ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.pushButtonChooseHoI3Path, SIGNAL(clicked()), this, SLOT(ChooseHoI3Path()) );
}

ConfigurationDialog::~ConfigurationDialog()
{

}

void ConfigurationDialog::ChooseHoI3Path()
{
	QFileDialog::Options options;
	options |= QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this, tr("Choos HoI3 base path"),	ui.lineEditHoI3Path->text(),options);

	if( directory.isEmpty() == false )
	{
		ui.lineEditHoI3Path->setText(directory);
	}
}
