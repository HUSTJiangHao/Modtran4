/********************************************************************************
** Form generated from reading UI file 'mtrWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MTRWIDGET_H
#define UI_MTRWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mtrWidgetClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_openTp5;
    QPushButton *btn_startMod;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_openTp7;
    QPushButton *btn_cRadiance;
    QPushButton *btn_cTransmittance;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btn_clr;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *modtranStateText;

    void setupUi(QMainWindow *mtrWidgetClass)
    {
        if (mtrWidgetClass->objectName().isEmpty())
            mtrWidgetClass->setObjectName(QStringLiteral("mtrWidgetClass"));
        mtrWidgetClass->resize(650, 367);
        centralWidget = new QWidget(mtrWidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        btn_openTp5 = new QPushButton(centralWidget);
        btn_openTp5->setObjectName(QStringLiteral("btn_openTp5"));

        verticalLayout_2->addWidget(btn_openTp5);

        btn_startMod = new QPushButton(centralWidget);
        btn_startMod->setObjectName(QStringLiteral("btn_startMod"));

        verticalLayout_2->addWidget(btn_startMod);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btn_openTp7 = new QPushButton(centralWidget);
        btn_openTp7->setObjectName(QStringLiteral("btn_openTp7"));

        verticalLayout_2->addWidget(btn_openTp7);

        btn_cRadiance = new QPushButton(centralWidget);
        btn_cRadiance->setObjectName(QStringLiteral("btn_cRadiance"));

        verticalLayout_2->addWidget(btn_cRadiance);

        btn_cTransmittance = new QPushButton(centralWidget);
        btn_cTransmittance->setObjectName(QStringLiteral("btn_cTransmittance"));

        verticalLayout_2->addWidget(btn_cTransmittance);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        btn_clr = new QPushButton(centralWidget);
        btn_clr->setObjectName(QStringLiteral("btn_clr"));

        verticalLayout_2->addWidget(btn_clr);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        modtranStateText = new QPlainTextEdit(centralWidget);
        modtranStateText->setObjectName(QStringLiteral("modtranStateText"));

        verticalLayout->addWidget(modtranStateText);


        horizontalLayout->addLayout(verticalLayout);

        mtrWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(mtrWidgetClass);

        //QMetaObject::connectSlotsByName(mtrWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *mtrWidgetClass)
    {
        mtrWidgetClass->setWindowTitle(QApplication::translate("mtrWidgetClass", "mtrWidget", nullptr));
        btn_openTp5->setText(QApplication::translate("mtrWidgetClass", "\346\211\223\345\274\200tp5\346\226\207\344\273\266", nullptr));
        btn_startMod->setText(QApplication::translate("mtrWidgetClass", "modtran\350\256\241\347\256\227", nullptr));
        btn_openTp7->setText(QApplication::translate("mtrWidgetClass", "\346\211\223\345\274\200tp7\346\226\207\344\273\266", nullptr));
        btn_cRadiance->setText(QApplication::translate("mtrWidgetClass", "\350\276\220\344\272\256\345\272\246\350\247\243\346\236\220", nullptr));
        btn_cTransmittance->setText(QApplication::translate("mtrWidgetClass", "\351\200\217\350\277\207\347\216\207\350\256\241\347\256\227", nullptr));
        btn_clr->setText(QApplication::translate("mtrWidgetClass", "\346\270\205\351\231\244\346\226\207\346\234\254", nullptr));
        label->setText(QApplication::translate("mtrWidgetClass", "modtran\350\276\223\345\207\272:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mtrWidgetClass: public Ui_mtrWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MTRWIDGET_H
