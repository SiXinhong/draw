#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include<window/mainwindow.h>
#include<window/mythread.h>
class MainWindow;
class myThread;
class controlThread
{
public:
    controlThread();
    void start();
    void getMainWindow(MainWindow *temp);
private:
    MainWindow *mWindow;
    myThread *mThread;
private slots:
    void threadFinished();
};

#endif // CONTROLTHREAD_H
