/********************************************************************************
** Form generated from reading UI file 'wumainwin.ui'
**
** Created: Sun Aug 13 16:21:24 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WUMAINWIN_H
#define UI_WUMAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wumainWin
{
public:
    QAction *action;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *wumainWin)
    {
        if (wumainWin->objectName().isEmpty())
            wumainWin->setObjectName(QString::fromUtf8("wumainWin"));
        wumainWin->resize(800, 600);
        action = new QAction(wumainWin);
        action->setObjectName(QString::fromUtf8("action"));
        centralwidget = new QWidget(wumainWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        wumainWin->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(wumainWin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        wumainWin->setStatusBar(statusbar);
        toolBar = new QToolBar(wumainWin);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        wumainWin->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(wumainWin);

        QMetaObject::connectSlotsByName(wumainWin);
    } // setupUi

    void retranslateUi(QMainWindow *wumainWin)
    {
        wumainWin->setWindowTitle(QApplication::translate("wumainWin", "MainWindow", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("wumainWin", "\346\211\223\345\274\200\346\250\241\345\236\213", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("wumainWin", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wumainWin: public Ui_wumainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WUMAINWIN_H
