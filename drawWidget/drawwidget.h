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
#define rectSize  10 //9  ԭ����ֵ
class MainWindow;
class childWindow;
class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    //spotColorAll allColor;
    explicit DrawWidget(QWidget *parent = 0);
    int showDigital;

    //��ɫ��Ϣ
    QColor iconColor[maxSize];
    void addAreaSpot();
    void addCtrlSpot();
    void addImagePath();
    void addSpotOrigin(int drawOk);
    void addSpotPoint();
    void addSpecialPath();//spotMove��
    void addHandlePath();
    void areaSelected();
//����������
    void backWardF();
    void forWardF();
    void saveStation();
    void readStation();

    int collisonDetection(int num,float saveP[300][2]);
    void caculateOneCurve2(int uflag);
    void caculateOneCurve();
    //----------xiaotian    ���������Բ�·��  ʹ�þ���ķ�ʽ
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
    //--------------------xiaotian     �������Բʰߵ�,ʹ�þ���Ļ���
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
    //��ȡ�Ӵ���ctrlFlag״̬��spotSelectedCtrl
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
    //-----------xiaotian  ���ðߵ���ɫ
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
    //�븸���ڽ�������Ҫ����
    void getAllColor(spotColorAll&,int &backGroundColorIndex,QColor &backGroundColor);
    int getEventStyle();
    int getDrawOk();
    int getSpotSelectedNum();
    void getSpotNum(int *);
    void getAreaRatio(float *temp);
    float getStretch();
    void setNewColor(QColor *,int colorNum);

    //�ߵ��Զ����ɺ���
    int  saveSpotPoint();
    //------------------xiaotian   ���������Բʵ����ߵ�
    void getDigitalSpotPoint();
    void getSpotPoint();//��һ���ߵ�
    void getCanvasPoint(int,int);//�����������ߵ�
    void getCanvasPointS(int,int);//�����������ߵ�

    //���������Բʻ����ߵ����  ----xiaotian
    void getCanvasPointSTest(int, int);
    //-------xiaotian    ��ɫ������ͼ�η�����ԡ�
    int getCanvasPointSTestByControl(int, int);
    //------------xiaotian  �Բ�ͼ�������㷨
    int getCanvasDigital();

    //����ͼ�����
    void getAreaRa(float area[1000]);
    //��¼ÿһ�������Բ�ͼ�������
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




    //----------xiaotian    ��¼��ɫ����
    void getColorRation(int colorJZ[500][500],int count,int value);
    int colorJ[500][500];
    void getCanvasPointS2(int,int);//�Զ����������Բ�
    void getCanvasPointT(int,int);//�����������ߵ�
    void getCanvasPointNew();

    void getCanvasBigPoint();//����ߵ�
    void getCanvasBigPointS();
    void getCanvasBigPointT();


    //��ͼƬ
    void openPicture(QString fileName);
    //ȡ�������Բ�ͼ��
    void getDigitalCanvas(QPainter &p);



    void getEdgePoint();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    //�Ҽ�
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
    //��ͼ��
    childWindow *cWindow;
    //int yes;
    //centralWidget��С�仯��
    float widthChange;
    float heightChange;
    int preWidth;
    int preHeight;
    int isFirstResize;

    getPoint use;
    saveSpot saveGet;

    //����ͼ�����ĵ�ʹ��
    QPointF preoffset1;
    int predivX;
    int predivY;


    int flag;
    //0����ʼֵΪ0��
    //1�����غϣ��ҷǵ�һ��������һ�����غ�
    //2:ѡ��ԭ��
    //3����һ��������һ������ͬ���ҵ���ܸ�������2
    //4��ѡ�еĵ��ǵ�һ�����Ƶ�
    //5��ѡ�еĵ��ǵڶ������Ƶ�
    //6: ѡ�е��ǰߵ�

    //Ϊ��ͬʱѡ�ж���ߵ���
    int ctrlFlag;
    int markFlag;
    //������ֹ�������ſ�֮�󻹷�����������ʾѡ��״̬��������mouse�ƶ�
    int spotOperation;
    int drawOk;//��������Ѿ����ƺõİߵ�ĸ���
