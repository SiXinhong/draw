/********************************************************************************
** Form generated from reading UI file 'childwindow.ui'
**
** Created: Sun Aug 13 16:21:24 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHILDWINDOW_H
#define UI_CHILDWINDOW_H

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

class Ui_childWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *childWindow)
    {
        if (childWindow->objectName().isEmpty())
            childWindow->setObjectName(QString::fromUtf8("childWindow"));
        childWindow->resize(1565, 1115);
        action = new QAction(childWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(childWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(childWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(childWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        childWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(childWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        childWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(childWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        childWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(childWindow);

        QMetaObject::connectSlotsByName(childWindow);
    } // setupUi

    void retranslateUi(QMainWindow *childWindow)
    {
        childWindow->setWindowTitle(QApplication::translate("childWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("childWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("childWindow", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("childWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("childWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class childWindow: public Ui_childWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHILDWINDOW_H
