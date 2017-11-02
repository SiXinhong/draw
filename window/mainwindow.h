#ifndef MainWindow_H
#define MainWindow_H

#include "cvaux.h"
#include "cxcore.h"
#include "highgui.h"
#include <fstream>
#include<stdio.h>
#include <iomanip>
#include<QDebug>
#include "caculate/caculate.h"
#include "caculate/RGB2LAB.h"


#include <QMainWindow>
#include"childwindow.h"
#include<QPainter>
#include <QTextCodec>
#include"caculate/getpoint.h"
#include<QMouseEvent>
#include<list>
#include<QToolButton>
#include<QPushButton>
#include <QSplitter>
#include<QListWidget>
#include<QTreeWidget>
#include <QtCore/QMap>
#include <QtGui/QDoubleSpinBox>
#include<QMap>
#include<QtCore/QMap>
#include <QtGui/QIcon>
#include<QComboBox>
#include<QPixmap>
#include<QLabel>
#include<QBrush>
//#include<QColor>
#include<QDockWidget>
#include<QGroupBox>
#include<QRadioButton>
#include "ui_MainWindow.h"
#include "qtpropertybrowser/qtpropertybrowser.h"
#include "qtpropertybrowser/qteditorfactory.h"
#include "qtpropertybrowser/qttreepropertybrowser.h"
#include"drawWidget/drawwidget.h"
#include"window/spotcolorall.h"
#include"myScrollDialog/mydialog.h"
#include <QTextCodec>
#include <QTextStream>
#include <QFile>
#include<QClipboard>
#include <QObject>
#include<QFileDialog>
#include<QAction>
#include<QMenu>
#include"caculate/colorm.h"
#include"window/mythread.h"
#include"window/controlthread.h"






class DrawWidget;
class colorM;
class myThread;
class controlThread;
//struct spotColorAll;
namespace Ui {
    class MainWindow;
}

//typedef struct{
//    QColor myColorM[maxSize];
//    //int num;
//    int indexM[maxSize];
//    //int flag;
//}spotColorAllM;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString fileName;
    explicit MainWindow(QWidget *parent = 0);
    void getCentral(DrawWidget *centralTemp);
    void getControlThread(controlThread *temp);
    void paintEvent(QPaintEvent *);
    void terminateThread();
    void autoColorS();
    void autoColorF();
    void autoColorFD();
    void autoColorByControl();//���԰����趨����ȥ�����ɫ��
    //------xiaotian   ������ɫ��ռ����
    float caucluateColor(int colorIndex);
    int colorJZ[500][500];


    void getDifferentColor();//�ȿ�������ͼ�����̣߳���������������ݲ�ͬ����ɫ�������ɫ
    int returnGetSize();
    void startThread();
    void endThread();
    //void getThread(controlThread *temp);
    void generateColor(QColor ca[4],QString fileName);//��ȡ����ɫ
    QMessageBox threadMessageBox;
    DrawWidget* centralDraw;


    ~MainWindow();

private:
    Ui::MainWindow *ui;


