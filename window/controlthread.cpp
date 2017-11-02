#include "controlthread.h"
#include<QPushButton>

controlThread::controlThread()
{
}


void controlThread::start(){
    mThread=new myThread(mWindow);
    //QObject::connect(mThread,SIGNAL(finished()),this,SLOT(threadFinished()));
    mThread->start();
    //mThread->isFinished();
    //mWindow->centralDraw->getCanvasPointNew();
    qDebug("½áÊøÁË");
    //mWindow->getDifferentColor();
    //mWindow->terminateThread();
}

void controlThread::getMainWindow(MainWindow *temp){
    mWindow=temp;
}

void controlThread::threadFinished(){
    //mWindow->terminateThread();
}
