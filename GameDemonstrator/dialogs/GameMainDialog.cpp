#include "stdafx.h"
#include "GameMainDialog.h"
#include "GameDemonstrator.h"

void Ui_GameMainDialog::setupUi(QDialog *GameMainDialog)
{
	if (GameMainDialog->objectName().isEmpty())
		GameMainDialog->setObjectName(QStringLiteral("GameMainDialog"));
	GameMainDialog->resize(560, 418);
	StartSingleplayer = new QPushButton(GameMainDialog);
	StartSingleplayer->setObjectName(QStringLiteral("StartSingleplayer"));
	StartSingleplayer->setGeometry(QRect(110, 110, 281, 34));
	StartEditor = new QPushButton(GameMainDialog);
	StartEditor->setObjectName(QStringLiteral("StartEditor"));
	StartEditor->setGeometry(QRect(110, 160, 281, 34));
	CloseGame = new QPushButton(GameMainDialog);
	CloseGame->setObjectName(QStringLiteral("CloseGame"));
	CloseGame->setGeometry(QRect(110, 210, 281, 34));

	retranslateUi(GameMainDialog);

	QMetaObject::connectSlotsByName(GameMainDialog);
}

void Ui_GameMainDialog::retranslateUi(QDialog *GameMainDialog)
{
	GameMainDialog->setWindowTitle(QApplication::translate("GameMainDialog", "GameMainDialog", 0));
	StartSingleplayer->setText(QApplication::translate("GameMainDialog", "Start Singleplayer Game", 0));
	StartEditor->setText(QApplication::translate("GameMainDialog", "Start Editor", 0));
	CloseGame->setText(QApplication::translate("GameMainDialog", "Close Game", 0));
}

Ui::GameMainDialog::GameMainDialog(QDialog* dialog)
{
	setupUi(dialog);
	retranslateUi(dialog);
	QObject::connect(CloseGame, &QPushButton::clicked, dialog, &QDialog::accept);
}

void Ui::GameMainDialog::Init(GameDemonstrator* gameDemonstrator)
{
	GameDemonstratorObject = gameDemonstrator;
	QObject::connect(CloseGame, &QPushButton::clicked, GameDemonstratorObject, &GameDemonstrator::close);
}
