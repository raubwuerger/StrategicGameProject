#include "stdafx.h"
#include "ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.pushButtonChooseHoI3Path, SIGNAL(clicked()), this, SLOT(ChooseHoI3Path()) );

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget( ui.labelHoI3Path, 0, 0);
	mainLayout->addWidget( ui.labelMods, 1, 0);
	mainLayout->addWidget( ui.lineEditHoI3Path, 0, 1, 1, 3);
	mainLayout->addWidget( ui.listWidget, 1, 1, 8, 4 );

	ui.pushButtonChooseHoI3Path->setMaximumWidth(ui.pushButtonChooseHoI3Path->width());
	mainLayout->addWidget( ui.pushButtonChooseHoI3Path, 0, 4 );
	ui.pushButtonAddMod->setMaximumWidth(ui.pushButtonAddMod->width());
	mainLayout->addWidget( ui.pushButtonAddMod, 1, 5 );
	mainLayout->addWidget( ui.pushButtonModifyMod, 2, 5 );
	mainLayout->addWidget( ui.pushButtonDeleteMod, 3, 5 );
	mainLayout->addWidget( ui.pushButtonClose, 8, 5 );

	setLayout(mainLayout);
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
