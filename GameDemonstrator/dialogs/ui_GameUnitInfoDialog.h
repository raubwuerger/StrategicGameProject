/********************************************************************************
** Form generated from reading UI file 'GameUnitInfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEUNITINFODIALOG_H
#define UI_GAMEUNITINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameUnitInfoDialog
{
public:
    QLineEdit *lineEditId;
    QLineEdit *lineEditName;
    QLineEdit *lineEditType;
    QLabel *labelType;
    QLabel *labelName;
    QLabel *labelId;
    QLabel *labelMovement;
    QLineEdit *lineEditTypeMovement;
    QLabel *labelStrength;
    QLineEdit *lineEditStrength;

    void setupUi(QWidget *GameUnitInfoDialog)
    {
        if (GameUnitInfoDialog->objectName().isEmpty())
            GameUnitInfoDialog->setObjectName(QStringLiteral("GameUnitInfoDialog"));
        GameUnitInfoDialog->resize(260, 210);
        GameUnitInfoDialog->setMinimumSize(QSize(260, 210));
        lineEditId = new QLineEdit(GameUnitInfoDialog);
        lineEditId->setObjectName(QStringLiteral("lineEditId"));
        lineEditId->setGeometry(QRect(130, 10, 113, 28));
        lineEditName = new QLineEdit(GameUnitInfoDialog);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));
        lineEditName->setGeometry(QRect(130, 50, 113, 28));
        lineEditType = new QLineEdit(GameUnitInfoDialog);
        lineEditType->setObjectName(QStringLiteral("lineEditType"));
        lineEditType->setGeometry(QRect(130, 90, 113, 28));
        labelType = new QLabel(GameUnitInfoDialog);
        labelType->setObjectName(QStringLiteral("labelType"));
        labelType->setGeometry(QRect(20, 90, 90, 20));
        labelType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelName = new QLabel(GameUnitInfoDialog);
        labelName->setObjectName(QStringLiteral("labelName"));
        labelName->setGeometry(QRect(20, 50, 90, 20));
        labelName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelId = new QLabel(GameUnitInfoDialog);
        labelId->setObjectName(QStringLiteral("labelId"));
        labelId->setGeometry(QRect(20, 10, 90, 20));
        labelId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMovement = new QLabel(GameUnitInfoDialog);
        labelMovement->setObjectName(QStringLiteral("labelMovement"));
        labelMovement->setGeometry(QRect(20, 130, 90, 20));
        labelMovement->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditTypeMovement = new QLineEdit(GameUnitInfoDialog);
        lineEditTypeMovement->setObjectName(QStringLiteral("lineEditTypeMovement"));
        lineEditTypeMovement->setGeometry(QRect(130, 130, 113, 28));
        labelStrength = new QLabel(GameUnitInfoDialog);
        labelStrength->setObjectName(QStringLiteral("labelStrength"));
        labelStrength->setGeometry(QRect(20, 170, 90, 20));
        labelStrength->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditStrength = new QLineEdit(GameUnitInfoDialog);
        lineEditStrength->setObjectName(QStringLiteral("lineEditStrength"));
        lineEditStrength->setGeometry(QRect(130, 170, 113, 28));

        retranslateUi(GameUnitInfoDialog);

        QMetaObject::connectSlotsByName(GameUnitInfoDialog);
    } // setupUi

    void retranslateUi(QWidget *GameUnitInfoDialog)
    {
        GameUnitInfoDialog->setWindowTitle(QApplication::translate("GameUnitInfoDialog", "GameUnitInfoDialog", 0));
        labelType->setText(QApplication::translate("GameUnitInfoDialog", "Type:", 0));
        labelName->setText(QApplication::translate("GameUnitInfoDialog", "Name:", 0));
        labelId->setText(QApplication::translate("GameUnitInfoDialog", "ID:", 0));
        labelMovement->setText(QApplication::translate("GameUnitInfoDialog", "Movement:", 0));
        labelStrength->setText(QApplication::translate("GameUnitInfoDialog", "Strength:", 0));
    } // retranslateUi

};

namespace Ui {
    class GameUnitInfoDialog: public Ui_GameUnitInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEUNITINFODIALOG_H
