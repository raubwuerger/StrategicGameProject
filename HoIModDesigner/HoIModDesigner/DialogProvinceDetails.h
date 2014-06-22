#ifndef DIALOGPROVINCEDETAILS_H
#define DIALOGPROVINCEDETAILS_H

#include <QDialog>
#include "ui_DialogProvinceDetail.h"
class ProvinceItem;

class DialogProvinceDetails : public QDialog
{
	Q_OBJECT

public:
/** */
	DialogProvinceDetails(QWidget *parent = 0);
/** */
	~DialogProvinceDetails();
/** Set m_ProvinceItem */
	void SetProvinceItem( ProvinceItem * val );
/** */
	void UpdateProvinceItem( ProvinceItem * val );
private:
	Ui::DialogProvinceDetail ui;
};

#endif // DIALOGPROVINCEDETAILS_H
