#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H
#include <QtGui/QApplication>
#include "window/MainWindow.h"
#include <QGLWidget>
#include"drawWidget/drawwidget.h"
#include"drawWidget/digitalwidget.h"
//#include<QScrollArea>
#include"myScrollDialog/myqscrollarea.h"
#include <QTextCodec>
#include<window/controlthread.h>
#endif // DRAWWIDGET_H

int main(int argc, char *argv[])
{
    QApplication c(argc, argv);
    MainWindow *w=new MainWindow;
    controlThread *control=new controlThread;
    w->getControlThread(control);
    control->getMainWindow(w);

    //digitalwidget *centralDraw = new digitalwidget(w);
    DrawWidget *centralDraw=new DrawWidget(w);

    myQScrollArea *pArea= new myQScrollArea;

    pArea->setWidget(centralDraw);
    w->setCentralWidget(pArea);
    pArea->getDrawWidget(centralDraw);

    w->getCentral(centralDraw);
    w->showMaximized();
    centralDraw->getMainArea(w,pArea);
    c.setWindowIcon(QIcon("icon/myapp.ico"));


    //Set Encode GBK
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    w->setWindowTitle(QWidget::tr("迷彩自动生成系统"));

    return c.exec();
}