//    float backGroundProportion1;
    getPoint use;
    int flag;
    //0����ʼֵΪ0��
    //1�����غϣ��ҷǵ�һ��������һ�����غ�
    //2:ѡ��ԭ��
    //3����һ��������һ������ͬ���ҵ���ܸ�������2
    //4��ѡ�еĵ��ǵ�һ�����Ƶ�
    //5��ѡ�еĵ��ǵڶ������Ƶ�
    //6: ѡ�е��ǰߵ�

    int markFlag;
    //������ֹ�������ſ�֮�󻹷�����������ʾѡ��״̬��������mouse�ƶ�

    int drawOk;//��������Ѿ����ƺõİߵ�ĸ���
    int bigDrawOk[600];
    int bigDrawOkNum;
    int smallDrawOk[600];
    int smallDrawOkNum;
    spotColorAll allColor;
    float colorProportion[maxSize];

    float backGroundProportion;
    int spotOperation;//1����ƽ��2������ת3��������

    int drawFlag;
    int OPointFlag;
    //1��drawFlagΪ0��ʾ���ʴ���δѡ��״̬
    //2��drawFlagΪ1��ʾ���˻��ʣ����Ի���


    int forcePointSize;
    int oPointSize;

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
    QPointF *currentPoint;
    QPointF *selectedPoint;
    QPointF handleA;
    QPointF handleB;
    QPointF handleO;
    QPainterPath *pathImage;
    QPainterPath *path;
    QPainterPath *cPath;
    QPainterPath *backRect;
    //QColor backGroundColor;
    QColor spotColor;
    QToolButton *toolBtn;
    //ǰ������
    QToolButton *forWard;
    QToolButton *backWard;
    QToolButton *setOPoint;
    QToolButton *toolBtnSave;
    QToolButton *toolBtnR;
    QToolButton *deleteAll;
    QToolButton *clearOneSpot;
    QToolButton *spotMoveB;
    QToolButton *spotRotation;
    QToolButton *spotZoom;
    QToolButton *autoSpot;
    QToolButton *autoSpotBig;
    QToolButton *autoCanvas;
    QToolButton *spotMapping;
    QToolButton *AutoCAD;
    QToolButton *AutoCADL;
    QToolButton *AutoCADR;
    QToolButton *AutoCADU;
    QToolButton *AutoCADD;
    QToolButton *AutoCADA;
    QToolButton *AutoCADM;
    QToolButton *addOneColor;
    QToolButton *deleteOneColor;
    QToolButton *fiveOpen;
    QToolButton *readProject;
    QToolButton *saveProject;
    //Ϊ���ƶ���ߵ���ӵı���
    int pointNum;
    //int spotNum[maxSize];
    list<QPointF*>oPointAll;//�û�����ԭ��
    list<QPainterPath*>allPath;
    list<QPointF*>oPointTemp;
    list<QPointF*>thePointTempDraw;
    list<QPointF*>thePointTemp;//������ʱ��ѡ�п��Ƶ���
    int spotSelectedNum;
    int oPointMoveFlag;
    list<QPointF*>handlePointAll;
    // allColor;
    list<QPainterPath*>pathImageAll;


    QDialog *myDialog;
    QDialog *myDialogColor;
    QDialog *addColorDialog;
    QDialog *deleteColorDialog;
    int colorChoose;
    QDockWidget rightDock;
    QDockWidget *preRightDock;

    //leftDcokWidget����
    QtGroupPropertyManager *groupManagerL;
    QtGroupPropertyManager *preGroupManagerL;
    QtSpinBoxFactory *spinBoxFactoryL;
    QtSpinBoxFactory *preSpinBoxFactoryL;
    QtEnumPropertyManager *enumManagerL;
    QtEnumPropertyManager *preEnumManagerL;
    QtEnumEditorFactory *comboBoxFactoryL;
    QtEnumEditorFactory *preComboBoxFactoryL;

    //��ɫ
    QtProperty *BGProperty;
    QtProperty *preBGProperty;

    //�ߴ�
    QtProperty *BGPropertySize;
    QtProperty *BGPropertyX;
    QtProperty *BGPropertyY;
    QtProperty *BGPropertyZ;

    //�����
    QtProperty *tempProportion[maxSize];
    QtProperty *preTempProportion[maxSize];


    QToolBar * mainToolBar;//�ڶ���������
    QToolBar * preMainToolBar;
    QStringList *enumNamesL;//������ɫ������
    QStringList *preEnumNamesL;
    QtProperty *task1L;
    QtProperty *task2L;
    QTreeWidget *leftTreeWidget;
    QDockWidget leftDock;
    QtIntPropertyManager *intManagerL;
    QtIntPropertyManager *preIntManagerL;

    QSplitter *splitterRightL;
    QSplitter *preSplitterRightL;



    QtProperty *priority11L;
    QSplitter *splitterMainL;
    QSplitter *preSplitterMainL;
    QtTreePropertyBrowser *editorL;
    QtTreePropertyBrowser *preEditorL;
    QDockWidget *preLeftDockL;
    QtProperty *priority10L;







    QtIntPropertyManager *intManager;
    QtIntPropertyManager *preIntManager;
    QtGroupPropertyManager *groupManager;
    QComboBox *spotComboBox;
    QComboBox *deleteComboBox;

    //�����ɫ��
    int currentIndex11;
    int currentIndex12;
    int currentIndex21;
    int currentIndex22;
    int currentIndex23;
    int currentIndex31;
    int currentIndex32;
    int currentIndex33;
    int currentIndex34;
    QComboBox spotComboBoxD11;
    QComboBox spotComboBoxD12;

    QComboBox spotComboBoxD21;
    QComboBox spotComboBoxD22;
    QComboBox spotComboBoxD23;

    QComboBox spotComboBoxD31;
    QComboBox spotComboBoxD32;
    QComboBox spotComboBoxD33;
    QComboBox spotComboBoxD34;


    QComboBox *backgroundComboBox;
    QSplitter *splitterMain;
    QSplitter *splitterRight;
    QSplitter *preSplitterRight;
    QListWidget *tempListWidget;

    QtProperty *priority10;
    QtProperty *priority11;
    QtProperty *priority12;
    QtProperty *priority13;
    QtProperty *priority14;
    QtProperty *priority1R;
    QtProperty *priority1G;
    QtProperty *priority1B;
    QtProperty *priority15;
    QtProperty *priority16;
    QtProperty *priority17;//�����
    /////////////////����������ã�
    int addColorNum;//�û�������ɫ��Ŀ

    QtProperty *priority20;
    QtProperty *priority21;
    QtProperty *priority22;
    QtProperty *priority2R;
    QtProperty *priority2G;
    QtProperty *priority2B;

    QtProperty *priority30;
    QtProperty *priority31;
    QtProperty *priority32;
    QtProperty *priority33;
    QtProperty *priority3R;
    QtProperty *priority3G;
    QtProperty *priority3B;

    QtProperty *task1;
    QtProperty *task2;
    QtProperty *task3;
    QtSpinBoxFactory *spinBoxFactory;
    QtEnumPropertyManager *enumManager;
    QtEnumPropertyManager *preEnumManager;
    QtEnumEditorFactory *comboBoxFactory;
    QtProperty *item8;
    QStringList *enumNames;
    QtTreePropertyBrowser *editor;
    QColor iconColor[35];
