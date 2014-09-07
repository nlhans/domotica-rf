/********************************************************************************
** Form generated from reading UI file 'domoticasimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOMOTICASIMULATOR_H
#define UI_DOMOTICASIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DomoticaSimulator
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DomoticaSimulator)
    {
        if (DomoticaSimulator->objectName().isEmpty())
            DomoticaSimulator->setObjectName(QStringLiteral("DomoticaSimulator"));
        DomoticaSimulator->resize(501, 371);
        centralWidget = new QWidget(DomoticaSimulator);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DomoticaSimulator->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DomoticaSimulator);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 501, 20));
        DomoticaSimulator->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DomoticaSimulator);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DomoticaSimulator->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DomoticaSimulator);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DomoticaSimulator->setStatusBar(statusBar);

        retranslateUi(DomoticaSimulator);

        QMetaObject::connectSlotsByName(DomoticaSimulator);
    } // setupUi

    void retranslateUi(QMainWindow *DomoticaSimulator)
    {
        DomoticaSimulator->setWindowTitle(QApplication::translate("DomoticaSimulator", "DomoticaSimulator", 0));
    } // retranslateUi

};

namespace Ui {
    class DomoticaSimulator: public Ui_DomoticaSimulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOMOTICASIMULATOR_H
