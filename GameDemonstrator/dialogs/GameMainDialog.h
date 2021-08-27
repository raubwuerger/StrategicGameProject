/********************************************************************************
** Form generated from reading UI file 'GameMainDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GAMEMAINDIALOG_H
#define GAMEMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

class GameDemonstrator;

QT_BEGIN_NAMESPACE

class Ui_GameMainDialog
{
public:
	/** */
	void setupUi(QDialog *GameMainDialog); // setupUi
	/** */
	void retranslateUi(QDialog *GameMainDialog); // retranslateUi
public:
    QPushButton *StartSingleplayer;
    QPushButton *StartEditor;
    QPushButton *CloseGame;
};

namespace Ui
{
    class GameMainDialog: public Ui_GameMainDialog
	{
	public:
		/** */
		GameMainDialog(QDialog* dialog);
		/** */
		void Init(GameDemonstrator* gameDemonstrator);
	private:
		QDialog* Dialog;
		GameDemonstrator* GameDemonstratorObject;
	};
}

QT_END_NAMESPACE

#endif // GAMEMAINDIALOG_H
