#ifndef MYTHREAD_H
#define MYTHREAD_H
/***************MyThread.h******************/

#include <QtCore/QThread>
#include<window/mainwindow.h>
class MainWindow;
class myThread: public QThread
{
    Q_OBJECT
public:
    myThread(MainWindow *m);
    ~myThread();
protected:
    MainWindow *mWindow;
    void run();
private:
    QMutex qm;
};

#endif // MYTHREAD_H
