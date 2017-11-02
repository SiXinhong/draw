#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H
#include <QWidget>
#include<QDebug>
#include<QMoveEvent>
#include<QtGui>
#include<QPaintEvent>
#include<QColor>
#include<QPixmap>
#include<QPoint>
#include<QPainter>
#include<QPalette>
#include <QTextCodec>
#include"caculate/getpoint.h"
#include<list>
#include<QToolButton>
#include <QSplitter>
#include<QListWidget>
#include<QTreeWidget>
#include <QtCore/QMap>
#include <QtGui/QDoubleSpinBox>
#include "qtPropertyBrowser/qtpropertybrowser.h"
#include "qtPropertyBrowser/qteditorfactory.h"
#include "qtPropertyBrowser/qttreepropertybrowser.h"
#include<QMap>
#include <QtGui/QIcon>
#include<QComboBox>
#include<QMessageBox>
#include<QWheelEvent>
#include"window/mainwindow.h"
#include"myScrollDialog/myqscrollarea.h"
#include<cmath>
#include<window/spotColorAll.h>
#include<caculate/savespot.h>
#include<QKeyEvent>
#include"window/wumainwin.h"
#include"model/wumian.h"
#include<stdlib.h>
#include<time.h>
#include"drawWidget/spot.h"
#include<QAction>
#define rectSize  10 //9  原来的值
class MainWindow;
class childWindow;
class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    //spotColorAll allColor;
    explicit DrawWidget(QWidget *parent = 0);
    int showDigital;

    //颜色信息
    QColor iconColor[maxSize];
    void addAreaSpot();
    void addCtrlSpot();
    void addImagePath();
    void addSpotOrigin(int drawOk);
    void addSpotPoint();
    void addSpecialPath();//spotMove用
    void addHandlePath();
    void areaSelected();
//重做撤销用
    void backWardF();
    void forWardF();
    void saveStation();
    void readStation();

    int collisonDetection(int num,float saveP[300][2]);
    void caculateOneCurve2(int uflag);
    void caculateOneCurve();
    //----------xiaotian    绘制数码迷彩路径  使用矩阵的方式
    void caculateOneCurveByDigital(int edge[10][10],int oriX,int oriY,int edgeW,int rowS,int colS);
    void caculateCanvasPath();
    void caculateAreaRatio();
    void changeSpotOrign();
    void clear();
    void clearOne();
    //void contextMenuEvent(QContextMenuEvent *);

    void deleteSpot();
    void drawOPoint(QPainter &p);
    void drawHandlePoint(QPainter &p);
    void drawProcessLine(QPainter &p);
    void drawBackground(QPainter &p);
    void drawCanvas(QPainter &p);
    void drawCLine(QPainter &p);
    void drawBlank(QPainter &p);
    void drawEdgeLine(QPainter &p);
    void drawCanvasX(QPainter &p);
    void drawMark(QPainter &p);
    void drawOrign(QPainter &p);
    void drawScaleLine(QPainter &p);

    void drawSpot(QPainter &p);
    //---------- xiaotian
    //--------------------xiaotian     画数码迷彩斑点,使用矩阵的画法
    void drawDigitalSpot(QPainter &p);
    void drawNbSpot(QPainter &p);

    void drawDigital(QPainter &p);

    //void getOriginPosition();
    void getPointStyle(int *,int&,int*,int&,int&);
    float getWindowScale();
    void getSpotColor(int count);
    void getAutoCAD();
    void getFiveImage();
