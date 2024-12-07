/********************************************************************************
** Form generated from reading UI file 'occQt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCCQT_H
#define UI_OCCQT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_occQtClass
{
public:
    QAction *actionExit;
    QAction *actionZoom;
    QAction *actionPan;
    QAction *actionRotate;
    QAction *actionReset;
    QAction *actionFitAll;
    QAction *actionAbout;
    QAction *actionBox;
    QAction *actionCone;
    QAction *actionNew;
    QAction *actionDeleteAll;
    QAction *actionPoints;
    QAction *actionLines;
    QAction *actionCircle;
    QAction *actionSplines;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuPrimitive;
    QMenu *menuModeling;
    QMenu *menuHelp;
    QMenu *menu2D;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *occQtClass)
    {
        if (occQtClass->objectName().isEmpty())
            occQtClass->setObjectName(QString::fromUtf8("occQtClass"));
        occQtClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/lamp.png"), QSize(), QIcon::Normal, QIcon::Off);
        occQtClass->setWindowIcon(icon);
        actionExit = new QAction(occQtClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionZoom = new QAction(occQtClass);
        actionZoom->setObjectName(QString::fromUtf8("actionZoom"));
        actionZoom->setCheckable(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/Zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon1);
        actionPan = new QAction(occQtClass);
        actionPan->setObjectName(QString::fromUtf8("actionPan"));
        actionPan->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/Pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPan->setIcon(icon2);
        actionRotate = new QAction(occQtClass);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        actionRotate->setCheckable(false);
        actionRotate->setChecked(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resources/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon3);
        actionReset = new QAction(occQtClass);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Resources/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset->setIcon(icon4);
        actionFitAll = new QAction(occQtClass);
        actionFitAll->setObjectName(QString::fromUtf8("actionFitAll"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Resources/FitAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFitAll->setIcon(icon5);
        actionAbout = new QAction(occQtClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setIcon(icon);
        actionBox = new QAction(occQtClass);
        actionBox->setObjectName(QString::fromUtf8("actionBox"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Resources/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBox->setIcon(icon6);
        actionCone = new QAction(occQtClass);
        actionCone->setObjectName(QString::fromUtf8("actionCone"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Resources/cone.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCone->setIcon(icon7);
        actionNew = new QAction(occQtClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Resources/fillet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon8);
        actionDeleteAll = new QAction(occQtClass);
        actionDeleteAll->setObjectName(QString::fromUtf8("actionDeleteAll"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Resources/delete.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteAll->setIcon(icon9);
        actionPoints = new QAction(occQtClass);
        actionPoints->setObjectName(QString::fromUtf8("actionPoints"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Resources/points.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPoints->setIcon(icon10);
        actionLines = new QAction(occQtClass);
        actionLines->setObjectName(QString::fromUtf8("actionLines"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Resources/lines.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLines->setIcon(icon11);
        actionCircle = new QAction(occQtClass);
        actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
        actionSplines = new QAction(occQtClass);
        actionSplines->setObjectName(QString::fromUtf8("actionSplines"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Resources/spline.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSplines->setIcon(icon12);
        centralWidget = new QWidget(occQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        occQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(occQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 33));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuPrimitive = new QMenu(menuBar);
        menuPrimitive->setObjectName(QString::fromUtf8("menuPrimitive"));
        menuModeling = new QMenu(menuBar);
        menuModeling->setObjectName(QString::fromUtf8("menuModeling"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menu2D = new QMenu(menuBar);
        menu2D->setObjectName(QString::fromUtf8("menu2D"));
        occQtClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(occQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        occQtClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuPrimitive->menuAction());
        menuBar->addAction(menu2D->menuAction());
        menuBar->addAction(menuModeling->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuView->addAction(actionZoom);
        menuView->addAction(actionPan);
        menuView->addAction(actionRotate);
        menuView->addSeparator();
        menuView->addAction(actionReset);
        menuView->addAction(actionFitAll);
        menuView->addAction(actionDeleteAll);
        menuPrimitive->addAction(actionBox);
        menuPrimitive->addAction(actionCone);
        menuModeling->addAction(actionNew);
        menuModeling->addSeparator();
        menuModeling->addSeparator();
        menuHelp->addAction(actionAbout);
        menu2D->addAction(actionPoints);
        menu2D->addAction(actionLines);
        menu2D->addAction(actionSplines);

        retranslateUi(occQtClass);

        QMetaObject::connectSlotsByName(occQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *occQtClass)
    {
        occQtClass->setWindowTitle(QCoreApplication::translate("occQtClass", "SimpleGM", nullptr));
        actionExit->setText(QCoreApplication::translate("occQtClass", "&Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("occQtClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionZoom->setText(QCoreApplication::translate("occQtClass", "&Zoom", nullptr));
        actionPan->setText(QCoreApplication::translate("occQtClass", "&Pan", nullptr));
        actionRotate->setText(QCoreApplication::translate("occQtClass", "&Rotate", nullptr));
        actionReset->setText(QCoreApplication::translate("occQtClass", "&BaseView", nullptr));
        actionFitAll->setText(QCoreApplication::translate("occQtClass", "&FitAll", nullptr));
        actionAbout->setText(QCoreApplication::translate("occQtClass", "&About", nullptr));
        actionBox->setText(QCoreApplication::translate("occQtClass", "&Box", nullptr));
        actionCone->setText(QCoreApplication::translate("occQtClass", "&Cone", nullptr));
        actionNew->setText(QCoreApplication::translate("occQtClass", "&NewElement", nullptr));
        actionDeleteAll->setText(QCoreApplication::translate("occQtClass", "&DeleteAll", nullptr));
        actionPoints->setText(QCoreApplication::translate("occQtClass", "&Points", nullptr));
        actionLines->setText(QCoreApplication::translate("occQtClass", "&Lines", nullptr));
        actionCircle->setText(QCoreApplication::translate("occQtClass", "&Circle", nullptr));
        actionSplines->setText(QCoreApplication::translate("occQtClass", "Splines", nullptr));
        menuFile->setTitle(QCoreApplication::translate("occQtClass", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("occQtClass", "&View", nullptr));
        menuPrimitive->setTitle(QCoreApplication::translate("occQtClass", "Primi&tive", nullptr));
        menuModeling->setTitle(QCoreApplication::translate("occQtClass", "3D", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("occQtClass", "&Help", nullptr));
        menu2D->setTitle(QCoreApplication::translate("occQtClass", "2D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class occQtClass: public Ui_occQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCQT_H