//private:
    //QToolButton toolBtnR;
    //���û������ñ���
    QRadioButton *canvasB;
    QRadioButton *modelB;
    QButtonGroup *allRadio;
    QButtonGroup *allRadioColor;
    QButtonGroup *size;
    int getSize;
    //��ȡ�Ի���QLineEdit����
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;
    QLineEdit *edit5;


    //��ȡ��ɫ��ֵ������
    QLineEdit *editH;
    QLineEdit *editS;
    QLineEdit *editV;
    QLineEdit *editName;
    colorM colorManagement;
    QString colorName[maxSize];
    //ɾ����ɫ����
    QLineEdit *editHD;
    QLineEdit *editSD;
    QLineEdit *editSV;



    //���Ӵ��ڽ����������
    int drawX,drawY,drawZ;
    float modelStretch;
    int spotNum[maxSize];
    float areaRatio[maxSize];
    QColor backGroundColor;
    int backGroundColorIndex;
    int spotLineWidth;
    QColor spotLineColor;
    int keyPointSize;
    QColor keyPointColor;
    int handlePointSize;
    int hPointLineWidth;
    QColor handlePointColor;
    int spotR,spotG,spotB;
    int keyPointR,keyPointG,keyPointB;
    int handlePointR,handlePointG,handlePointB;
    int markNum;//����ϡ���
    int minResolution;//��С�ֱ���
    int radiusFlag;
    spotChangeSpot exchangeS;
    float windowScale;
    int AutoCADFlag;

    //��ѡ��
    int ctrlFlag;
    int ctrlSize;
    list<int>spotSelectedCtrl;

    //�״���ʾ��
    int firstShow;

    QLabel *str;
    QLabel *preStr;//�����label��ӵ�״̬����
    QLabel *lb;    //�����label��ӵ�״̬����
    QLabel *lb1;
    QLabel *preLb;
    QLabel *preLb1;


    //�Ҽ��˵�
    QAction *actCpy;
    QAction *actShowEdge;
    QAction *actCut;
    QAction *paste;
    QAction *actDelete;
    QAction *setColor;
    QAction *refreshAreaRatio;
    QAction *showKeyPoint;
    int rightX,rightY;
    int ifShowSpotEdge;

    QMenu *menu;

    //���Ӵ���ɫ����
    int drawOk1,drawOk2,drawOk3,drawOk4;

    //�ߵ��Զ������߳�
    myThread *mThread;
    controlThread *cThread;




    void initialColor();
protected:
    //spotColorAll a;
    //void paintEvent(QPaintEvent *event);
    //void addLeftQDcokWidget();
    void addBackGroundEdit();
    void addRightQDockWidget();
    void addMyToolBar();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *);
    //void drawCanvas();

public slots:
private slots:
    void autoS();
    void autoC();
    void autoDigitalTest();
    void autoDigital();
    void backWardF();
    void forWardF();
    void addSpotEdit();


    void autoColorT();
    void ChildWindowEventSlot();
    void clearAll();
    void clearOne();
    void closeDialog();
    void closeACDialog();
    void closeDCDialog();
    void closeAddColorDialog();
    void closeDelColorDialog();
    void closeDialogColor();
    void showNotingColor();
    void comboBoxBackGroundChanged();
    void comboBoxSpotChanged();
    void contextMenuEvent(QContextMenuEvent *);
    void caculateColorProportion();
    void copyAutoCADL();
    void copyAutoCADR();
    void copyAutoCADM();
    void copyAutoCADU();
    void copyAutoCADD();
    void copyAutoCADA();
    void showACDialog();
    void showDCDialog();
    //void drawClicked();
    void editBackGround();
    void editOPoint();
    void editForcePoint();
    void editSpot();
    void getAllColor();
    void leftDockWidgetChanged();
    void mapping();
    void on_action_triggered();
    void openPicture();
    void saveSpot();
    void saveCanvasF();
    void readCanvasF();
    void refreshAreaRatio_s();
    void showSpotEdge();
    void setColorD();
    void showDialog();
    void showNoting();
    void showVersion();
    void showStretch();
    void setChange();
    void setRadiusFlag();
    void setDrawFlag();
    void setOPointFlag();
    void setSpotMoveFlag();
    void setRoationFlag();
    void setStretchFlag();
    void spotSelected();
    /////
    void fiveOpenS();
    void rightCpy();
    void rightCut();
    void rightPaste();
    void rightDelete();
    //void clear();
};

#endif // MainWindow_H