//    void getThePoint(int (*num)[100],int hasNum,int area);
    void getThePoint(int (*num)[1000],int hasNum,int area);
    void getThePointAll(int (*num)[1000],int hasNum,int area);
    void getMainArea(MainWindow *mainTemp,QScrollArea *showArea);
    //获取子窗口ctrlFlag状态与spotSelectedCtrl
    void getCtrl(int &,list<int>&);

    int handleSelected();

    void judgeIntersection(int num[5][1000],int count,int *hasNum,int ox,int oy,int wid,int hei);

    void mapping();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressNotDrawOk();
    void mousePressDrawOk();

    int oPointMove(QMouseEvent *event);
    int oPointSelected();

    void paintEvent(QPaintEvent *);

    void resizeEvent(QResizeEvent *event);
    int return_flag();
    void saveCanvasF(QString fileName);
    void readCanvasF(QString fileName);
    //void autoColor();
    void setCanvasXY(int x,int y,int tempFlag);
    //-----------xiaotian  设置斑点颜色
    void setAutoSingleColor(spotColorAll tempAllColor,int tempIndex,int count);

    void setAutoColor(spotColorAll,int);
    void setCanvasXYZ(int x,int y,int z,int tempFlag);
    void setCenter(float x,float y);
    void setColor(QColor temp,int tempIndex,spotChangeSpot *exchangeS);
    void setBackGroundColor(QColor tempColor,int index);
    void setBackGroundSize(int x,int y,int z);
    void setCanDraw();
    void setCanNDraw();
    void setRadiusFlag(int tempFlag);
    void setDrawFlag(int flag);
    void setOPointFlag(int flag);
    //void set(int flag);
    void spotMove(QMouseEvent *event);
    int spotSelected();
    void setHandlePoint(QMouseEvent *event);
    void setSpotOperationFlag(int flag);
    void setZeroPoint(int flag);
    void wheelEvent(QWheelEvent *);
    //与父窗口交互所需要函数
    void getAllColor(spotColorAll&,int &backGroundColorIndex,QColor &backGroundColor);
    int getEventStyle();
    int getDrawOk();
    int getSpotSelectedNum();
    void getSpotNum(int *);
    void getAreaRatio(float *temp);
    float getStretch();
    void setNewColor(QColor *,int colorNum);

    //斑点自动生成函数
    int  saveSpotPoint();
    //------------------xiaotian   测试数码迷彩单个斑点
    void getDigitalSpotPoint();
    void getSpotPoint();//画一个斑点
    void getCanvasPoint(int,int);//画整个画布斑点
    void getCanvasPointS(int,int);//画整个画布斑点

    //生成数码迷彩画布斑点测试  ----xiaotian
    void getCanvasPointSTest(int, int);
    //-------xiaotian    颜色分配与图形分配测试。
    int getCanvasPointSTestByControl(int, int);
    //------------xiaotian  迷彩图案生成算法
    int getCanvasDigital();

    //计算图案面积
    void getAreaRa(float area[1000]);
    //记录每一个数码迷彩图案的面积
    float graphArea[1000];
    int graphCount;
    float uptotalArea;
    void removePath(int index);
    int removeCurrentRow[maxSize];
    int removeCurrentCol[maxSize];
    int removeRow[maxSize];
    int removeCol[maxSize];
    string graphName[maxSize];

    int centerremoveCurrentRow[maxSize];
    int centerremoveCurrentCol[maxSize];
    int centerremoveRow[maxSize];
    int centerremoveCol[maxSize];
    string centergrapName[maxSize];
    int nbFlag;




    //----------xiaotian    记录颜色矩阵
    void getColorRation(int colorJZ[500][500],int count,int value);
    int colorJ[500][500];
    void getCanvasPointS2(int,int);//自动生成数码迷彩
    void getCanvasPointT(int,int);//画整个画布斑点
    void getCanvasPointNew();

    void getCanvasBigPoint();//画大斑点
    void getCanvasBigPointS();
    void getCanvasBigPointT();


    //打开图片
    void openPicture(QString fileName);
    //取得数码迷彩图案
    void getDigitalCanvas(QPainter &p);



    void getEdgePoint();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    //右键
    void rightCpy();
    void rightCut();
    void rightPaste();
    void rightDelete();
    void showSpotEdge(int );
    string drawBlock(int,int,int);
signals:
    void ChildWindowEvent();
    void getShowStretch();
    void getAllColor_s();
    void releaseCtrl_S();
    void spotSelected_S();
    //void spotSelected_one();
protected:
    //void qkeyevent(QKeyEvent *event);
public slots:
private slots:
    void QScrollAreaResize();
    void ChildWindowEventSlot();
private:
    //贴图用
    childWindow *cWindow;
    //int yes;
    //centralWidget大小变化用
    float widthChange;
    float heightChange;
    int preWidth;
    int preHeight;
    int isFirstResize;

    getPoint use;
    saveSpot saveGet;

    //调整图形中心点使用
    QPointF preoffset1;
    int predivX;
    int predivY;


    int flag;
    //0：初始值为0，
    //1：点重合，且非第一个点和最后一个点重合
    //2:选中原点
    //3：第一个点和最后一个点相同，且点的总个数大于2
    //4：选中的点是第一个控制点
    //5：选中的点是第二个控制点
    //6: 选中的是斑点

    //为了同时选中多个斑点用
    int ctrlFlag;
    int markFlag;
    //用来防止鼠标左键放开之后还发生滑动，表示选中状态，但不随mouse移动
    int spotOperation;
    int drawOk;//用来存放已经绘制好的斑点的个数
