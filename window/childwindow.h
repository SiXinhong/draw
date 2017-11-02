#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QMainWindow>
#include <QGLWidget>
#include<QMouseEvent>
#include <QMainWindow>
#include"childwindow.h"
#include<QPainter>
#include <QTextCodec>
//#include"getpoint.h"
#include<QMouseEvent>
#include<list>
#include<QToolButton>
#include <QSplitter>

#include <QtGui/QDoubleSpinBox>
#include<QtCore/QMap>
#include <QtGui/QIcon>
#include<QComboBox>
#include<QToolButton>
#include <QSplitter>
#include <model/first_opengl.h>
#include<model/fiveview.h>
#include<QFileDialog>



namespace Ui {
    class childWindow;
}

class childWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit childWindow(QWidget *parent = 0);
    ~childWindow();

    int fiveViewFlag;

private:
    Ui::childWindow *ui;


    //添加右侧DockWidget
//    QDockWidget *rightDock;
//    QSplitter *splitterMain;
//    QSplitter *splitterRight;
//    QListWidget *tempListWidget;

    QToolButton *showFiveView;
    QToolButton *openObj;
    QToolButton *saveObj;


    QToolButton *xy;
    QToolButton *yz;
    QToolButton *xz;
    QToolButton *line;
    QToolButton *cube;
    QToolButton *sphere;
    QToolButton *fiveImage;
    QToolButton *changeback;
    QToolButton *planeFlag;
    QToolButton *boxFlag;
    //生成model类

    first_opengl *c;
    fiveView *ff;

    char* modelFILE;

protected:
   // void addRightQDockWidget();
    void addMyToolBar();
//    void closeEvent(QCloseEvent *event);
    GLMmodel *model;
private slots:

//    void closeEvent(QCloseEvent *event);
    void showFiveViewS();
    void xyMap();
    void yzMap();
    void xzMap();
    void linerMap();
    void cubeMap();
    void sphereMap();
    void fiveImageS();

    void openobjS();
    void changebackS();
    void planeFlagS();
    void boxFlagS();
signals:
    void ChildWindowEvent();
};

#endif // CHILDWINDOW_H
