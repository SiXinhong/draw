/**************MyThread.cpp*****************/

#include "mythread.h"
#include <iostream>

myThread::myThread(MainWindow *m) : QThread()
{
    this->mWindow=m;
}

void myThread::run(){
    //mWindow->startThread();
    //qm.lock();
    mWindow->centralDraw->setCanNDraw();
    mWindow->centralDraw->getCanvasPointNew();
    qDebug("½áÊøÁË");
    //qm.unlock();
    mWindow->getDifferentColor();
    mWindow->centralDraw->setCanDraw();
    //mWindow->terminateThread();
    //mWindow->terminateThread();
}

myThread::~myThread()
{
}