//    int bigDrawOk[600];
//    int bigDrawOkNum;
//    int smallDrawOk[5000];
//    int smallDrawOkNum;
    int ifCanDraw;
    int drawFlag;
    int showOPoint;

    //1��drawFlagΪ0��ʾ���ʴ���δѡ��״̬
    //2��drawFlagΪ1��ʾ���˻��ʣ����Ի���
    float forcePointSize;
    float oPointSize;
    list<QPointF*>oPoint;//�û�����ԭ��
    //typedef list<QPointF*> m;
    //list<m>::iterator oP = o.begin();
    list<QPointF*>oPointImage;
    list<QPointF*>thePointImage;
    list<QPointF*>oPointImageAll;//����ͼƬ��
    list<QPointF*>midPoint;
    list<QPointF*>midM;
    list<QPointF*>tranCoo;
    list<QPointF*>thePoint;//���Ƶ�
    list<QPointF*>thePointImageAll;//����ͼƬ��
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

    //Ϊ���ƶ���ߵ���ӵı���
    int pointNum;
    int spotNum[maxSize];
    float stretch[maxSize];
    float rotation[maxSize];

    //Ϊʵ�ְߵ��ƶ���ӵı���
    //��Űߵ����ĵ�����
    float spotOriginX[maxSize];
    float spotOriginY[maxSize];

    //Ϊ�������ͼ��������ͼ�ã�
    float spotOriginXI[maxSize];
    float spotOriginYI[maxSize];
    //int selectedSpot;

    //������������ĵı��ε�
    float spotOriginOX[maxSize];
    float spotOriginOY[maxSize];
    //float spotOriginOX[maxSize];
    //float spotOriginOY[maxSize];

    //������������ĵ�ǰһ�ε�
    float spotOriginPOX[maxSize];
    float spotOriginPOY[maxSize];
    //float spotOriginPOX[maxSize];
    //float spotOriginPOY[maxSize];


    list<QPointF*>oPointAll;//�û�����ԭ��
    list<QPainterPath*>allPath;
    //-----------xiaotian      ����Χ�ڰ��ĵ�
    list<QPainterPath*>otherPath;





    list<QPointF*>oPointTemp;
    list<QPointF*>thePointTempDraw;
    list<QPointF*>thePointTemp;//������ʱ��ѡ�п��Ƶ���
    int spotSelectedNum;
    int ctrlSize;//���±ߵı���һ��洢ѡ�еĵ����
    //int spotSelectedCtrl[500];
    list<int>spotSelectedCtrl;
    int oPointJudge;//�������ְߵ���״��ͬ��ʱ����ѡ�е��ĸ��ߵ�Ĺؼ���
    int oPointMoveFlag;
    list<QPointF*>handlePointAll;
    spotColorAll allColor;
    list<QPainterPath*>pathImageAll;

    //DrawWidget *centralDraw;
    MainWindow *mainWin;
    //��������
    float canvasX;
    float canvasY;
    float canvasZ;
    QPainterPath *canvasPath;
    float areaRatio[maxSize];
    float drawX;
    float drawY;
    float drawZ;

    int firstFlag;
    int drawCanvasFlag;//0����ʾΪĬ�ϻ�����1��ʾ����Ϊֻ�г��Ϳ�ľ��Σ�2��ʾ����Ϊ������״
    //������������仯��Ҫ�ı���
    QScrollArea *showArea;
    float windowScale;
    float preWindowScale;
    int wheelFlag;
    float midWidth;
    float midHeight;
    float preMidWidth;
    float preMidHeight;
    //�븸���ڽ�������Ҫ����
    //1����ʾ�аߵ�ոջ��ꡣ2����ʾѡ��һ���ߵ㡣3����ʾ�ߵ���״�����仯��4����ʾ�ߵ���ɫ�����仯��5����ʾ����strech
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
    int markNum;//����ϡ���
    int minResolution;//���ʰ뾶
    int radiusFlag;
    int addColorNum;

    //Ϊ�ߵ������AUTOCAD��ͼ
    int AutoCADFlag;
    int areaGet;//�ߵ��������ĸ�����
    spot *tempSave;


    //����ǰ��,�ܹ����Խ�������
    spot backForward[11];
    int hasNumBF;
    int nowPlace;

//����ճ��
    int cpyNum;
    int rightX,rightY;
    int ifShowSpotEdge;
    //�����鷽ʽ��¼·��
    QPainterPath *canvasPathA[500];

    //Ϊ�������Ӵ��ߵ���ɫͳһ
    int drawOk1,drawOk2,drawOk3,drawOk4;

    //�ߵ��Ƭѡȡ��
    int mousePressFlag;
    int xBegin,yBegin,xEnd,yEnd;
    //������ɫ�����仯ʱ��
//    int A[2000];
//    int backGroundSpotNum;



};

#endif // DRAWWIDGET_H