//    int bigDrawOk[600];
//    int bigDrawOkNum;
//    int smallDrawOk[5000];
//    int smallDrawOkNum;
    int ifCanDraw;
    int drawFlag;
    int showOPoint;

    //1、drawFlag为0表示画笔处于未选中状态
    //2、drawFlag为1表示点了画笔，可以画点
    float forcePointSize;
    float oPointSize;
    list<QPointF*>oPoint;//用户画的原点
    //typedef list<QPointF*> m;
    //list<m>::iterator oP = o.begin();
    list<QPointF*>oPointImage;
    list<QPointF*>thePointImage;
    list<QPointF*>oPointImageAll;//保存图片用
    list<QPointF*>midPoint;
    list<QPointF*>midM;
    list<QPointF*>tranCoo;
    list<QPointF*>thePoint;//控制点
    list<QPointF*>thePointImageAll;//保存图片用
    list<QPointF*>::iterator handleSelectedA;
    list<QPointF*>::iterator handleSelectedB;
    list<QPointF*>::iterator handleSelectedO;
    MainWindow *main;
    QPointF *currentPoint;
    QPoint *currentPoint1;
    QPointF *selectedPoint;
    QPointF handleA;
    QPointF handleB;
    QPointF handleO;
    QPainterPath *pathImage;
    QPainterPath *path;
    QPainterPath *forAutoSpotP[3000];
    QPainterPath *cPath;
    QPainterPath *backRect;
    QColor spotColor;

    //为绘制多个斑点添加的变量
    int pointNum;
    int spotNum[maxSize];
    float stretch[maxSize];
    float rotation[maxSize];

    //为实现斑点移动添加的变量
    //存放斑点中心点坐标
    float spotOriginX[maxSize];
    float spotOriginY[maxSize];

    //为画出五个图（五面贴图用）
    float spotOriginXI[maxSize];
    float spotOriginYI[maxSize];
    //int selectedSpot;

    //保存相对于中心的本次点
    float spotOriginOX[maxSize];
    float spotOriginOY[maxSize];
    //float spotOriginOX[maxSize];
    //float spotOriginOY[maxSize];

    //保存相对于中心的前一次点
    float spotOriginPOX[maxSize];
    float spotOriginPOY[maxSize];
    //float spotOriginPOX[maxSize];
    //float spotOriginPOY[maxSize];


    list<QPointF*>oPointAll;//用户画的原点
    list<QPainterPath*>allPath;
    //-----------xiaotian      画外围内包的点
    list<QPainterPath*>otherPath;





    list<QPointF*>oPointTemp;
    list<QPointF*>thePointTempDraw;
    list<QPointF*>thePointTemp;//用作临时的选中控制点用
    int spotSelectedNum;
    int ctrlSize;//跟下边的变量一起存储选中的点情况
    //int spotSelectedCtrl[500];
    list<int>spotSelectedCtrl;
    int oPointJudge;//用来区分斑点形状相同的时候是选中的哪个斑点的关键点
    int oPointMoveFlag;
    list<QPointF*>handlePointAll;
    spotColorAll allColor;
    list<QPainterPath*>pathImageAll;

    //DrawWidget *centralDraw;
    MainWindow *mainWin;
    //画布变量
    float canvasX;
    float canvasY;
    float canvasZ;
    QPainterPath *canvasPath;
    float areaRatio[maxSize];
    float drawX;
    float drawY;
    float drawZ;

    int firstFlag;
    int drawCanvasFlag;//0，表示为默认画布，1表示画布为只有长和宽的矩形，2表示画布为格子形状
    //窗口随滚动条变化需要的变量
    QScrollArea *showArea;
    float windowScale;
    float preWindowScale;
    int wheelFlag;
    float midWidth;
    float midHeight;
    float preMidWidth;
    float preMidHeight;
    //与父窗口交互所需要变量
    //1：表示有斑点刚刚画完。2：表示选中一个斑点。3：表示斑点形状发生变化。4：表示斑点颜色发生变化。5：表示设置strech
    int eventStyle;
    QColor backGroundColor;
    int backGroundColorIndex;
    int spotLineWidth;
    QColor spotLineColor;
    int keyPointSize;
    QColor keyPointColor;
    int handlePointSize;
    int hPointLineWidth;
    QColor handlePointColor;
    int markNum;//曲率稀疏度
    int minResolution;//曲率半径
    int radiusFlag;
    int addColorNum;

    //为斑点随机与AUTOCAD绘图
    int AutoCADFlag;
    int areaGet;//斑点该随机到哪个区域
    spot *tempSave;


    //回退前进,总共可以进行六次
    spot backForward[11];
    int hasNumBF;
    int nowPlace;

//复制粘贴
    int cpyNum;
    int rightX,rightY;
    int ifShowSpotEdge;
    //用数组方式记录路径
    QPainterPath *canvasPathA[500];

    //为了让连接处斑点颜色统一
    int drawOk1,drawOk2,drawOk3,drawOk4;

    //斑点成片选取用
    int mousePressFlag;
    int xBegin,yBegin,xEnd,yEnd;
    //背景颜色发生变化时用
//    int A[2000];
//    int backGroundSpotNum;



};

#endif // DRAWWIDGET_H
