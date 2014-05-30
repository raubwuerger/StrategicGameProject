#include "stdafx.h"
#include "hoimoddesigner.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HoIModDesigner w;
	w.show();
	return a.exec();
}
