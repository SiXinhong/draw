/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Aug 13 16:21:24 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *actionZ;
    QAction *actionS;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QAction *action_11;
    QAction *action_12;
    QAction *action_13;
    QAction *action_14;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu4;
    QMenu *menuT;
    QMenu *menu;
    QMenu *menu_4;
    QMenu *menuCAD;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1054, 666);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        actionZ = new QAction(MainWindow);
        actionZ->setObjectName(QString::fromUtf8("actionZ"));
        actionS = new QAction(MainWindow);
        actionS->setObjectName(QString::fromUtf8("actionS"));
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QString::fromUtf8("action_10"));
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QString::fromUtf8("action_11"));
        action_12 = new QAction(MainWindow);
        action_12->setObjectName(QString::fromUtf8("action_12"));
        action_13 = new QAction(MainWindow);
        action_13->setObjectName(QString::fromUtf8("action_13"));
        action_14 = new QAction(MainWindow);
        action_14->setObjectName(QString::fromUtf8("action_14"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1054, 26));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu4 = new QMenu(menuBar);
        menu4->setObjectName(QString::fromUtf8("menu4"));
        menuT = new QMenu(menuBar);
        menuT->setObjectName(QString::fromUtf8("menuT"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menuCAD = new QMenu(menuBar);
        menuCAD->setObjectName(QString::fromUtf8("menuCAD"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(33, 33));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu4->menuAction());
        menuBar->addAction(menuT->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menuCAD->menuAction());
        menuBar->addAction(menu->menuAction());
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        action->setText(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_2->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\267\245\347\250\213", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\267\245\347\250\213", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\267\245\347\250\213", 0, QApplication::UnicodeUTF8));
        action_5->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266", 0, QApplication::UnicodeUTF8));
        actionZ->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264", 0, QApplication::UnicodeUTF8));
        actionS->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        action_8->setText(QApplication::translate("MainWindow", "\347\224\273\347\254\224", 0, QApplication::UnicodeUTF8));
        action_9->setText(QApplication::translate("MainWindow", "\346\251\241\347\232\256", 0, QApplication::UnicodeUTF8));
        action_10->setText(QApplication::translate("MainWindow", "\344\270\273\350\247\206\345\233\276", 0, QApplication::UnicodeUTF8));
        action_11->setText(QApplication::translate("MainWindow", "\344\270\211\347\273\264\347\253\213\344\275\223\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        action_12->setText(QApplication::translate("MainWindow", "\344\272\224\351\235\242\350\264\264\345\233\276\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        action_13->setText(QApplication::translate("MainWindow", "\344\275\277\347\224\250\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
        action_14->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        menu4->setTitle(QApplication::translate("MainWindow", "\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
        menuT->setTitle(QApplication::translate("MainWindow", "\350\247\206\345\233\276", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        menuCAD->setTitle(QApplication::translate("MainWindow", "CAD\346\216\245\345\217\243", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
