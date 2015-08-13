#include "stdafx.h"
#include "gamedemonstrator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameDemonstrator w;
	w.show();
	return a.exec();
}
