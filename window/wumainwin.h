#ifndef WUMAINWIN_H
#define WUMAINWIN_H

#include <QMainWindow>
#include<model/wumian.h>
#include<QToolBar>
#include<QToolButton>
#include <QGLWidget>
#include<QToolButton>


namespace Ui {
    class wumainWin;
}

class wumainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit wumainWin(QWidget *parent = 0);
    ~wumainWin();

    QString fileT;
    int flag;
private:
    Ui::wumainWin *ui;

    wumian *test;
    //QToolButton *open;
   // QAction *ac_open;
    QToolButton *openObj;
    QToolButton *savePic;
   // QToolButton *changBack;


private slots:
    void openS();
    void savePicS();
    void changBackS();
};

#endif // WUMAINWIN_H
