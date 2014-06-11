#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include "ui_ConfigurationDialog.h"

class ConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigurationDialog(QWidget *parent = 0);
	~ConfigurationDialog();
private slots:
	void ChooseHoI3Path();

private:
	Ui::ConfigurationDialog ui;
};

#endif // CONFIGURATIONDIALOG_H
