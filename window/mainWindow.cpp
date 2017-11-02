#include "MainWindow.h"

//提取主题色
#define nClusters 300
#define new_nClusters 4
#define MY_FELEM(mat, i, j) CV_MAT_ELEM(*(mat), float, i, j)
#define MY_BELEM(mat, i, j) CV_MAT_ELEM(*(mat), BYTE, i, j)
#define MY_SELEM(mat, i, j) CV_MAT_ELEM(*(mat), short, i, j)
#define MY_LELEM(mat, i, j) CV_MAT_ELEM(*(mat), long, i, j)
#define MY_DELEM(mat, i, j) CV_MAT_ELEM(*(mat), double, i, j)

/**********************
*  对图片中的颜色进行排序  *
 *********************/
user_head *_head = NULL;
sort_color *sort_head = NULL;
int tmp_count = 0;






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    //connect(ui->showChildWindow,SIGNAL(clicked()),this,SLOT(showChildWindow()));

    this->addToolBarBreak();
    this->addToolBarBreak();

    mainToolBar=NULL;
    preMainToolBar=NULL;

    getSize=0;
    modelStretch=1;
    drawX=400;
    drawY=300;
    drawZ=0;
    AutoCADFlag=0;

    forcePointSize=5;
    oPointSize=5;
    drawFlag=0;
    OPointFlag=0;
    radiusFlag=0;
    spotOperation=1;
    drawOk=0;
    spotSelectedNum=0;
    spotComboBox=NULL;
    //showDialog();
    backGroundColorIndex=29;
    //backGroundProportion=0;

    //多选用
    ctrlFlag=0;
    ctrlSize=0;

    //首次显示用
    firstShow=0;

    //初始化线程
    mThread=new myThread(this);


    spotR=0;spotG=0;spotB=255;
    keyPointR=255;keyPointG=0;keyPointB=255;
    handlePointR=0;handlePointG=0;handlePointB=255;

    windowScale=0;
    spotLineWidth=1;
    spotLineColor=QColor(spotR,spotG,spotB);
    keyPointSize=20;
    keyPointColor=QColor(keyPointR,keyPointG,keyPointG);
    handlePointSize=10;
    //hPointLineWidth=1;
    handlePointColor=QColor(handlePointR,handlePointG,handlePointB);
    markNum=100;//曲率稀疏度
    minResolution=30;//曲率半径
    backGroundColor.setRgb(255,255,255);

    //spotComboBoxD11.clear();

    preEnumManager=NULL;
    preIntManager=NULL;
    preSplitterRight = NULL;
    preBGProperty=NULL;
    BGProperty=NULL;
    preRightDock = NULL;
    preLb1 = NULL;

    preIntManagerL=NULL;
    preSplitterMainL=NULL;
    preSplitterRightL=NULL;
    preIntManagerL=NULL;
    preEnumNamesL=NULL;
    preGroupManagerL=NULL;
    preSpinBoxFactoryL=NULL;
    preEnumManagerL=NULL;
    preComboBoxFactoryL=NULL;
    preEditorL=NULL;
    //初始化斑点颜色
    addColorNum=0;//颜色数目
    for(int i=0;i<maxSize;i++){
        allColor.myColor[i].setRgb(255,255,255);
        allColor.index[i]=29;
        allColor.colorName[i]="";
    }
    //初始化颜色比
    for(int i=1;i<35;i++){
        colorProportion[i]=0;
    }
    //初始化面积比
    for(int i=1;i<35;i++){
        tempProportion[i]=NULL;
    }
    for(int i=1;i<35;i++){
        preTempProportion[i]=NULL;
    }
    //初始化所要获取的图纸的标记
    //copyFlag=1;

    str=NULL;
    preStr=NULL;//将这个label添加到状态栏中
    lb=NULL;    //将这个label添加到状态栏中
    preLb=NULL;

    exchangeS.handlePointColor=handlePointColor;
    exchangeS.handlePointR=handlePointR;
    exchangeS.handlePointG=handlePointG;
    exchangeS.handlePointB=handlePointB;
    exchangeS.handlePointSize=handlePointSize;
    exchangeS.hPointLineWidth=hPointLineWidth;

    exchangeS.keyPointColor=keyPointColor;
    exchangeS.keyPointSize=keyPointSize;

    exchangeS.markNum=markNum;
    exchangeS.minResolution=minResolution;

    exchangeS.spotLineColor=spotLineColor;
    exchangeS.spotLineWidth=spotLineWidth;

    drawOk1=0,drawOk2=0,drawOk3=0,drawOk4=0;


    QColor temp;

    //    temp.setRgb(72,77,64);temp.setHsv(83,43,77);iconColor[1]=temp;temp.setRgb(76,81,69);temp.setHsv(85,37,81);iconColor[2]=temp;
    //    temp.setRgb(77,88,69);temp.setHsv(94,55,88);iconColor[3]=temp;temp.setRgb(83,91,74);temp.setHsv(88,47,91);iconColor[4]=temp;
    temp.setRgb(178.371,179.721,157.561);iconColor[1]=temp;temp.setRgb(103.156,125.768,43.992);iconColor[2]=temp;
    temp.setRgb(65.0947,78.5004,36.5558);iconColor[3]=temp;temp.setRgb(104.462,107.685,99.9589);iconColor[4]=temp;




    temp.setRgb(80,95,61);temp.setHsv(86,91,95);iconColor[5]=temp;temp.setRgb(99,106,74);temp.setHsv(73,77,106);iconColor[6]=temp;
    temp.setRgb(96,99,76);temp.setHsv(67,59,99);iconColor[7]=temp;temp.setRgb(109,111,64);temp.setHsv(62,108,111);iconColor[8]=temp;
    temp.setRgb(87,81,74);temp.setHsv(32,38,87);iconColor[9]=temp;temp.setRgb(98,81,65);temp.setHsv(29,86,98);iconColor[10]=temp;
    temp.setRgb(105,93,71);temp.setHsv(38,82,105);iconColor[11]=temp;temp.setRgb(105,94,72);temp.setHsv(40,80,105);iconColor[12]=temp;
    temp.setRgb(110,94,87);temp.setHsv(18,53,110);iconColor[13]=temp;temp.setRgb(139,110,86);temp.setHsv(27,97,139);iconColor[14]=temp;
    temp.setRgb(129,115,94);temp.setHsv(36,69,129);iconColor[15]=temp;temp.setRgb(117,84,63);temp.setHsv(23,118,117);iconColor[16]=temp;
    temp.setRgb(134,92,75);temp.setHsv(17,112,134);iconColor[17]=temp;temp.setRgb(123,111,78);temp.setHsv(44,93,123);iconColor[18]=temp;
    //    temp.setRgb(162,125,95);temp.setHsv(26,105,162);iconColor[19]=temp;temp.setRgb(170,136,99);temp.setHsv(31,106,170);iconColor[20]=temp;
    //    temp.setRgb(184,146,99);temp.setHsv(33,118,184);iconColor[21]=temp;temp.setRgb(202,150,96);temp.setHsv(30,134,202);iconColor[22]=temp;
    temp.setRgb(43.1485,69.9915,22.1081);iconColor[19]=temp;temp.setRgb(90.0164,118.484,44.5868);iconColor[20]=temp;
    temp.setRgb(71.3203,96.9174,32.867);iconColor[21]=temp;temp.setRgb(108.426,126.502,62.806);iconColor[22]=temp;
    //    temp.setRgb(146,123,87);temp.setHsv(36,103,146);iconColor[23]=temp;temp.setRgb(146,127,104);temp.setHsv(32,73,146);iconColor[24]=temp;
    //    temp.setRgb(136,134,127);temp.setHsv(46,16,136);iconColor[25]=temp;temp.setRgb(158,137,108);temp.setHsv(34,81,158);iconColor[26]=temp;
    temp.setRgb(131.408,141.206,108.518);iconColor[23]=temp;temp.setRgb(84.0282,95.2832,80.1185);iconColor[24]=temp;
    temp.setRgb(86.6,86.98,93.0486);iconColor[25]=temp;temp.setRgb(142.48,142.583,145.358);iconColor[26]=temp;
    //    temp.setRgb(166,155,138);temp.setHsv(36,43,166);iconColor[27]=temp;temp.setRgb(182,166,141);temp.setHsv(36,57,182);iconColor[28]=temp;
    //    temp.setRgb(69,68,68);temp.setHsv(180,7,68);iconColor[29]=temp;temp.setRgb(236,235,233);temp.setHsv(40,3,236);iconColor[30]=temp;
    temp.setRgb(68.4632,86.4538,45.96);iconColor[27]=temp;temp.setRgb(101.311,96.4732,94.9814);iconColor[28]=temp;
    temp.setRgb(97.4025,155.778,60.6729);iconColor[29]=temp;temp.setRgb(121.24,126.061,90.6117);iconColor[30]=temp;
    //    a.setRgb(68.4632,86.4538,45.96);//118.133,93.2779,69.0604
    //    a.setRgb(101.311,96.4732,94.9814);//118.133,93.2779,69.0604
    //    a.setRgb(97.4025,155.778,60.6729);//118.133,93.2779,69.060
    //    a.setRgb(121.24,126.061,90.6117);

    //初始化颜色下拉条
    initialColor();


    //    centralDraw=new DrawWidget(this);
    //    this->setCentralWidget(centralDraw);
    //    forcePointSize=20;
    //    oPointSize=20;
    //    spotColor.setRgb(255,255,255);
    //    backGroundColor.setRgb(255,255,255);
    //    connect(spotMapping,SIGNAL(clicked()),this,SLOT(mapping()));
    //    connect(intManager, SIGNAL(valueChanged(QtProperty *, int)),
    //            this, SLOT(editForcePoint()));

    addMyToolBar();

    //    connect(deleteAll,SIGNAL(clicked()),this,SLOT(clearAll()));
    //    connect(backWard,SIGNAL(clicked()),this,SLOT(backWardF()));
    //    connect(forWard,SIGNAL(clicked()),this,SLOT(forWardF()));
    //connect(clearOneSpot,SIGNAL(clicked()),this,SLOT(clearOne()));


    //connect(toolBtn,SIGNAL(clicked()),this,SLOT(setDrawFlag()));
    //connect(setOPoint,SIGNAL(clicked()),this,SLOT(setOPointFlag()));
    //    connect(spotMoveB,SIGNAL(clicked()),this,SLOT(setSpotMoveFlag()));
    //    connect(spotRotation,SIGNAL(clicked()),this,SLOT(setRoationFlag()));
    //    connect(spotZoom,SIGNAL(clicked()),this,SLOT(setStretchFlag()));
    //    connect(toolBtnR,SIGNAL(clicked()),this,SLOT(setRadiusFlag()));
    //    connect(spotMapping,SIGNAL(clicked()),this,SLOT(mapping()));
    //spotMapping
    //    connect(autoSpot,SIGNAL(clicked()),this,SLOT(autoS()));
    //    connect(autoCanvas,SIGNAL(clicked()),this,SLOT(autoC()));
    //connect(AutoCAD,SIGNAL(clicked()),this,SLOT(saveSpot()));
    //    connect(fiveOpen,SIGNAL(clicked()),this,SLOT(fiveOpenS()));

    //    connect(AutoCADL,SIGNAL(clicked()),this,SLOT(copyAutoCADL()));
    //    connect(AutoCADR,SIGNAL(clicked()),this,SLOT(copyAutoCADR()));
    //    connect(AutoCADM,SIGNAL(clicked()),this,SLOT(copyAutoCADM()));
    //    connect(AutoCADU,SIGNAL(clicked()),this,SLOT(copyAutoCADU()));
    //    connect(AutoCADD,SIGNAL(clicked()),this,SLOT(copyAutoCADD()));
    //    connect(AutoCADA,SIGNAL(clicked()),this,SLOT(copyAutoCADA()));
    //    connect(readProject,SIGNAL(clicked()),this,SLOT(readCanvasF()));
    //    connect(saveProject,SIGNAL(clicked()),this,SLOT(saveCanvasF()));
    //颜色管理对话框
    //    connect(addOneColor,SIGNAL(clicked()),this,SLOT(showACDialog()));
    //    connect(deleteOneColor,SIGNAL(clicked()),this,SLOT(showDCDialog()));

    //pathImage=new(QPainterPath);
    //connect(,SIGNAL(triggered()),this,SLOT(showDialog()));
    QActionGroup *group=new QActionGroup(this);
    QAction *setCanvas=group->addAction(tr("新建画板"));
    ui->menu_2->addAction(setCanvas);
    connect(setCanvas,SIGNAL(triggered()),this,SLOT(showDialog()));

    //xin cong 1030 0:32
    QAction *openProject=group->addAction(tr("打开工程"));
    ui->menu_2->addAction(openProject);
    connect(openProject,SIGNAL(triggered()),this,SLOT(openProject()));

    QAction *saveProject=group->addAction(tr("保存工程"));
    ui->menu_2->addAction(saveProject);
    connect(saveProject,SIGNAL(triggered()),this,SLOT(saveCanvasF()));

    //打开图片
    QAction *openPicture=group->addAction(tr("打开图片"));
    ui->menu_2->addAction(openPicture);
    connect(openPicture,SIGNAL(triggered()),this,SLOT(openPicture()));


    QActionGroup *group2=new QActionGroup(this);
    QAction *back=group2->addAction(tr("回退"));
    ui->menu_3->addAction(back);
    connect(back,SIGNAL(triggered()),this,SLOT(backWardF()));


    QAction *go=group2->addAction(tr("前进"));
    ui->menu_3->addAction(go);
    connect(go,SIGNAL(triggered()),this,SLOT(forWardF()));

    QAction *copy=group2->addAction(tr("复制"));
    ui->menu_3->addAction(copy);
    connect(copy,SIGNAL(triggered()),this,SLOT(rightCpy()));

    QAction *paste1=group2->addAction(tr("粘贴"));
    ui->menu_3->addAction(paste1);
    connect(paste1,SIGNAL(triggered()),this,SLOT(rightPaste()));

    QAction *del=group2->addAction(tr("删除"));
    ui->menu_3->addAction(del);
    connect(del,SIGNAL(triggered()),this,SLOT(rightDelete()));


    QActionGroup *group3=new QActionGroup(this);
    QAction *pen=group3->addAction(tr("画笔"));
    ui->menu4->addAction(pen);
    connect(pen,SIGNAL(triggered()),this,SLOT(setDrawFlag()));

    QAction *brush=group3->addAction(tr("橡皮"));
    ui->menu4->addAction(brush);
    connect(brush,SIGNAL(triggered()),this,SLOT(clearAll()));

    QAction *brush1=group3->addAction(tr("移动"));
    ui->menu4->addAction(brush1);
    connect(brush1,SIGNAL(triggered()),this,SLOT(setSpotMoveFlag()));

    QAction *brush2=group3->addAction(tr("放缩"));
    ui->menu4->addAction(brush2);
    connect(brush2,SIGNAL(triggered()),this,SLOT(setStretchFlag()));

    QAction *brush3=group3->addAction(tr("旋转"));
    ui->menu4->addAction(brush3);
    connect(brush3,SIGNAL(triggered()),this,SLOT(setRoationFlag()));

    QAction *brush4=group3->addAction(tr("单斑点生成"));
    ui->menu4->addAction(brush4);
    connect(brush4,SIGNAL(triggered()),this,SLOT(autoS()));

    QAction *brush5=group3->addAction(tr("全图生成"));
    ui->menu4->addAction(brush5);
    connect(brush5,SIGNAL(triggered()),this,SLOT(autoC()));


    QActionGroup *group4=new QActionGroup(this);
    QAction *modelfram=group4->addAction(tr("三维展示界面"));
    ui->menuT->addAction(modelfram);
    connect(modelfram,SIGNAL(triggered()),this,SLOT(mapping()));

    QAction *fivefram=group4->addAction(tr("五面贴图界面"));
    ui->menuT->addAction(fivefram);
    connect(fivefram,SIGNAL(triggered()),this,SLOT(fiveOpenS()));

    QActionGroup *group5=new QActionGroup(this);
    QAction *colper=group5->addAction(tr("颜色比设置"));
    ui->menu_4->addAction(colper);
    connect(colper,SIGNAL(triggered()),this,SLOT(setColorD()));


    QAction *f5=group5->addAction(tr("刷新面积比"));
    ui->menu_4->addAction(f5);
    connect(f5,SIGNAL(triggered()),this,SLOT(refreshAreaRatio_s()));

    QAction *keyspot=group5->addAction(tr("显示/不显示关键点"));
    ui->menu_4->addAction(keyspot);
    connect(keyspot,SIGNAL(triggered()),this,SLOT(setOPointFlag()));

    QActionGroup *group6=new QActionGroup(this);
    QAction *cad_cen=group6->addAction(tr("获取中间视图"));
    ui->menuCAD->addAction(cad_cen);
    connect(cad_cen,SIGNAL(triggered()),this,SLOT(copyAutoCADM()));

    QAction *cad_up=group6->addAction(tr("获取前视图"));
    ui->menuCAD->addAction(cad_up);
    connect(cad_up,SIGNAL(triggered()),this,SLOT(copyAutoCADU()));

    QAction *cad_down=group6->addAction(tr("获取后视图"));
    ui->menuCAD->addAction(cad_down);
    connect(cad_down,SIGNAL(triggered()),this,SLOT(copyAutoCADD()));

    QAction *cad_L=group6->addAction(tr("获取左视图"));
    ui->menuCAD->addAction(cad_L);
    connect(cad_L,SIGNAL(triggered()),this,SLOT(copyAutoCADL()));

    QAction *cad_R=group6->addAction(tr("获取右视图"));
    ui->menuCAD->addAction(cad_R);
    connect(cad_R,SIGNAL(triggered()),this,SLOT(copyAutoCADR()));

    QAction *cad_ALL=group6->addAction(tr("获取全部视图"));
    ui->menuCAD->addAction(cad_ALL);
    connect(cad_ALL,SIGNAL(triggered()),this,SLOT(copyAutoCADA()));

    QActionGroup *group1=new QActionGroup(this);
    QAction *version=group1->addAction(tr("版本信息"));
    ui->menu->addAction(version);
    connect(version,SIGNAL(triggered()),this,SLOT(showVersion()));
    //leftDock=new QDockWidget(QObject::tr("属性框"),this);
    //addLeftQDcokWidget();
    addBackGroundEdit();
    addSpotEdit();


    menu = new QMenu(this);
    ifShowSpotEdge=1;//设置开始的时候显示斑点边缘
    actCpy=new QAction(tr("复制"), menu);
    //actCut=new QAction(tr("剪切"), menu);
    paste=new QAction(tr("粘贴"), menu);
    actShowEdge=new QAction(tr("显示/不显示斑点边缘线"), menu);
    actDelete=new QAction(tr("删除"), menu);
    setColor=new QAction(tr("设置颜色及斑点大小"),menu);
    refreshAreaRatio=new QAction(tr("刷新面积比"),menu);
    showKeyPoint=new QAction(tr("显示/不显示 关键点"),menu);
    rightX=0;
    rightY=0;
    connect(actCpy,SIGNAL(triggered()),this,SLOT(rightCpy()));
    connect(actShowEdge,SIGNAL(triggered()),this,SLOT(showSpotEdge()));
    connect(paste,SIGNAL(triggered()),this,SLOT(rightPaste()));
    connect(actDelete,SIGNAL(triggered()),this,SLOT(rightDelete()));
    connect(setColor,SIGNAL(triggered()),this,SLOT(setColorD()));
    connect(refreshAreaRatio,SIGNAL(triggered()),this,SLOT(refreshAreaRatio_s()));
    connect(showKeyPoint,SIGNAL(triggered()),this,SLOT(setOPointFlag()));
    connect(actCpy,SIGNAL(triggered()),this,SLOT(showSpotEdge()));
    showStretch();

    //this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    childWindow *child=new childWindow;
    child->show();
}
//提取主题色
void MainWindow::generateColor(QColor ca[],QString fileName){
    IplImage* img=cvLoadImage(fileName.toLatin1().data());//加载图像，图像放在Debug文件夹里，这里是相对路径
    IplImage *pResult=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,3);//创建用于显示的图像，二值图像

    char outimg[] = "data\\out_img.txt"; // 此处写入文件名
    char str_time[] = "data\\time.txt"; // 此处写入文件名
    char _statistics[] = "data\\statistics.txt"; // 此处写入文件名
    char _statistics_end[] = "data\\_statistics_af_caculate.txt"; // 此处写入文件名

    //ofstream or_imag(original);
    ofstream out_img(outimg);
    ofstream out_time(str_time);
    ofstream statistics(_statistics);
    ofstream statistics_af_caculate(_statistics_end);
    ofstream out("data\\color.txt");
    ofstream statistics_af_caculate_end("data\\statistics_af_caculate_end.txt");

    int i,j;
    CvMat*samples=cvCreateMat((img->width)*(img->height),1,CV_32FC3);//创建样本矩阵，CV_32FC3代表位浮点通道（彩色图像）
    CvMat*clusters=cvCreateMat((img->width)*(img->height),1,CV_32SC1);//创建类别标记矩阵，CV_32SF1代表位整型通道
    CvMat*centers=cvCreateMat(nClusters,1,CV_32FC3);//创建类别标记矩阵，CV_32SF1代表位整型通道

    int k=0;
    for (i=0;i<img->width;i++)
    {
        for(j=0;j<img->height;j++)
        {
            CvScalar s;
            //获取图像各个像素点的三通道值（RGB）
            s.val[0]=(float)cvGet2D(img,j,i).val[0];
            s.val[1]=(float)cvGet2D(img,j,i).val[1];
            s.val[2]=(float)cvGet2D(img,j,i).val[2];
            cvSet2D(samples,k++,0,s);//将像素点三通道的值按顺序排入样本矩阵
        }
    }
    /*****************
                            * 统计聚类后颜色分类 *
                             ****************/
    /*****************
*  计算程序运行时间  *
 ****************/
    clock_t start,finish;
    double totaltime;
    start=clock();
    cvKMeans_3(samples,nClusters,clusters,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,100,1.0),1, (CvRNG *)0,0, centers,0,out);//开始聚类，迭代次，终止误差.0
    /********************************
                      *          计算程序运行时间         *
                       ********************************/
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    out_time << "\n此程序的运行时间为" << totaltime << " 秒！" << endl;
    /*********************************
                    * 将图片中原来的颜色替换为提取过后的颜色 *
                     ********************************/
    _head = NULL;
    sort_head = NULL;
    tmp_count = 0;
    k = 0;
    for (i=0;i<img->width;i++){
        for(j=0;j<img->height;j++)
        {
            int index =cvGet2D(clusters,k,0).val[0];
            float need_color = 0;
            need_color = cvGet2D(centers,index,0).val[0]*0.072169
                    + cvGet2D(centers,index,0).val[1]*0.715160
                    + cvGet2D(centers,index,0).val[2]*0.212671;
            if(need_color < 230 && need_color > 40){
                insert(cvGet2D(centers,index,0).val[0],
                       cvGet2D(centers,index,0).val[1],
                       cvGet2D(centers,index,0).val[2],
                       &_head);
            }

            /********************************
                          *   把颜色导入到新的样本矩阵中看效果   *
                           ********************************/
            CvScalar s;
            //获取图像各个像素点的三通道值（RGB）
            s.val[0]=cvGet2D(centers,index,0).val[0];
            s.val[1]=cvGet2D(centers,index,0).val[1];
            s.val[2]=cvGet2D(centers,index,0).val[2];
            cvSet2D(samples,k,0,s);
            /**************************
                            *   把图片中原来的颜色进行替换  *
                            **************************/
            cvSet2D(img,j,i,cvGet2D(centers,index,0));
            cvSet2D(pResult,j,i,cvGet2D(centers,index,0));
            k++;
        }
    }
    /********************************
                   *  对处理后图片颜色排序同时输出到文本  *
                    ********************************/
    float a,b,c;
    user_head *_tmp= _head;//初始化记录链表;
    tmp_count = 0;
    while(_tmp != NULL){
        tmp_count += 1;
        a = _tmp->data.r;
        b = _tmp->data.g;
        c = _tmp->data.b;
        //out_img << _tmp->_num << endl;
        sortcolor(a,b,c,_tmp->_num,&sort_head);
        _tmp = _tmp->next;
    }
    /***********************
                      *  新版本聚类算法用到的变量  *
                       ***********************/
    CvMat*new_samples=cvCreateMat(tmp_count,1,CV_32FC3);//创建样本矩阵，CV_32FC3代表位浮点通道（彩色图像）
    CvMat*new_clusters=cvCreateMat(tmp_count,1,CV_32SC1);//创建类别标记矩阵，CV_32SF1代表位整型通道
    CvMat*new_centers=cvCreateMat(new_nClusters,1,CV_32FC3);//创建类别标记矩阵，CV_32SF1代表位整型通道
    statistics << "处理后颜色总数：" << tmp_count << endl;

    sort_color* tmp_color;
    tmp_color = sort_head;
    k = 0;
    int num[1200];
    for(int i =0;i < 1000;i++){
        num[i] = 0;
    }

    QColor allColor[nClusters];
    while(tmp_color != NULL){
        CvScalar s;
        RGB2LAB(tmp_color->data.b,
                tmp_color->data.g,
                tmp_color->data.r,
                a,b,c/*(float)s.val[0],(float)s.val[1],(float)s.val[2]*/);
        //获取图像各个像素点的三通道值(RGB)图片中存放的为BGR不是RGB，所以这地方要换一下顺序
        s.val[0]=/*(int)*/a;
        s.val[1]=/*(int)*/b;
        s.val[2]=/*(int)*/c;
        allColor[k].setRed(tmp_color->data.b);
        allColor[k].setGreen(tmp_color->data.g);
        allColor[k].setBlue(tmp_color->data.r);
        cvSet2D(new_samples,k++,0,s);//将像素点三通道的值按顺序排入样本矩阵
        num[k] = tmp_color->color_num;
        statistics_af_caculate << left << k << ","
                               << tmp_color->data.b << ","
                               << tmp_color->data.g << ","
                               << tmp_color->data.r << ","
                               << setw(3) <<
                                  tmp_color->color_num
                               <<endl;
        tmp_color = tmp_color->next;
    }

    /****************
                         *  新版本聚类算法  *
                          ***************/
    int center_or_label[30];
    for(int i = 0;i < 30;i++){
        center_or_label[i] = -1;
    }
    new_cvKMeans_3(new_samples,new_nClusters,new_clusters,
                   cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.01),10000/*attemps*/, (CvRNG *)0,0,
                   new_centers,0,out,num,center_or_label);//开始聚类，迭代次，终止误差.0


    for(int i = 0;i < new_nClusters;i++){
        statistics_af_caculate << "index:" << center_or_label[i]+1 << endl;
    }


    _head = NULL;
    sort_head = NULL;
    int end_count = 0;
    for(int i = 0;i < tmp_count;i++){
        int index =cvGet2D(new_clusters,i,0).val[0];
        if(index > -1){
            insert(cvGet2D(new_centers,index,0).val[0],
                   cvGet2D(new_centers,index,0).val[1],
                   cvGet2D(new_centers,index,0).val[2],
                   &_head);
        }
    }

    _tmp = _head;//初始化记录链表
    while(_tmp != NULL){
        end_count += 1;
        a = _tmp->data.r;
        b = _tmp->data.g;
        c = _tmp->data.b;
        sortcolor(a,b,c,_tmp->_num,&sort_head);
        _tmp = _tmp->next;
    }

    tmp_color = sort_head;
    k = 0;

    //QColor ca[new_nClusters];

    while(tmp_color != NULL){
        statistics_af_caculate_end << left << k++ << ","
                                   << tmp_color->data.r << ","
                                   << tmp_color->data.g << ","
                                   << tmp_color->data.b << ","
                                   << setw(3) <<
                                      tmp_color->color_num
                                   <<endl;

        tmp_color = tmp_color->next;
    }
    for(int i = 0;i < new_nClusters;i++){
        ca[i] = allColor[center_or_label[i]];
        statistics_af_caculate << "index111:" << center_or_label[i]<< endl;
    }
}


//主题色分配
void MainWindow::autoColorFD(){
    QColor temp[4];
    //提取主题色
    generateColor(temp,fileName);

    //temp[0].getRgb();
    //index与RGB颜色对应
    for(int i=0;i<4;i++){
        centralDraw->iconColor[i+1]=temp[i];
    }

    /*
   centralDraw->iconColor[1]=temp;
    centralDraw->iconColor[2]=temp;
    centralDraw->iconColor[3]=temp;
    centralDraw->iconColor[4]=temp;
    */
    //数码迷彩颜色设置
    currentIndex31=1;
    currentIndex32=2;
    currentIndex33=3;
    currentIndex34=4;



    int tempSmallAll;
    centralDraw->getAreaRatio(areaRatio);
    centralDraw->getPointStyle(bigDrawOk,bigDrawOkNum,smallDrawOk,smallDrawOkNum,tempSmallAll);

    caculateColorProportion();
    //3:3:2:2
    float proportionA,proportionB=0,proportionC=0,proportionD=0;
    int countA,countB,countC,countD;
    countA=0;countB=0;countC=0;countD=0;
    int A[1500],B[1500],C[1500],D[1500];
    proportionA=backGroundProportion;

    if(proportionA>30){
        for(int i=1;i<bigDrawOkNum+1;){

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


        }

        for(int i=1;i<smallDrawOkNum+1;){
            //qDebug("%d",i);
            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }

            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;




            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;



            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;
        }

        //测试斑点分配
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex33;
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex31;
        }
        for(int t=1;t<countD+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[D[t]]=currentIndex32;
        }

        backGroundColorIndex=currentIndex34;
        backGroundColor=iconColor[backGroundColorIndex];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();


        //qDebug(">0.3 bai  fen  bi  shi:%f   %f   %f   %f",proportionA,proportionB,proportionC,proportionD);
    }
    else{
        //qDebug("aaaaaaaaaaaaaaaaaaa:%f",proportionA);
        for(int i=1;i<bigDrawOkNum+1;){
            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
                //qDebug("***********%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;
            qDebug("@@@@@@@@@@@@@@@@@@%d",i);
        }


        for(int i=1;i<smallDrawOkNum+1;){

            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
        }


        //测试斑点分配
        for(int t=1;t<countA+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[A[t]]=currentIndex34;
            //qDebug("A######%d",A[t]);
        }
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex33;
            //qDebug("B######%d",B[t]);
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex32;
            //qDebug("C######%d",C[t]);
        }
        for(int t=1;t<countD+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[D[t]]=currentIndex31;
            //qDebug("D######%d",D[t]);
        }

        for(int i=1;i<bigDrawOkNum+1;i++){
            qDebug("~~~~~~~~~~~~~~~~~%d",bigDrawOk[i]);
        }

        backGroundColorIndex=currentIndex34;
        backGroundColor=iconColor[backGroundColorIndex];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();
        //qDebug("<0.3 bai  fen  bi  shi:%f   %f   %f   %f",proportionA,proportionB,proportionC,proportionD);
    }

}

//---------xiaotian   计算颜色所占比例
float MainWindow::caucluateColor(int colorIndex){
    int count = 0;
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            if(colorJZ[i][j] == colorIndex){
                count++;
            }
        }
    }

    return count;
}

//-----------xiaotian      测试颜色按照设定比例填充 40:30:25:5
void MainWindow::autoColorByControl(){
    centralDraw->showDigital = 1;
    //40:30:25:5  测试斑点颜色分配
    int countA,countB,countC,countD;
    countA=0;countB=0;countC=0;countD=0;
    float proportionA,proportionB=0,proportionC=0,proportionD=0;
    double countProA = 0.4;
    double countProB = 0.3;
    double countProC = 0.25;
    double countProD = 0.05;
    caculateColorProportion();

    proportionA=backGroundProportion;

    float totalCount = 2*(drawX/10) * (drawZ/10) + (2*drawZ+drawX)/10 * drawY/10;


    //计算图案的面积,存入数组中.
    float areaRa[1000];
    //初始化
    for(int i=0;i<1000;i++){
        areaRa[i] = 0;
    }
    centralDraw->getAreaRa(areaRa);

    //图案所占面积比可以拿到

    backGroundColorIndex=currentIndex34;
    //backGroundColor=allColor.myColor[4];
    //计算图案颜色所占比
    int rowNum = drawZ/10;
    int colNum = drawY/10;

    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            colorJZ[i][j] = 0;
        }
    }

    //centralDraw->setAutoColor(allColor,backGroundColorIndex);
    //数组存放图案编号     -------xiaotian
    int length = drawOk;
    int graphIndex[length];


    for(int i=0;i<length;i++){
        graphIndex[i] = (i+1);
    }


    //首先分配currentIndex31颜色。 占比30
    //31--1   32--2  33--3  34--4  颜色编号对应
    int cancelcurrentIndex31 = 0;
    int cancelcurrentIndex32 = 0;
    int cancelcurrentIndex33 = 0;

/*
    while(proportionB<=countProB){
        if(length == 0)
            break;
        int num = rand()%length;
        //将图案graphIndex[num]颜色置为currentIndex31
        allColor.index[graphIndex[num]] = currentIndex31;
        centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
        //生成颜色矩阵
        centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex31+1);
        //计算颜色比例
        float index31 = caucluateColor(currentIndex31+1);
        proportionB = index31/totalCount;
        if(proportionB > countProB){
            //应该撤销上一步操作。
            //1.将已涂色的图案颜色置为白色。
            //2.修改颜色矩阵。
            allColor.index[graphIndex[num]] = 30;
            centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
            //生成颜色矩阵
            centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex31+1);
            index31 = caucluateColor(currentIndex31+1);
            proportionB = index31/totalCount;
            cancelcurrentIndex31 = graphIndex[num];
            break;

        }else{
            //将num从graphIndex数组中移除
            for(int i=num;i<length;i++){
                graphIndex[i] = graphIndex[i+1];
            }
            length--;
        }
    }

    cout<<"第一块"<<endl;

    //首先分配currentIndex32颜色。 占比25
    //31--1   32--2  33--3  34--4  颜色编号对应
    while(proportionC<=countProC){
        if(length == 0)
            break;
        int cancelIndex = 0;
        int num = rand()%length;
        //将图案graphIndex[num]颜色置为currentIndex31
        allColor.index[graphIndex[num]] = currentIndex32;
        centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
        //生成颜色矩阵
        centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex32+1);
        //计算颜色比例
        float index32 = caucluateColor(currentIndex32+1);
        proportionC = index32/totalCount;
        if(proportionC > countProC){
            //应该撤销上一步操作。
            //1.将已涂色的图案颜色置为白色。
            //2.修改颜色矩阵。
            allColor.index[graphIndex[num]] = 30;
            centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
            //生成颜色矩阵
            centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex32+1);
            index32 = caucluateColor(currentIndex32+1);
            proportionC = index32/totalCount;
            //将移除的图案再放回到数组中去。
            cancelcurrentIndex32 = graphIndex[num];
            break;

        }else{
            //将num从graphIndex数组中移除
            //记录要移除的图案下标。

            for(int i=num;i<length;i++){
                graphIndex[i] = graphIndex[i+1];
            }
            length--;
        }
    }

    cout<<"第二块"<<endl;


    while(proportionD<=countProD){
        if(length == 0)
            break;
        int num = rand()%length;
        //将图案graphIndex[num]颜色置为currentIndex33
        allColor.index[graphIndex[num]] = currentIndex33;
        centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
        //生成颜色矩阵
        centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex33+1);
        //计算颜色比例
        float index33 = caucluateColor(currentIndex33+1);
        proportionD = index33/totalCount;
        if(proportionD > countProD){
            //应该撤销上一步操作。
            //1.将已涂色的图案颜色置为白色。
            //2.修改颜色矩阵。
            allColor.index[graphIndex[num]] = 30;
            centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[num]);
            //生成颜色矩阵
            centralDraw->getColorRation(colorJZ,graphIndex[num],currentIndex33+1);
            index33 = caucluateColor(currentIndex33+1);
            proportionD = index33/totalCount;
            cancelcurrentIndex33 = graphIndex[num];
            break;

        }else{
            //将num从graphIndex数组中移除

            for(int i=num;i<length;i++){
                graphIndex[i] = graphIndex[i+1];
            }
            length--;
        }
    }
*/
//    cout<<"第三块"<<endl;


    for(int i=0;i<length;i++){
        //cout<<graphIndex[i]<<' '<<endl;
        //按照顺序进行分配图案

        allColor.index[graphIndex[i]] = currentIndex31;
        centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
        //生成颜色矩阵
        centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex31+1);
        //计算颜色比例
        float index31 = caucluateColor(currentIndex31+1);
        proportionB = index31/totalCount;

        if(proportionB > countProB){
            //如果大于0.3,则分配给C。
            allColor.index[graphIndex[i]] = 30;
            centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
            //生成颜色矩阵
            centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex31+1);
            index31 = caucluateColor(currentIndex31+1);
            proportionB = index31/totalCount;

            //分配给C
            allColor.index[graphIndex[i]] = currentIndex32;
            centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
            //生成颜色矩阵
            centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex32+1);
            //计算颜色比例
            float index32 = caucluateColor(currentIndex32+1);
            proportionC = index32/totalCount;

            if(proportionC > countProC){
                //
                allColor.index[graphIndex[i]] = 30;
                centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
                //生成颜色矩阵
                centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex32+1);
                index32 = caucluateColor(currentIndex32+1);
                proportionC = index32/totalCount;

                //给D
                allColor.index[graphIndex[i]] = currentIndex33;
                centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
                //生成颜色矩阵
                centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex33+1);
                //计算颜色比例
                float index33 = caucluateColor(currentIndex33+1);
                proportionD = index33/totalCount;
                if(proportionD>countProD){
                    allColor.index[graphIndex[i]] = 30;
                    centralDraw->setAutoSingleColor(allColor,backGroundColorIndex,graphIndex[i]);
                    //生成颜色矩阵
                    centralDraw->getColorRation(colorJZ,graphIndex[i],currentIndex33+1);
                    index33 = caucluateColor(currentIndex33+1);
                    proportionD = index33/totalCount;
                }else{
                    for(int j=i;j<length;j++){
                        graphIndex[j] = graphIndex[j+1];
                    }
                    length--;
                }

            }else{
                for(int j=i;j<length;j++){
                    graphIndex[j] = graphIndex[j+1];
                }
                length--;
            }

        }else{
            for(int j=i;j<length;j++){
                graphIndex[j] = graphIndex[j+1];
            }
            length--;
        }

    }


    //            for(int i=0;i<length;i++){

    //                cout<<graphIndex[i]<<' '<<endl;

    //                 centralDraw->removePath(graphIndex[i]-1);
    //                 //颜色下标数组也需要迁移。
    //                 for(int k=graphIndex[i];k<maxSize;k++){
    //                     allColor.index[k] = allColor.index[k+1];
    //                 }
    //                int j=i+1;
    //                for(j;j<length;j++){
    //                    graphIndex[j] = graphIndex[j] - 1;
    //                }

    //            }


    for(int i=0;i<50;i++){
        for(int j=0;j<60;j++){
            cout<<colorJZ[i][j]<<' ';
        }
        cout<<endl;
    }




    centralDraw->setAutoColor(allColor,backGroundColorIndex);
    cout<<proportionB<<' '<<proportionC<<' '<<proportionD<<endl;


    //最后剩余的图案是不满足颜色填充的，需要移除，然后重新在中心点做内包的颜色填充。




    centralDraw->update();



    //centralDraw->removePath(1);




    //addBackGroundEdit();



}




//----------------------------------颜色分配 --------xiaotian
void MainWindow::autoColorF(){
    int tempSmallAll;

    //-----------xiaotian    这两个方法
    centralDraw->getAreaRatio(areaRatio);
    centralDraw->getPointStyle(bigDrawOk,bigDrawOkNum,smallDrawOk,smallDrawOkNum,tempSmallAll);

    caculateColorProportion();
    //3:3:2:2
    float proportionA,proportionB=0,proportionC=0,proportionD=0;
    int countA,countB,countC,countD;
    countA=0;countB=0;countC=0;countD=0;
    int A[1500],B[1500],C[1500],D[1500];
    proportionA=backGroundProportion;

    if(proportionA>30){
        for(int i=1;i<bigDrawOkNum+1;){

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;//qDebug("%d",i);
            }
            if(i>bigDrawOkNum)
                break;


        }

        for(int i=1;i<smallDrawOkNum+1;){
            //qDebug("%d",i);
            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }

            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;




            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;



            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;qDebug("%d",i);
                }
            }
            if(i>smallDrawOkNum)
                break;
        }

        //测试斑点分配
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex33;
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex31;
        }
        for(int t=1;t<countD+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[D[t]]=currentIndex32;
        }

        backGroundColorIndex=currentIndex34;
        backGroundColor=iconColor[backGroundColorIndex];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();


        //qDebug(">0.3 bai  fen  bi  shi:%f   %f   %f   %f",proportionA,proportionB,proportionC,proportionD);
    }
    else{
        //qDebug("aaaaaaaaaaaaaaaaaaa:%f",proportionA);
        for(int i=1;i<bigDrawOkNum+1;){
            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
                //qDebug("***********%d",i);
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;

            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<20){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionD<20){
                proportionD+=areaRatio[bigDrawOk[i]];
                D[++countD]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;
            qDebug("@@@@@@@@@@@@@@@@@@%d",i);
        }


        for(int i=1;i<smallDrawOkNum+1;){

            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionA<30){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<20){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionD<20){
                if(i<tempSmallAll+1){
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;

                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionD+=areaRatio[smallDrawOk[i]];
                    D[++countD]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
        }


        //测试斑点分配
        for(int t=1;t<countA+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[A[t]]=currentIndex34;
            //qDebug("A######%d",A[t]);
        }
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex33;
            //qDebug("B######%d",B[t]);
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex32;
            //qDebug("C######%d",C[t]);
        }
        for(int t=1;t<countD+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[D[t]]=currentIndex31;
            //qDebug("D######%d",D[t]);
        }

        for(int i=1;i<bigDrawOkNum+1;i++){
            qDebug("~~~~~~~~~~~~~~~~~%d",bigDrawOk[i]);
        }

        backGroundColorIndex=currentIndex34;
        backGroundColor=iconColor[backGroundColorIndex];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();
        //qDebug("<0.3 bai  fen  bi  shi:%f   %f   %f   %f",proportionA,proportionB,proportionC,proportionD);
    }

}


void MainWindow::autoColorS(){
    int tempSmallAll;
    centralDraw->getAreaRatio(areaRatio);
    centralDraw->getPointStyle(bigDrawOk,bigDrawOkNum,smallDrawOk,smallDrawOkNum,tempSmallAll);
    caculateColorProportion();



    //4:3:3
    float proportionA,proportionB=0,proportionC=0;
    int countA,countB,countC;
    countA=0;countB=0;countC=0;
    proportionA=backGroundProportion;
    int A[2000],B[2000],C[2000];

    if(proportionA>40){
        for(int i=1;i<bigDrawOkNum+1;){
            //qDebug("%d",i);
            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                //qDebug("+++B%d",bigDrawOk[i]);
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<30){
                proportionC+=areaRatio[bigDrawOk[i]];
                //qDebug("+++B%d",bigDrawOk[i]);
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;

        }

        for(int i=1;i<smallDrawOkNum+1;){
            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<30){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }

                proportionC+=areaRatio[smallDrawOk[i]];
                C[++countC]=smallDrawOk[i];
                i++;
            }
            if(i>smallDrawOkNum)
                break;
        }

        //测试斑点分配
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex21;
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex22;
        }

        backGroundColorIndex=currentIndex23;
        backGroundColor=iconColor[backGroundColorIndex+1];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();

        //qDebug(">0.3 bai  fen  bi  shi:%f   %f   %f",proportionA,proportionB,proportionC);
    }
    else{
        //qDebug("aaaaaaaaaaaaaaaaaaa:%f",proportionA);
        for(int i=1;i<bigDrawOkNum+1;){
            if(proportionB<30){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;


            if(proportionC<30){
                proportionC+=areaRatio[bigDrawOk[i]];
                C[++countC]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;

        }


        for(int i=1;i<smallDrawOkNum+1;){
            if(proportionA<40){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<30){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
            ////////////////////////////////////////////////////////////////////
            if(proportionA<40){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionA<40){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<30){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
            ////////////////////////////////////////////////////////
            if(proportionA<40){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionB<30){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionC<30){
                if(i<tempSmallAll+1){
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;

                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionC+=areaRatio[smallDrawOk[i]];
                    C[++countC]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


        }

        //测试斑点分配
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex21;
        }
        for(int t=1;t<countC+1;t++){
            //qDebug("CCCCCCC:%d",C[t]);
            allColor.index[C[t]]=currentIndex22;
        }
        for(int t=1;t<countA+1;t++){
            allColor.index[A[t]]=currentIndex23;
        }

        backGroundColorIndex=currentIndex23;
        backGroundColor=iconColor[currentIndex23+1];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
        //addBackGroundEdit();

        //qDebug("<0.3 bai  fen  bi  shi:%f   %f   %f",proportionA,proportionB,proportionC);
    }
}
void MainWindow::autoColorT(){
    //    drawOk=centralDraw->getDrawOk();
    //    for(int i=1;i<drawOk+1;i++){
    //        allColor.index[i]=currentIndex11;
    //    }
    //    backGroundColorIndex=currentIndex12;
    //    backGroundColor=iconColor[currentIndex12];
    //    centralDraw->setAutoColor(allColor,backGroundColorIndex);


    int tempSmallAll;
    centralDraw->getAreaRatio(areaRatio);
    centralDraw->getPointStyle(bigDrawOk,bigDrawOkNum,smallDrawOk,smallDrawOkNum,tempSmallAll);
    caculateColorProportion();



    //6:4
    float proportionA,proportionB=0;
    int countA,countB;
    countA=0;countB=0;
    proportionA=backGroundProportion;
    int A[2000],B[2000];

    if(proportionA>60){
        for(int i=1;i<bigDrawOkNum+1;i++){
            proportionB+=areaRatio[bigDrawOk[i]];
            B[++countB]=bigDrawOk[i];

        }

        for(int i=1;i<smallDrawOkNum+1;i++){
            proportionB+=areaRatio[smallDrawOk[i]];
            B[++countB]=smallDrawOk[i];
        }

        //测试斑点分配
        for(int t=1;t<countB+1;t++){
            //qDebug("BBBBBBBB:%d",B[t]);
            allColor.index[B[t]]=currentIndex21;
        }

        backGroundColorIndex=currentIndex23;
        backGroundColor=iconColor[backGroundColorIndex+1];
        centralDraw->setAutoColor(allColor,backGroundColorIndex);
    }
    else{
        //qDebug("aaaaaaaaaaaaaaaaaaa:%f",proportionA);
        //大斑点都分配给B
        for(int i=1;i<bigDrawOkNum+1;){
            if(proportionB<40){
                proportionB+=areaRatio[bigDrawOk[i]];
                B[++countB]=bigDrawOk[i];
                i++;
            }
            if(i>bigDrawOkNum)
                break;
        }

        //////////////////////////////////////////////////现在开始分配小斑点
        for(int i=1;i<smallDrawOkNum+1;){
            if(proportionA<60){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionB<40){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
            ////////////////////////////////////////////////////////////////////
            if(proportionA<60){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;


            if(proportionB<40){
                if(i<tempSmallAll+1){
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;

                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionB+=areaRatio[smallDrawOk[i]];
                    B[++countB]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;

            if(proportionA<60){
                if(i<tempSmallAll+1){
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;

                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
                else{
                    proportionA+=areaRatio[smallDrawOk[i]];
                    A[++countA]=smallDrawOk[i];
                    i++;
                }
            }
            if(i>smallDrawOkNum)
                break;
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    //测试斑点分配
    for(int t=1;t<countB+1;t++){
        //qDebug("BBBBBBBB:%d",B[t]);
        allColor.index[B[t]]=currentIndex11;
    }

    for(int t=1;t<countA+1;t++){
        allColor.index[A[t]]=currentIndex12;
    }

    backGroundColorIndex=currentIndex12;
    backGroundColor=iconColor[currentIndex12+1];
    centralDraw->setAutoColor(allColor,backGroundColorIndex);
    //addBackGroundEdit();

    //qDebug("<0.3 bai  fen  bi  shi:%f   %f   %f",proportionA,proportionB,proportionC);
}

void MainWindow::autoS(){
    //centralDraw->getSpotPoint();
    centralDraw->getDigitalSpotPoint();
}

//自动生成数码迷彩
void MainWindow::autoDigital(){
    //    if(fileName == ""){
    //       QMessageBox::about(NULL, "Warning", "请打开图片!!!!");
    //    }else{
    windowScale=centralDraw->getWindowScale();
    if(fabs(windowScale-1)<0.001){
        if(AutoCADFlag){
            //centralDraw->getCanvasPointS2(90,60);
            //autoColorFD();

            //centralDraw->getCanvasPointSTestByControl(100,100);
            centralDraw->getCanvasDigital();
            autoColorByControl();
            //不显示斑点边缘线
            //centralDraw->showSpotEdge(1);

        }
    }
    //    }
}



void MainWindow::autoDigitalTest(){
    windowScale=centralDraw->getWindowScale();
    if(fabs(windowScale-1)<0.001){
        if(AutoCADFlag){
            //centralDraw->getCanvasBigPointS();
            //centralDraw->getCanvasPointS(70,40);
            //centralDraw->getCanvasPointS(90,60);
            centralDraw->getCanvasPointNew();
            //-------------------------xiaotian
            //调两遍，斑点分布就会较为密集.
            //centralDraw->getCanvasPointSTest(100,100);
            autoColorF();
            //---------------xiaotian   测试颜色分配与图形生成
            //int totalgrahcount = centralDraw->getCanvasPointSTestByControl(100,100);

            //autoColorF();
            //autoColorByControl();
            //centralDraw->getDigitalCanvas();
        }
    }
}

void MainWindow::autoC(){
    windowScale=centralDraw->getWindowScale();
    if(fabs(windowScale-1)<0.001){
        if(AutoCADFlag){
            /////////////////////////////////////////
            if(colorChoose==1){//6:4
                if(getSize==1){
                    //autoColorT();

                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前不要做任何操作，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }

                    //enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }
                else if(getSize==0){
                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前不要做任何操作，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }
                    //autoColorT();
                    //addBackGroundEdit();
                    //enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }
            }
            else if(colorChoose==2){//4:3:3
                if(getSize==1){
                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前可以切换到其他窗口，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    //如果选择是，则继续生成斑点
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }
                    //                centralDraw->getCanvasBigPointS();
                    //                centralDraw->getCanvasPointS(100,100);
                    //                autoColorS();
                    //centralDraw->getCanvasPointNew();
                    //斑点自动生成线程
                    //autoColorS();
                    //enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }else if(getSize==0){
                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前不要做任何操作，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }
                    //centralDraw->getCanvasPointNew();
                    //autoColorS();
                    //                    centralDraw->getCanvasPointS(90,80);
                    //                    autoColorS();
                    //                    enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }
            }
            else if(colorChoose==3){//2:2:3:3
                //qDebug("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%d",getSize);
                if(getSize==1){
                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前不要做任何操作，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }
                    //autoColorF();
                    //enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }else if(getSize==0){
                    //mThread=new myThread(this);
                    QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", tr("   即将生成斑点，屏幕布满斑点之前不要做任何操作，此过程可能需要一分多钟！        "), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(rb == QMessageBox::Yes)
                    {
                        cThread->start();
                    }
                    //autoColorF();
                    //enumManagerL->setValue(BGProperty,backGroundColorIndex);
                }
            }
            else{
                QMessageBox msgBox(this);
                msgBox.setWindowTitle(tr("提示"));
                msgBox.setText(tr("请右键选择颜色比!        "));
                msgBox.setMinimumSize(200,100);
                msgBox.exec();
            }

            ///////////////////////////////////////////////////////
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("请在五面画布下用此功能！        "));
            msgBox.setMinimumSize(200,100);
            //msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
            msgBox.exec();

            //            QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Show Qt", "Do you want to show Qt dialog?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            //            if(rb == QMessageBox::Yes)
            //            {
            //                    QMessageBox::aboutQt(NULL, "About Qt");
            //            }

        }
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前缩放比例必须为1        "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
    }
}

void MainWindow::addBackGroundEdit(){

    if(preEnumManagerL){
        delete preEnumManagerL;
    }
    if(preIntManagerL){
        delete preIntManagerL;
    }

    if(preSplitterRightL){
        delete preSplitterRightL;
    }
    if(preEnumNamesL){
        delete preEnumNamesL;
    }
    //    if(preBGProperty){
    //        delete preBGProperty;
    //    }

    splitterMainL=new QSplitter(&leftDock);
    preSplitterMainL=splitterMainL;

    leftDock.setWidget(splitterMainL);
    splitterRightL=new QSplitter(Qt::Vertical,splitterMainL);
    preSplitterRightL=splitterRightL;

    intManagerL = new QtIntPropertyManager(splitterRightL);
    preIntManagerL=intManagerL;

    //加颜色下拉框
    enumNamesL=new(QStringList);
    preEnumNamesL=enumNamesL;
    groupManagerL = new QtGroupPropertyManager(splitterRightL);///////////////////////////////
    preGroupManagerL=groupManagerL;

    spinBoxFactoryL = new QtSpinBoxFactory;
    preSpinBoxFactoryL=spinBoxFactoryL;

    enumManagerL = new QtEnumPropertyManager;
    preEnumManagerL=enumManagerL;

    comboBoxFactoryL = new QtEnumEditorFactory;
    preComboBoxFactoryL=comboBoxFactoryL;

    BGProperty = enumManagerL->addProperty(tr("背景颜色"));
    preBGProperty=BGProperty;

    (*enumNamesL) << tr("深绿1") << tr("深绿2") << tr("中绿1") << tr("中绿2")<< tr("翠绿1")<< tr("翠绿2") << tr("黄绿1") << tr("黄绿2");
    (*enumNamesL) << tr("褐土1") << tr("褐土2") << tr("褐土3") << tr("褐土4")<< tr("褐土5")<< tr("褐土6") << tr("褐土7") << tr("红土1");
    (*enumNamesL) << tr("红土2") << tr("黄土1") << tr("黄土2") << tr("黄土3")<< tr("黄土4")<< tr("黄土5") << tr("沙土1") << tr("沙土2");
    (*enumNamesL) << tr("沙土3") << tr("沙土4") << tr("沙土5") << tr("沙土6")<< tr("黑色")<< /*tr(mm);*/tr("白色");
    for(int i=1;i<addColorNum+1;i++){
        //        QString temp("你好");
        //        QByteArray ba = temp.toLatin1();/*allColor.colorName[i].toLatin1();*/

        //        //qDebug()<<allColor.colorName[i];
        //        char *mm = ba.data();
        (*enumNamesL)<<allColor.colorName[i];
    }


    enumManagerL->setEnumNames(BGProperty, *enumNamesL);

    QMap<int,QIcon> enumIcons;
    QPixmap pix[31+addColorNum];
    QPixmap tempPix(200,100);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        enumIcons[i-1] = QIcon(pix[i]);
    }

    enumManagerL->setEnumIcons(BGProperty, enumIcons);

    enumManagerL->setValue(BGProperty,backGroundColorIndex);
    task1L = groupManagerL->addProperty(tr("画布属性"));
    task1L->addSubProperty(BGProperty);


    //加属性长宽高:
    //intManagerL = new QtIntPropertyManager(splitterRight);
    //preIntManagerL=intManagerL;
    BGPropertySize = intManagerL->addProperty(tr("背景尺寸"));
    //spinBoxFactoryL = new QtSpinBoxFactory;

    BGPropertyX= intManagerL->addProperty(tr("长(cm)"));
    intManagerL->setRange(BGPropertyX, 0, 5000);
    BGPropertyY= intManagerL->addProperty(tr("宽(cm)"));
    intManagerL->setRange(BGPropertyY, 0, 800);
    BGPropertyZ= intManagerL->addProperty(tr("高(cm)"));
    intManagerL->setRange(BGPropertyZ, 0, 800);

    BGPropertySize->addSubProperty(BGPropertyX);
    BGPropertySize->addSubProperty(BGPropertyY);
    BGPropertySize->addSubProperty(BGPropertyZ);


    intManagerL->setValue(BGPropertyX,drawX);
    intManagerL->setValue(BGPropertyY,drawY);
    intManagerL->setValue(BGPropertyZ,drawZ);
    task1L->addSubProperty(BGPropertySize);

    //加面积统计
    task2L = groupManagerL->addProperty(tr("颜色统计"));
    //    for(int i=1;i<31;i++){
    ////        if(preTempProportion[i])
    ////            delete preTempProportion[i];
    //    }
    //为了让面积比和为100
    int tempAll=0;
    for(int i=1;i<31+addColorNum;i++){
        tempAll+=colorProportion[i];
    }
    int i=1;
    while(fabs(colorProportion[i])<2){
        i++;
    }
    colorProportion[i]+=100-tempAll;

    for(int i=1;i<31+addColorNum;i++){
        if(colorProportion[i]!=0){
            //            case 31:tempProportion[i]= intManagerL->addProperty(tr("新颜色一"));preTempProportion[i]=tempProportion[i];break;
            //            case 32:tempProportion[i]= intManagerL->addProperty(tr("新颜色二"));preTempProportion[i]=tempProportion[i];break;
            //            case 33:tempProportion[i]= intManagerL->addProperty(tr("新颜色三"));preTempProportion[i]=tempProportion[i];break;
            //            case 34:tempProportion[i]= intManagerL->addProperty(tr("新颜色四"));preTempProportion[i]=tempProportion[i];break;
            if(i>30){
                tempProportion[i]= intManagerL->addProperty(allColor.colorName[i-30]);
                //qDebug()<<allColor.colorName[i];
                preTempProportion[i]=tempProportion[i];
            }
            switch(i){
            case 1:tempProportion[i]= intManagerL->addProperty(tr("深绿1"));preTempProportion[i]=tempProportion[i];break;
            case 2:tempProportion[i]= intManagerL->addProperty(tr("深绿2"));preTempProportion[i]=tempProportion[i];break;
            case 3:tempProportion[i]= intManagerL->addProperty(tr("中绿1"));preTempProportion[i]=tempProportion[i];break;
            case 4:tempProportion[i]= intManagerL->addProperty(tr("中绿2"));preTempProportion[i]=tempProportion[i];break;
            case 5:tempProportion[i]= intManagerL->addProperty(tr("翠绿1"));preTempProportion[i]=tempProportion[i];break;
            case 6:tempProportion[i]= intManagerL->addProperty(tr("翠绿2"));preTempProportion[i]=tempProportion[i];break;
            case 7:tempProportion[i]= intManagerL->addProperty(tr("黄绿1"));preTempProportion[i]=tempProportion[i];break;
            case 8:tempProportion[i]= intManagerL->addProperty(tr("黄绿2"));preTempProportion[i]=tempProportion[i];break;
            case 9:tempProportion[i]= intManagerL->addProperty(tr("褐土1"));preTempProportion[i]=tempProportion[i];break;
            case 10:tempProportion[i]= intManagerL->addProperty(tr("褐土2"));preTempProportion[i]=tempProportion[i];break;
            case 11:tempProportion[i]= intManagerL->addProperty(tr("褐土3"));preTempProportion[i]=tempProportion[i];break;
            case 12:tempProportion[i]= intManagerL->addProperty(tr("褐土4"));preTempProportion[i]=tempProportion[i];break;
            case 13:tempProportion[i]= intManagerL->addProperty(tr("褐土5"));preTempProportion[i]=tempProportion[i];break;
            case 14:tempProportion[i]= intManagerL->addProperty(tr("褐土6"));preTempProportion[i]=tempProportion[i];break;
            case 15:tempProportion[i]= intManagerL->addProperty(tr("褐土7"));preTempProportion[i]=tempProportion[i];break;
            case 16:tempProportion[i]= intManagerL->addProperty(tr("红土1"));preTempProportion[i]=tempProportion[i];break;
            case 17:tempProportion[i]= intManagerL->addProperty(tr("红土2"));preTempProportion[i]=tempProportion[i];break;
            case 18:tempProportion[i]= intManagerL->addProperty(tr("黄土1"));preTempProportion[i]=tempProportion[i];break;
            case 19:tempProportion[i]= intManagerL->addProperty(tr("黄土2"));preTempProportion[i]=tempProportion[i];break;
            case 20:tempProportion[i]= intManagerL->addProperty(tr("黄土3"));preTempProportion[i]=tempProportion[i];break;
            case 21:tempProportion[i]= intManagerL->addProperty(tr("黄土4"));preTempProportion[i]=tempProportion[i];break;
            case 22:tempProportion[i]= intManagerL->addProperty(tr("黄土5"));preTempProportion[i]=tempProportion[i];break;
            case 23:tempProportion[i]= intManagerL->addProperty(tr("沙土1"));preTempProportion[i]=tempProportion[i];break;
            case 24:tempProportion[i]= intManagerL->addProperty(tr("沙土2"));preTempProportion[i]=tempProportion[i];break;
            case 25:tempProportion[i]= intManagerL->addProperty(tr("沙土3"));preTempProportion[i]=tempProportion[i];break;
            case 26:tempProportion[i]= intManagerL->addProperty(tr("沙土4"));preTempProportion[i]=tempProportion[i];break;
            case 27:tempProportion[i]= intManagerL->addProperty(tr("沙土5"));preTempProportion[i]=tempProportion[i];break;
            case 28:tempProportion[i]= intManagerL->addProperty(tr("沙土6"));preTempProportion[i]=tempProportion[i];break;
            case 29:tempProportion[i]= intManagerL->addProperty(tr("黑"));preTempProportion[i]=tempProportion[i];break;
            case 30:tempProportion[i]= intManagerL->addProperty(tr("白"));preTempProportion[i]=tempProportion[i];break;
            default: break;
            }
            intManagerL->setValue(tempProportion[i],colorProportion[i]);
            //qDebug("%f",colorProportion[i]);
            task2L->addSubProperty(tempProportion[i]);
        }
        //        QtDoublePropertyManager *intl=new QtDoublePropertyManager(splitterRightL);
        //        intManagerL = new QtIntPropertyManager(splitterRightL);
        //        QtProperty *tempL=intl->addProperty(tr("测试"));
        //        intl->setValue(tempL,22.222);
        //        task2L->addSubProperty(tempL);

    }



    editorL = new QtTreePropertyBrowser(splitterRightL);
    preEditorL=editorL;
    editorL->setFactoryForManager(enumManagerL,comboBoxFactoryL);
    editorL->setFactoryForManager(intManagerL, spinBoxFactoryL);
    editorL->addProperty(task1L);
    editorL->addProperty(task2L);
    editorL->show();


    leftDock.setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,&leftDock);
    connect(enumManagerL, SIGNAL(propertyChanged(QtProperty *)),this, SLOT(editBackGround()));
    connect(intManagerL, SIGNAL(valueChanged(QtProperty *,int)),
            this, SLOT(editBackGround()));

}

void MainWindow::addRightQDockWidget(){
    //    rightDock=new QDockWidget(QObject::tr("属性框"),this);
    //    splitterMain=new QSplitter(rightDock);
    //    splitterRight=new QSplitter(Qt::Vertical,splitterMain);
    //    splitterRight->setMinimumWidth(200);
    //    tempListWidget=new QListWidget(splitterRight);

    //    rightDock->setWidget(splitterMain);
    //    rightDock->setWidget(splitterRight);
    //    tempListWidget->setMinimumWidth(200);
    //    rightDock->setWidget(tempListWidget);
    //    intManager = new QtIntPropertyManager(splitterRight);
    //    rightDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    //    addDockWidget(Qt::RightDockWidgetArea,rightDock);
}
void MainWindow::addMyToolBar(){

    /*QToolBar * */mainToolBar = addToolBar(tr("2222"));
    if(preMainToolBar){
        delete preMainToolBar;
    }
    preMainToolBar=mainToolBar;
    ui->mainToolBar->setMovable(false);//加入另一个工具栏

    //    QToolBar * mainToolBar1 = addToolBar(tr("2222"));
    //    ui->mainToolBar1->setMovable(false);


    toolBtn = new QToolButton(this);
    toolBtn->setToolTip(tr("画笔"));
    toolBtn->setCheckable(true);
    toolBtn->setIcon(QPixmap("icon/pen.png"));
    toolBtn->setMinimumHeight(35);
    ui->mainToolBar->addWidget(toolBtn);
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(setDrawFlag()));
    //mainToolBar1->addWidget(toolBtn);



    deleteAll = new QToolButton(this);
    deleteAll->setToolTip(tr("清空"));
    deleteAll->setIcon(QPixmap("icon/xiangpi.png"));
    //toolBtn->setText(tr("颜色"));
    deleteAll->setMinimumHeight(35);
    ui->mainToolBar->addWidget(deleteAll);
    connect(deleteAll,SIGNAL(clicked()),this,SLOT(clearAll()));

    backWard = new QToolButton(this);
    backWard->setToolTip(tr("回退"));
    backWard->setIcon(QPixmap("icon/backWard.png"));
    //toolBtn->setText(tr("颜色"));
    backWard->setMinimumHeight(35);
    /*ui->*/mainToolBar->addWidget(backWard);

    forWard = new QToolButton(this);
    forWard->setToolTip(tr("前进"));
    forWard->setIcon(QPixmap("icon/forWard.png"));
    //toolBtn->setText(tr("颜色"));
    forWard->setMinimumHeight(35);
    /*ui->*/mainToolBar->addWidget(forWard);


    QLabel *spotLabel=new QLabel(this);
    spotLabel->setText(tr("前景色："));
    spotLabel->setMinimumHeight(25);
    spotLabel->setMinimumWidth(35);
    /*ui->*/mainToolBar->addWidget(spotLabel);



    spotComboBox=new QComboBox(this);
    //connect(spotComboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(leftDockWidgetChanged()));
    spotComboBox->addItem(tr(" 深绿1  DG0730"));
    spotComboBox->addItem(tr(" 深绿2  DG0730"));
    spotComboBox->addItem(tr(" 中绿1  DG0730"));
    spotComboBox->addItem(tr(" 中绿2  DG0730"));
    spotComboBox->addItem(tr(" 翠绿1  DG0730"));
    spotComboBox->addItem(tr(" 翠绿2  DG0730"));
    spotComboBox->addItem(tr(" 黄绿1  YG1247"));
    spotComboBox->addItem(tr(" 黄绿2  YG1560"));
    spotComboBox->addItem(tr(" 褐土1  BE0811"));
    spotComboBox->addItem(tr(" 褐土2  BE0922"));
    spotComboBox->addItem(tr(" 褐土3  BE1130"));
    spotComboBox->addItem(tr(" 褐土4  BE1225"));
    spotComboBox->addItem(tr(" 褐土5  BE1230"));
    spotComboBox->addItem(tr(" 褐土6  BE1732"));
    spotComboBox->addItem(tr(" 褐土7  BE1824"));
    spotComboBox->addItem(tr(" 红土1  RE1125"));
    spotComboBox->addItem(tr(" 红土2  RE1328"));
    spotComboBox->addItem(tr(" 黄土1  YE1624"));
    spotComboBox->addItem(tr(" 黄土2  YE2344"));
    spotComboBox->addItem(tr(" 黄土3  YE2738"));
    spotComboBox->addItem(tr(" 黄土4  YE3249"));
    spotComboBox->addItem(tr(" 黄土5  YE3559"));
    spotComboBox->addItem(tr(" 沙土1  SE2139"));
    spotComboBox->addItem(tr(" 沙土2  SE2232"));
    spotComboBox->addItem(tr(" 沙土3  SE2425"));
    spotComboBox->addItem(tr(" 沙土4  SE2635"));
    spotComboBox->addItem(tr(" 沙土5  SE3340"));
    spotComboBox->addItem(tr(" 沙土6  SE3948"));
    spotComboBox->addItem(tr(" 黑色   BN0606"));
    spotComboBox->addItem(tr(" 白色   WN8384"));
    //QComboBox *spotComboBox;
    //spotComboBox->removeItem(1);


    for(int i=1;i<addColorNum+1;i++){
        spotComboBox->addItem(allColor.colorName[i]);
        //qDebug()<<allColor.colorName[i];
        //(*enumNamesL)<<allColor.colorName[i];
    }

    //spotComboBox->setMaximumHeight(66);
    //    QPixmap pix(800,600);
    //    QPainter p(&pix);

    QPixmap pix[31+addColorNum];
    QPixmap tempPix(100,100);
    //QPixmap *pix=new QPixmap(600,600);
    spotComboBox->setFixedHeight(22);
    spotComboBox->setFixedWidth(200);
    //    spotComboBox->setItemIcon(0,QIcon("0.jpg"));
    //    spotComboBox->setItemIcon(1,QIcon("1.jpg"));
    //    spotComboBox->setItemIcon(2,QIcon("2.jpg"));
    //    spotComboBox->setItemIcon(3,QIcon("3.jpg"));
    //    spotComboBox->setItemIcon(4,QIcon("4.jpg"));
    //    spotComboBox->setItemIcon(5,QIcon("5.jpg"));
    //    spotComboBox->setItemIcon(6,QIcon("6.jpg"));
    //    spotComboBox->setItemIcon(7,QIcon("7.jpg"));

    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        //qDebug11("%d",i);
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBox->setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBox->setIconSize(QSize(30,50));//(165,18));
    spotComboBox->setCurrentIndex(allColor.index[spotSelectedNum]);
    //spotComboBox->setIconSize(a);
    //spotComboBox->addItem(tr("2  DG0730"));
    //spotComboBox->setCurrentIndex(0);
    //spotComboBox->addItems(tr("aaaaa"));
    //spotComboBox->setMinimumHeight(20);
    //spotComboBox->setMinimumWidth(150);
    /*ui->*/mainToolBar->addWidget(spotComboBox);
    connect(spotComboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(comboBoxSpotChanged()));


    QLabel *mh=new QLabel(this);
    mh->setText(tr("  "));
    mh->setMinimumHeight(25);
    mh->setMinimumWidth(35);
    /*ui->*/mainToolBar->addWidget(mh);



    QLabel *backgroundLabel=new QLabel(this);
    backgroundLabel->setText(tr("背景色："));
    backgroundLabel->setMinimumHeight(25);
    backgroundLabel->setMinimumWidth(75);
    /*ui->*/mainToolBar->addWidget(backgroundLabel);


    backgroundComboBox=new QComboBox(this);

    backgroundComboBox->addItem(tr(" 深绿1  DG0730"));
    backgroundComboBox->addItem(tr(" 深绿2  DG0730"));
    backgroundComboBox->addItem(tr(" 中绿1  DG0730"));
    backgroundComboBox->addItem(tr(" 中绿2  DG0730"));
    backgroundComboBox->addItem(tr(" 翠绿1  DG0730"));
    backgroundComboBox->addItem(tr(" 翠绿2  DG0730"));
    backgroundComboBox->addItem(tr(" 黄绿1  YG1247"));
    backgroundComboBox->addItem(tr(" 黄绿2  YG1560"));
    backgroundComboBox->addItem(tr(" 褐土1  BE0811"));
    backgroundComboBox->addItem(tr(" 褐土2  BE0922"));
    backgroundComboBox->addItem(tr(" 褐土3  BE1130"));
    backgroundComboBox->addItem(tr(" 褐土4  BE1225"));
    backgroundComboBox->addItem(tr(" 褐土5  BE1230"));
    backgroundComboBox->addItem(tr(" 褐土6  BE1732"));
    backgroundComboBox->addItem(tr(" 褐土7  BE1824"));
    backgroundComboBox->addItem(tr(" 红土1  RE1125"));
    backgroundComboBox->addItem(tr(" 红土2  RE1328"));
    backgroundComboBox->addItem(tr(" 黄土1  YE1624"));
    backgroundComboBox->addItem(tr(" 黄土2  YE2344"));
    backgroundComboBox->addItem(tr(" 黄土3  YE2738"));
    backgroundComboBox->addItem(tr(" 黄土4  YE3249"));
    backgroundComboBox->addItem(tr(" 黄土5  YE3559"));
    backgroundComboBox->addItem(tr(" 沙土1  SE2139"));
    backgroundComboBox->addItem(tr(" 沙土2  SE2232"));
    backgroundComboBox->addItem(tr(" 沙土3  SE2425"));
    backgroundComboBox->addItem(tr(" 沙土4  SE2635"));
    backgroundComboBox->addItem(tr(" 沙土5  SE3340"));
    backgroundComboBox->addItem(tr(" 沙土6  SE3948"));
    backgroundComboBox->addItem(tr(" 黑色   BN0606"));
    backgroundComboBox->addItem(tr(" 白色   WN8384"));
    //backgroundComboBox->addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        backgroundComboBox->addItem(allColor.colorName[i]);
        qDebug()<<allColor.colorName[i];
        //(*enumNamesL)<<allColor.colorName[i];
    }




    backgroundComboBox->setFixedHeight(22);
    backgroundComboBox->setFixedWidth(200);
    //    backgroundComboBox->setItemIcon(0,QIcon("0.jpg"));
    //    backgroundComboBox->setItemIcon(1,QIcon("1.jpg"));
    //    backgroundComboBox->setItemIcon(2,QIcon("2.jpg"));
    //    backgroundComboBox->setItemIcon(3,QIcon("3.jpg"));
    //    backgroundComboBox->setItemIcon(4,QIcon("4.jpg"));
    //    backgroundComboBox->setItemIcon(5,QIcon("5.jpg"));
    //    backgroundComboBox->setItemIcon(6,QIcon("6.jpg"));
    //    backgroundComboBox->setItemIcon(7,QIcon("7.jpg"));
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        //qDebug1("%d",i);
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        backgroundComboBox->setItemIcon(i-1,QIcon(pix[i]));
    }
    backgroundComboBox->setIconSize(QSize(30,50));
    backgroundComboBox->setCurrentIndex(backGroundColorIndex);

    //connect(backgroundComboBox, SIGNAL(activated(int)),this, SLOT(comboBoxBackGroundChanged()));
    connect(backgroundComboBox, SIGNAL(currentIndexChanged(int)),this, SLOT(comboBoxBackGroundChanged()));

    //backgroundComboBox->setIconSize(QSize(60,50));
    /*ui->*/mainToolBar->addWidget(backgroundComboBox);

    saveProject = new QToolButton(this);//spotMapping->setChecked();
    saveProject->setToolTip(tr("保存工程"));
    saveProject->setIcon(QPixmap("icon/saveProject.png"));
    saveProject->setMinimumHeight(35);
    ui->mainToolBar->addWidget(saveProject);
    connect(saveProject,SIGNAL(clicked()),this,SLOT(saveCanvasF()));

    readProject = new QToolButton(this);//spotMapping->setChecked();
    readProject->setToolTip(tr("打开已保存工程"));
    readProject->setIcon(QPixmap("icon/readProject.png"));
    readProject->setMinimumHeight(35);
    ui->mainToolBar->addWidget(readProject);
    connect(readProject,SIGNAL(clicked()),this,SLOT(readCanvasF()));

    spotMoveB = new QToolButton(this);
    spotMoveB->setToolTip(tr("移动"));
    spotMoveB->setIcon(QPixmap("icon/Move.png"));
    //toolBtn->setText(tr("颜色"));
    spotMoveB->setMinimumHeight(35);
    ui->mainToolBar->addWidget(spotMoveB);
    connect(spotMoveB,SIGNAL(clicked()),this,SLOT(setSpotMoveFlag()));



    spotRotation = new QToolButton(this);
    spotRotation->setToolTip(tr("旋转"));
    spotRotation->setIcon(QPixmap("icon/Rotate.png"));
    //toolBtn->setText(tr("颜色"));
    spotRotation->setMinimumHeight(35);
    ui->mainToolBar->addWidget(spotRotation);
    connect(spotRotation,SIGNAL(clicked()),this,SLOT(setRoationFlag()));


    spotZoom = new QToolButton(this);
    spotZoom->setToolTip(tr("缩放"));
    spotZoom->setIcon(QPixmap("icon/big.png"));
    //toolBtn->setText(tr("颜色"));
    spotZoom->setMinimumHeight(35);
    ui->mainToolBar->addWidget(spotZoom);
    connect(spotZoom,SIGNAL(clicked()),this,SLOT(setStretchFlag()));


    //曲率半径
    //toolBtnR = new QToolButton(this);
    toolBtnR = new QToolButton(this);
    toolBtnR->setToolTip(tr("检测曲率半径"));
    toolBtnR->setCheckable(true);
    toolBtnR->setIcon(QPixmap("icon/check.png"));
    toolBtnR->setMinimumHeight(35);
    ui->mainToolBar->addWidget(toolBtnR);
    connect(toolBtnR,SIGNAL(clicked()),this,SLOT(setRadiusFlag()));

    autoSpot = new QToolButton(this);//spotMapping->setChecked();
    autoSpot->setToolTip(tr("自动生成一个斑点"));
    autoSpot->setIcon(QPixmap("icon/autoS.png"));
    //toolBtn->setText(tr("颜色"));
    autoSpot->setMinimumHeight(35);
    ui->mainToolBar->addWidget(autoSpot);
    connect(autoSpot,SIGNAL(clicked()),this,SLOT(autoS()));

    //自动生成大斑点
    //    autoSpotBig = new QToolButton(this);//spotMapping->setChecked();
    //    autoSpotBig->setToolTip(tr("自动生成一个大斑点"));
    //    autoSpotBig->setIcon(QPixmap("icon/bigSpot.png"));
    //    //toolBtn->setText(tr("颜色"));
    //    autoSpotBig->setMinimumHeight(35);
    //    /*ui->*/mainToolBar->addWidget(autoSpotBig);

    autoCanvas = new QToolButton(this);//spotMapping->setChecked();
    autoCanvas->setToolTip(tr("自动生成一画布斑点"));
    autoCanvas->setIcon(QPixmap("icon/autoC.png"));
    //toolBtn->setText(tr("颜色"));
    autoCanvas->setMinimumHeight(35);
    ui->mainToolBar->addWidget(autoCanvas);
    connect(autoCanvas,SIGNAL(clicked()),this,SLOT(autoC()));
    //connect(autoCanvas,SIGNAL(clicked()),this,SLOT(autoDigitalTest()));

    //生成数码迷彩
    autoCanvas = new QToolButton(this);//spotMapping->setChecked();
    autoCanvas->setToolTip(tr("自动生成数码迷彩"));
    autoCanvas->setIcon(QPixmap("icon/autoC.png"));
    //toolBtn->setText(tr("颜色"));
    autoCanvas->setMinimumHeight(35);
    ui->mainToolBar->addWidget(autoCanvas);
    connect(autoCanvas,SIGNAL(clicked()),this,SLOT(autoDigital()));









    spotMapping = new QToolButton(this);//spotMapping->setChecked();
    spotMapping->setToolTip(tr("立体贴图"));
    spotMapping->setIcon(QPixmap("icon/Paint.png"));
    //toolBtn->setText(tr("颜色"));
    spotMapping->setMinimumHeight(35);
    ui->mainToolBar->addWidget(spotMapping);
    connect(spotMapping,SIGNAL(clicked()),this,SLOT(mapping()));




    //    AutoCAD = new QToolButton(this);//spotMapping->setChecked();
    //    AutoCAD->setToolTip(tr("生成AutoCAD图纸"));
    //    AutoCAD->setIcon(QPixmap("icon/autoSpot.png"));
    //    //toolBtn->setText(tr("颜色"));
    //    AutoCAD->setMinimumHeight(45);
    //    ui->mainToolBar->addWidget(AutoCAD);


    fiveOpen=new QToolButton(this);
    fiveOpen->setToolTip(tr("五视图展示"));
    fiveOpen->setIcon(QPixmap("icon/five.png"));
    fiveOpen->setMinimumHeight(35);
    ui->mainToolBar->addWidget(fiveOpen);
    connect(fiveOpen,SIGNAL(clicked()),this,SLOT(fiveOpenS()));


    AutoCADL = new QToolButton(this);//spotMapping->setChecked();
    AutoCADL->setToolTip(tr("获取左视图斑点信息"));
    AutoCADL->setIcon(QPixmap("icon/l.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADL->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADL);
    connect(AutoCADL,SIGNAL(clicked()),this,SLOT(copyAutoCADL()));

    AutoCADR = new QToolButton(this);//spotMapping->setChecked();
    AutoCADR->setToolTip(tr("获取右视图斑点信息"));
    AutoCADR->setIcon(QPixmap("icon/r.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADR->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADR);
    connect(AutoCADR,SIGNAL(clicked()),this,SLOT(copyAutoCADR()));

    AutoCADM = new QToolButton(this);//spotMapping->setChecked();
    AutoCADM->setToolTip(tr("获取中间视图斑点信息"));
    AutoCADM->setIcon(QPixmap("icon/m.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADM->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADM);
    connect(AutoCADM,SIGNAL(clicked()),this,SLOT(copyAutoCADM()));

    AutoCADU = new QToolButton(this);//spotMapping->setChecked();
    AutoCADU->setToolTip(tr("获取前视图斑点信息"));
    AutoCADU->setIcon(QPixmap("icon/u.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADU->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADU);
    connect(AutoCADU,SIGNAL(clicked()),this,SLOT(copyAutoCADU()));

    AutoCADD = new QToolButton(this);//spotMapping->setChecked();
    AutoCADD->setToolTip(tr("获取后视图斑点信息"));
    AutoCADD->setIcon(QPixmap("icon/d.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADD->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADD);
    connect(AutoCADD,SIGNAL(clicked()),this,SLOT(copyAutoCADD()));


    //加个全部的
    AutoCADA = new QToolButton(this);//spotMapping->setChecked();
    AutoCADA->setToolTip(tr("获取全部视图斑点信息"));
    AutoCADA->setIcon(QPixmap("icon/all.png"));
    //toolBtn->setText(tr("颜色"));
    AutoCADA->setMinimumHeight(35);
    ui->mainToolBar->addWidget(AutoCADA);
    connect(AutoCADA,SIGNAL(clicked()),this,SLOT(copyAutoCADA()));

    //添加一种颜色
    addOneColor = new QToolButton(this);//spotMapping->setChecked();
    addOneColor->setToolTip(tr("添加一种颜色"));
    addOneColor->setIcon(QPixmap("icon/color.png"));
    //toolBtn->setText(tr("颜色"));
    addOneColor->setMinimumHeight(35);
    ui->mainToolBar->addWidget(addOneColor);
    connect(addOneColor,SIGNAL(clicked()),this,SLOT(showACDialog()));

    //删除一种颜色
    deleteOneColor = new QToolButton(this);//spotMapping->setChecked();
    deleteOneColor->setToolTip(tr("删除一种颜色"));
    deleteOneColor->setIcon(QPixmap("icon/deleteOne.png"));
    //toolBtn->setText(tr("颜色"));
    deleteOneColor->setMinimumHeight(35);
    ui->mainToolBar->addWidget(deleteOneColor);
    connect(deleteOneColor,SIGNAL(clicked()),this,SLOT(showDCDialog()));


    //    //clearOneSpot现在当做随机一画布大斑点用
    //    clearOneSpot = new QToolButton(this);//spotMapping->setChecked();
    //    clearOneSpot->setToolTip(tr("删除一个斑点"));
    //    clearOneSpot->setIcon(QPixmap("icon/deleteOne.png"));
    //    //toolBtn->setText(tr("颜色"));
    //    clearOneSpot->setMinimumHeight(45);
    //    ui->mainToolBar->addWidget(clearOneSpot);

    setOPoint = new QToolButton(this);
    setOPoint->setToolTip(tr("显示关键点"));
    setOPoint->setCheckable(true);
    setOPoint->setIcon(QPixmap("icon/showKeyPoint.png"));
    setOPoint->setMinimumHeight(35);
    /*ui->*/mainToolBar->addWidget(setOPoint);
    connect(setOPoint,SIGNAL(clicked()),this,SLOT(setOPointFlag()));
    connect(backWard,SIGNAL(clicked()),this,SLOT(backWardF()));
    connect(forWard,SIGNAL(clicked()),this,SLOT(forWardF()));
}

void MainWindow::addSpotEdit(){
    if(preEnumManager){
        delete preEnumManager;
    }
    if(preIntManager){
        delete preIntManager;
    }
    if(preSplitterRight){
        delete preSplitterRight;
    }
    splitterMain=new QSplitter(&rightDock);
    rightDock.setWidget(splitterMain);
    splitterRight=new QSplitter(Qt::Vertical,splitterMain);
    preSplitterRight=splitterRight;

    intManager = new QtIntPropertyManager(splitterRight);
    preIntManager=intManager;
    enumNames=new(QStringList);

    intManager->setRange(priority10, 0, 500);

    priority11 = intManager->addProperty(tr("斑点个数"));



    priority13 = intManager->addProperty(tr("斑点线宽"));
    priority15 = intManager->addProperty(tr("设置分辨率"));
    priority16 = intManager->addProperty(tr("曲率稀疏度"));
    priority14 = intManager->addProperty(tr("斑点线颜色"));
    priority17 = intManager->addProperty(tr("面积比"));
    intManager->setRange(priority17, 0, 120);

    priority20= intManager->addProperty(tr("关键点大小"));
    priority21= intManager->addProperty(tr("关键点个数"));
    priority22= intManager->addProperty(tr("关键点颜色"));

    priority30= intManager->addProperty(tr("控制点大小"));
    priority31= intManager->addProperty(tr("控制点个数"));
    priority32= intManager->addProperty(tr("控制点颜色"));

    priority1R= intManager->addProperty(tr("R"));
    priority1G= intManager->addProperty(tr("G"));
    priority1B= intManager->addProperty(tr("B"));
    intManager->setRange(priority1R, 0, 255);
    intManager->setRange(priority1G, 0, 255);
    intManager->setRange(priority1B, 0, 255);

    priority2R= intManager->addProperty(tr("R"));
    priority2G= intManager->addProperty(tr("G"));
    priority2B= intManager->addProperty(tr("B"));
    intManager->setRange(priority2R, 0, 255);
    intManager->setRange(priority2G, 0, 255);
    intManager->setRange(priority2B, 0, 255);

    priority3R= intManager->addProperty(tr("R"));
    priority3G= intManager->addProperty(tr("G"));
    priority3B= intManager->addProperty(tr("B"));
    intManager->setRange(priority3R, 0, 255);
    intManager->setRange(priority3G, 0, 255);
    intManager->setRange(priority3B, 0, 255);

    //加RGB子属性
    priority14->addSubProperty(priority1R);
    priority14->addSubProperty(priority1G);
    priority14->addSubProperty(priority1B);

    priority22->addSubProperty(priority2R);
    priority22->addSubProperty(priority2G);
    priority22->addSubProperty(priority2B);

    priority32->addSubProperty(priority3R);
    priority32->addSubProperty(priority3G);
    priority32->addSubProperty(priority3B);

    groupManager = new QtGroupPropertyManager(splitterRight);

    spinBoxFactory = new QtSpinBoxFactory;
    enumManager = new QtEnumPropertyManager;
    preEnumManager=enumManager;


    comboBoxFactory = new QtEnumEditorFactory;
    item8 = enumManager->addProperty(tr("斑点颜色"));
    (*enumNames) << tr("深绿1") << tr("深绿2") << tr("中绿1") << tr("中绿2")<< tr("翠绿1")<< tr("翠绿2") << tr("黄绿1") << tr("黄绿2");
    (*enumNames) << tr("褐土1") << tr("褐土2") << tr("褐土3") << tr("褐土4")<< tr("褐土5")<< tr("褐土6") << tr("褐土7") << tr("红土1");
    (*enumNames) << tr("红土2") << tr("黄土1") << tr("黄土2") << tr("黄土3")<< tr("黄土4")<< tr("黄土5") << tr("沙土1") << tr("沙土2");
    (*enumNames) << tr("沙土3") << tr("沙土4") << tr("沙土5") << tr("沙土6")<< tr("黑色")<< tr("白色");

    for(int i=1;i<addColorNum+1;i++){
        (*enumNames)<<allColor.colorName[i];
    }


    enumManager->setEnumNames(item8, *enumNames);

    QMap<int,QIcon> enumIcons;
    QPixmap pix[31+addColorNum];
    QPixmap tempPix(200,100);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        enumIcons[i-1] = QIcon(pix[i]);
    }

    enumManager->setEnumIcons(item8, enumIcons);
    enumManager->setValue(item8,allColor.index[spotSelectedNum]);

    task1 = groupManager->addProperty(tr("斑点属性"));
    intManager->setValue(priority11,drawOk);
    intManager->setValue(priority13,spotLineWidth);//keyPointSize
    intManager->setValue(priority15,minResolution);//设置分辨率
    intManager->setValue(priority16,markNum);//设置稀疏度
    intManager->setValue(priority17,areaRatio[spotSelectedNum]);
    intManager->setValue(priority20,keyPointSize);
    intManager->setValue(priority30,handlePointSize);
    intManager->setValue(priority31, 2*spotNum[spotSelectedNum]);
    intManager->setValue(priority21, spotNum[spotSelectedNum]);


    intManager->setValue(priority1R,spotR);
    intManager->setValue(priority1G,spotG);
    intManager->setValue(priority1B,spotB);

    intManager->setValue(priority2R,keyPointR);
    intManager->setValue(priority2G,keyPointG);
    intManager->setValue(priority2B,keyPointB);

    intManager->setValue(priority3R,handlePointR);
    intManager->setValue(priority3G,handlePointG);
    intManager->setValue(priority3B,handlePointB);


    task1->addSubProperty(priority11);
    task1->addSubProperty(priority13);
    task1->addSubProperty(priority15);
    task1->addSubProperty(priority16);
    task1->addSubProperty(priority17);
    task1->addSubProperty(item8);
    task1->addSubProperty(priority14);

    task2=groupManager->addProperty(tr("关键点属性"));
    task2->addSubProperty(priority20);
    task2->addSubProperty(priority21);
    task2->addSubProperty(priority22);

    task3=groupManager->addProperty(tr("控制点属性"));
    task3->addSubProperty(priority30);
    task3->addSubProperty(priority31);
    task3->addSubProperty(priority32);

    editor = new QtTreePropertyBrowser(splitterRight);
    editor->setFactoryForManager(enumManager,comboBoxFactory);
    editor->setFactoryForManager(intManager, spinBoxFactory);
    editor->addProperty(task1);
    editor->addProperty(task2);
    editor->addProperty(task3);
    editor->show();


    rightDock.setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,&rightDock);
    if(preRightDock){
        delete preRightDock;
    }
    connect(enumManager, SIGNAL(propertyChanged(QtProperty *)),this, SLOT(editSpot()));
    connect(intManager, SIGNAL(valueChanged(QtProperty *,int)),
            this, SLOT(editSpot()));
}
void MainWindow::backWardF(){
    centralDraw->backWardF();
}

void MainWindow::endThread(){

}

void MainWindow::forWardF(){
    centralDraw->forWardF();
}

void MainWindow::caculateColorProportion(){
    drawOk=centralDraw->getDrawOk();

    //初始化颜色比
    for(int i=1;i<31+addColorNum;i++){
        colorProportion[i]=0;
    }

    backGroundProportion=100;

    float tempCount=0;
    for(int i=1;i<drawOk+1;i++){

        colorProportion[allColor.index[i]+1]+=areaRatio[i];
        //qDebug("****************%d",allColor.index[i]+1);
        tempCount+=areaRatio[i];
    }

    //    for(int i=1;i<31;i++){
    //        qDebug("@@@@@@@@@@@@@@%f",colorProportion[i]);
    //    }



    //qDebug("$$$$$$$$$$$$%f",tempCount);
    float tempAllArea=0,tempAreaLeft;
    for(int i=1;i<31+addColorNum;i++){
        if(colorProportion[i]>0)
            tempAllArea+=colorProportion[i];
    }
    tempAreaLeft=100-tempAllArea;

    colorProportion[backGroundColorIndex+1]+=tempAreaLeft;

    backGroundProportion=100-tempCount;

}

void MainWindow::clearAll(){
    centralDraw->clear();
    centralDraw->update();
}
void MainWindow::clearOne(){
    //centralDraw->clearOne();
    //centralDraw->getCanvasBigPoint();
    //centralDraw->getCanvasBigPointS();
    //centralDraw->getCanvasBigPointT();
}

void MainWindow::ChildWindowEventSlot(){
    /*int tempFlag=*/centralDraw->getEventStyle();
    drawOk=centralDraw->getDrawOk();
    spotSelectedNum=centralDraw->getSpotSelectedNum();
    centralDraw->getSpotNum(spotNum);
    windowScale=centralDraw->getStretch();
    if(fabs(windowScale-1)<0.001){
        centralDraw->getAreaRatio(areaRatio);
    }
    centralDraw->getCtrl(ctrlSize,spotSelectedCtrl);
    caculateColorProportion();
    addSpotEdit();
    addBackGroundEdit();
    setChange();
}

void MainWindow::comboBoxSpotChanged(){
    int currentIndex=spotComboBox->currentIndex();
    spotColor=iconColor[currentIndex+1];
    allColor.myColor[spotSelectedNum]=spotColor;
    allColor.index[spotSelectedNum]=currentIndex;

    if(enumManager->value(item8)!=allColor.index[spotSelectedNum]){
        enumManager->setValue(item8,allColor.index[spotSelectedNum]);
    }

    if(ctrlSize){
        list<int>::iterator oP=spotSelectedCtrl.begin();
        for(int i=1;i<ctrlSize+1;i++,oP++){
            allColor.myColor[*oP]=spotColor;
            allColor.index[*oP]=currentIndex;
        }
    }
    else{
        allColor.myColor[spotSelectedNum]=spotColor;
        allColor.index[spotSelectedNum]=currentIndex;
    }
    //    qDebug("iiiiiiiiiiiiiiiiiiiid%d@@@@@@@@@@@@@@@@@%d",currentIndex,spotSelectedNum);

    centralDraw->setColor(spotColor,currentIndex,&exchangeS);
}

void MainWindow::comboBoxBackGroundChanged(){
    int currentIndex=backgroundComboBox->currentIndex();
    backGroundColor=iconColor[currentIndex+1];
    backGroundColorIndex=currentIndex;
    qDebug("CCCCCCCCCCCC%d",currentIndex);

    if(enumManagerL->value(BGProperty)!=backGroundColorIndex){
        enumManagerL->setValue(BGProperty,backGroundColorIndex);
    }

    centralDraw->setBackGroundColor(backGroundColor,backGroundColorIndex);
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    menu->addAction(actCpy);
    //menu->addAction(actCut);
    menu->addAction(paste);
    menu->addAction(actDelete);
    menu->addAction(actShowEdge);
    menu->addAction(setColor);
    menu->addAction(refreshAreaRatio);
    menu->addAction(showKeyPoint);
    menu->move(cursor().pos());
    rightX=cursor().pos().x();
    rightY=cursor().pos().y();
    //让菜单显示的位置在鼠标的坐标上
    menu->show();

}

void MainWindow::closeACDialog(){
    addColorDialog->close();
    QString tempS,colorName;
    int R,G,B;
    tempS=editH->text();
    R=tempS.toInt();
    tempS=editS->text();
    G=tempS.toInt();
    tempS=editV->text();
    B=tempS.toInt();

    colorName=editName->text();
    qDebug()<<R<<G<<B;

    QColor tempColor;
    tempColor.setRgb(R,G,B);
    tempColor.lighter(200);
    addColorNum++;
    iconColor[30+addColorNum]=tempColor;

    allColor.colorName[addColorNum]=colorName;

    centralDraw->setNewColor(iconColor,addColorNum);

    colorManagement.saveColorInfo(allColor,addColorNum,iconColor);


    delete addColorDialog;
    addBackGroundEdit();
    addSpotEdit();
    ui->mainToolBar->clear();
    addMyToolBar();

    //    if(preMainToolBar){
    //       delete preMainToolBar;
    //    }
}

void MainWindow::closeDCDialog(){
    deleteColorDialog->close();
    int tempIndex=deleteComboBox->currentIndex();
    qDebug()<<tempIndex;
    for(int i=tempIndex+1;i<addColorNum;i++){
        iconColor[30+i]=iconColor[30+i+1];
        allColor.colorName[i]=allColor.colorName[i+1];
    }
    addColorNum--;
    centralDraw->setNewColor(iconColor,addColorNum);

    colorManagement.saveColorInfo(allColor,addColorNum,iconColor);

    delete deleteColorDialog;
    addSpotEdit();
    addBackGroundEdit();

    ui->mainToolBar->clear();
    addMyToolBar();

}

void MainWindow::closeDelColorDialog(){
    //int tempIndex=deleteComboBox->currentIndex();
    //qDebug()<<tempIndex;
}

void MainWindow::closeDialog(){
    myDialog->close();
    int checkId=allRadio->checkedId();
    int x,y,z;
    QString tempS;
    if(checkId==0){
        tempS=edit1->text();
        x=tempS.toInt();
        tempS=edit2->text();
        y=tempS.toInt();
        if(x!=0&&y!=0){
            drawX=x;
            drawY=y;
            drawZ=0;
            float temp=drawX;
            modelStretch=temp/1000;
            AutoCADFlag=0;
            addBackGroundEdit();
            centralDraw->setCanvasXY(x,y,1);
        }
    }
    if(checkId==1){
        tempS=edit3->text();
        x=tempS.toInt();
        tempS=edit4->text();
        y=tempS.toInt();
        tempS=edit5->text();
        z=tempS.toInt();
        if(x!=0&&y!=0&&z!=0){
            drawX=x;
            drawY=y;
            drawZ=z;
            float temp=drawX;
            modelStretch=temp/1000;
            AutoCADFlag=1;
            addBackGroundEdit();
            centralDraw->setCanvasXYZ(x,y,z,2);
        }
    }
    delete myDialog;
}
void MainWindow::closeDialogColor(){
    myDialogColor->close();

    int checkId=allRadioColor->checkedId();
    //qDebug("xuan zhong id shi:%d",checkId);
    getSize=size->checkedId();

    if(checkId==0){
        //选择第一种颜色方案6:4
        colorChoose=1;
        currentIndex11=spotComboBoxD11.currentIndex();
        currentIndex12=spotComboBoxD12.currentIndex();
    }
    else if(checkId==1){
        //选择第二种颜色方案3:3:4
        colorChoose=2;
        currentIndex21=spotComboBoxD21.currentIndex();
        currentIndex22=spotComboBoxD22.currentIndex();
        currentIndex23=spotComboBoxD23.currentIndex();
    }
    else if(checkId==2){
        //选择第三种颜色方案2:2:3:3
        colorChoose=3;
        currentIndex31=spotComboBoxD31.currentIndex();
        currentIndex32=spotComboBoxD32.currentIndex();
        currentIndex33=spotComboBoxD33.currentIndex();
        currentIndex34=spotComboBoxD34.currentIndex();
    }
    spotComboBoxD11.clear();
    spotComboBoxD12.clear();

    spotComboBoxD21.clear();
    spotComboBoxD22.clear();
    spotComboBoxD23.clear();

    spotComboBoxD31.clear();
    spotComboBoxD32.clear();
    spotComboBoxD33.clear();
    spotComboBoxD34.clear();

    //delete myDialogColor;
}

void MainWindow::getControlThread(controlThread *temp){
    cThread=temp;
}

void MainWindow::showNotingColor(){
    myDialogColor->close();
    spotComboBoxD11.clear();
    spotComboBoxD12.clear();

    spotComboBoxD21.clear();
    spotComboBoxD22.clear();
    spotComboBoxD23.clear();

    spotComboBoxD31.clear();
    spotComboBoxD32.clear();
    spotComboBoxD33.clear();
    spotComboBoxD34.clear();

    return;
}

void MainWindow::copyAutoCADL(){
    if(centralDraw->saveSpotPoint()){
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("System");
        QFile file("..\\draw\\AutoCAD\\1.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(500,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取左视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
    }
}
void MainWindow::copyAutoCADR(){
    if(centralDraw->saveSpotPoint()){
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("utf8");
        //    QFile file("..\\draw\\AutoCAD\\1.txt");
        QFile file("..\\draw\\AutoCAD\\3.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(300,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取右视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(300,100);
        msgBox.exec();
    }
}
void MainWindow::copyAutoCADM(){
    if(centralDraw->saveSpotPoint()){
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("utf8");
        QFile file("..\\draw\\AutoCAD\\2.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(300,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取中间视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(300,100);
        msgBox.exec();
    }
}
void MainWindow::copyAutoCADU(){
    if(centralDraw->saveSpotPoint()){
        qDebug("sssssssss");
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("utf8");
        //QFile file("..\\draw\\AutoCAD\\3.txt");
        QFile file("..\\draw\\AutoCAD\\0.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(300,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取前视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(300,100);
        msgBox.exec();
    }
}
void MainWindow::copyAutoCADD(){
    if(centralDraw->saveSpotPoint()){
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("utf8");
        QFile file("..\\draw\\AutoCAD\\4.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(300,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取后视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(300,100);
        msgBox.exec();
    }
}
void MainWindow::copyAutoCADA(){
    if(centralDraw->saveSpotPoint()){
        QClipboard *clipboard = QApplication::clipboard();
        QTextCodec * code = QTextCodec::codecForName("utf8");
        QFile file("..\\draw\\AutoCAD\\5.txt");
        QMessageBox msgBox(this);


        if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ){
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("获取图纸失败！  "));
            msgBox.setMinimumSize(300,100);
            msgBox.exec();
            return ;
        }

        QTextStream stream(&file);
        stream.setCodec(code);//对输出流的设置
        clipboard->setText(stream.readAll());
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("获取五视图斑点信息成功，请在AutoCAD中ctrl+v即可完成斑点绘制！  "));
        msgBox.setMinimumSize(300,100);
        msgBox.exec();
    }
}
void MainWindow::editBackGround(){
    //qDebug("sssssssssss");
    int currentIndex=enumManagerL->value(BGProperty);
    qDebug("IIIIIIIIIII%d",currentIndex);
    if(currentIndex>-1){
        backGroundColor=iconColor[currentIndex+1];
        backGroundColorIndex=currentIndex;

        if(backgroundComboBox->currentIndex()!=currentIndex){
            //qDebug1("li:%d",spotSelectedNum);
            //qDebug("aaaaaaaaaaaaaa%d",currentIndex);
            backgroundComboBox->setCurrentIndex(currentIndex);
            qDebug("aaaaaaaaaaaa%d",currentIndex);
        }
    }

    //int tempX,tempY,tempZ;
    drawX=intManagerL->value(BGPropertyX);
    drawY=intManagerL->value(BGPropertyY);
    drawZ=intManagerL->value(BGPropertyZ);
    float temp=drawX;
    if(drawX<drawY)
        temp=drawY;
    if(drawX<drawZ)
        temp=drawZ;
    modelStretch=temp/1000;
    //qDebug("~~~%d %d %d",intManager->value(BGPropertyX),drawY,drawZ);
    if(drawZ){
        if(drawX!=0&&drawY!=0){
            //qDebug("sssssssssss");
            centralDraw->setBackGroundSize(drawX,drawY,drawZ);
            AutoCADFlag=1;
        }
    }
    else{
        if(drawX!=0&&drawY!=0){
            centralDraw->setBackGroundSize(drawX,drawY,drawZ);
            AutoCADFlag=0;
        }
    }

}


void MainWindow::editForcePoint(){
    //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
    //forcePointSize=intManager->value(priority);
    //qDebug1("dian da xiao shi :%d:",forcePointSize);
    this->repaint();
}

void MainWindow::editOPoint(){
    //oPointSize=intManager->value(priority);
    //enumManager->propertyChanged();
    this->repaint();

}

void MainWindow::editSpot(){
    //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
    //QtProperty *a;
    int currentIndex=enumManager->value(item8);
    //qDebug1(".........%d",currentIndex);
    //spotComboBox->setCurrentIndex(currentIndex);
    if(currentIndex>-1){
        spotColor=iconColor[currentIndex+1];
        allColor.myColor[spotSelectedNum]=spotColor;
        allColor.index[spotSelectedNum]=currentIndex;
        //qDebug("1111111111111111111111111111");
        if(spotComboBox->currentIndex()!=currentIndex){
            //qDebug1("li:%d",spotSelectedNum);
            spotComboBox->setCurrentIndex(currentIndex);
        }
        //获取右侧工具箱现在数据值

        //斑点值
        spotLineWidth=intManager->value(priority13);
        spotR=intManager->value(priority1R);
        spotG=intManager->value(priority1G);
        spotB=intManager->value(priority1B);
        minResolution=intManager->value(priority15);
        markNum=intManager->value(priority16);
        spotLineColor=QColor(spotR,spotG,spotB);

        //关键点值
        keyPointSize=intManager->value(priority20);
        keyPointR=intManager->value(priority2R);
        keyPointG=intManager->value(priority2G);
        keyPointB=intManager->value(priority2B);
        keyPointColor=QColor(keyPointR,keyPointG,keyPointB);

        //控制点值
        handlePointSize=intManager->value(priority30);
        handlePointR=intManager->value(priority3R);
        handlePointG=intManager->value(priority3G);
        handlePointB=intManager->value(priority3B);
        handlePointColor=QColor(handlePointR,handlePointG,handlePointB);

        exchangeS.handlePointColor=handlePointColor;
        exchangeS.handlePointSize=handlePointSize;
        exchangeS.hPointLineWidth=hPointLineWidth;
        exchangeS.keyPointColor=keyPointColor;
        exchangeS.keyPointSize=keyPointSize;
        exchangeS.markNum=markNum;
        exchangeS.minResolution=minResolution;
        exchangeS.spotLineColor=spotLineColor;
        exchangeS.spotLineWidth=spotLineWidth;
        //qDebug("sdfsdfsdfsddss");
        centralDraw->setColor(spotColor,currentIndex,&exchangeS);
    }

}

void MainWindow::initialColor(){
    //QColor tempColor[maxSize];
    colorManagement.getColorInfo(addColorNum,iconColor,allColor);
}

void MainWindow::getAllColor(){
    centralDraw->getAllColor(allColor,backGroundColorIndex,backGroundColor);
}

void MainWindow::getDifferentColor(){
    if(colorChoose==1){//6:4
        if(getSize==1){
            autoColorT();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }
        else if(getSize==0){
            autoColorT();
            //addBackGroundEdit();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }
    }
    else if(colorChoose==2){//4:3:3
        if(getSize==1){
            //                centralDraw->getCanvasBigPointS();
            //                centralDraw->getCanvasPointS(100,100);
            //                autoColorS();
            //centralDraw->getCanvasPointNew();
            //斑点自动生成线程
            autoColorS();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }else if(getSize==0){
            //centralDraw->getCanvasPointNew();
            autoColorS();
            //                    centralDraw->getCanvasPointS(90,80);
            //                    autoColorS();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }
    }
    else if(colorChoose==3){//2:2:3:3
        //qDebug("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%d",getSize);
        if(getSize==1){
            autoColorF();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }else if(getSize==0){
            autoColorF();
            enumManagerL->setValue(BGProperty,backGroundColorIndex);
        }
    }
}

void MainWindow::getCentral(DrawWidget *centralTemp){
    centralDraw=centralTemp;
    connect(centralDraw,SIGNAL(ChildWindowEvent()),this,SLOT(ChildWindowEventSlot()));
    connect(centralDraw,SIGNAL(getShowStretch()),this,SLOT(showStretch()));
    connect(centralDraw,SIGNAL(spotSelected_S()),this,SLOT(spotSelected()));
    connect(centralDraw,SIGNAL(getAllColor_s()),this,SLOT(getAllColor()));
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    centralDraw->keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    centralDraw->keyReleaseEvent(event);
}

void MainWindow::leftDockWidgetChanged(){
    //    int currentIndex=spotComboBox->currentIndex();
    //    leftDock->close();
    //    delete(leftDock);

    //    //新建一个DockWidget
    //    leftDock=new QDockWidget(QObject::tr("迷彩图案信息"),this);

    //    //新建一个分割窗口
    //    QSplitter *splitterMain=new QSplitter(Qt::Vertical,leftDock);
    //    //QSplitter *splitterRight=new QSplitter(Qt::Vertical,splitterMain);


    //    leftTreeWidget=new QTreeWidget(splitterMain);


    //    leftTreeWidget->setMinimumWidth(20);
    //    leftTreeWidget->setColumnCount(2);
    //    leftTreeWidget->setColumnWidth(0,100);
    //    leftTreeWidget->setColumnWidth(1,100);
    //    //leftTreeWidget->setColumnWidth(0,100);
    //    QListWidget *b=new QListWidget(splitterMain);

    //    b->setMinimumWidth(20);
    //    leftDock->setWidget(splitterMain);
    //    QStringList headers;
    //    headers<< QObject::tr("属性") <<QObject::tr("值");
    //    leftTreeWidget->setHeaderLabels(headers);
    //    QStringList zhangsan;
    //    zhangsan << QObject::tr("测试斑点1");
    //    QTreeWidgetItem *zhangsanroot = new QTreeWidgetItem(leftTreeWidget, zhangsan);
    //    QStringList zhangsanChinese;
    //    zhangsanChinese << QObject::tr("关键点") << QObject::tr("12");
    //    QTreeWidgetItem *leaf1 = new QTreeWidgetItem(zhangsanroot, zhangsanChinese);
    //    zhangsanroot->addChild(leaf1);
    //    QStringList zhangsanMath ;
    //        if(currentIndex==0){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("深绿1");
    //        }
    //        if(currentIndex==1){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("深绿2");
    //        }

    //        if(currentIndex==2){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("中绿1");
    //        }
    //        if(currentIndex==3){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("中绿2");
    //        }

    //        if(currentIndex==4){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("翠绿1");
    //        }
    //        if(currentIndex==5){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("翠绿2");
    //        }

    //        if(currentIndex==6){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("黄土1");
    //        }
    //        if(currentIndex==7){
    //            zhangsanMath<< QObject::tr("颜色") << QObject::tr("白色");
    //        }
    //    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(zhangsanroot, zhangsanMath);
    //    zhangsanroot->addChild(leaf2);
    //    leftTreeWidget->expandAll();
    //    leftDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    //    addDockWidget(Qt::LeftDockWidgetArea,leftDock);
}


void MainWindow::mapping()
{
    //    childWindow *child=new childWindow;
    //    child->setBaseSize(800,300);
    //    child->show();
    centralDraw->mapping();
    /////////

}

void MainWindow::paintEvent(QPaintEvent *){
    //qDebug1("@@@@@@@@@:%d  %d",width()-leftDock->width()-rightDock->width()-33,height());
}
void MainWindow::refreshAreaRatio_s(){
    windowScale=centralDraw->getWindowScale();
    if(fabs(windowScale-1)<0.001){
        ChildWindowEventSlot();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前缩放比例必须为1        "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
    }
}

void MainWindow::readCanvasF(){

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Document"),
                QDir::currentPath(),
                "Document files (*.spot)");
    if (!fileName.isNull()) { //用户选择了文件
        // 处理文件
        centralDraw->readCanvasF(fileName);
    } else {// 用户取消选择
    }
    //centralDraw->readCanvasF();
}

void MainWindow::closeAddColorDialog(){
    addColorDialog->close();
    delete addColorDialog;
}

void MainWindow::showACDialog(){
    addColorDialog=new QDialog;
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *lbN = new QLabel(QWidget::tr("     颜色名称:        "));
    QLabel *lbH = new QLabel(QWidget::tr("     R:              "));
    QLabel *lbS = new QLabel(QWidget::tr("     G:              "));
    QLabel *lbV = new QLabel(QWidget::tr("     B:              "));

    QValidator *validator=new QIntValidator(0,255,this);

    editH= new QLineEdit;
    editH->setValidator(validator);

    editS= new QLineEdit;
    editS->setValidator(validator);

    editV= new QLineEdit;
    editV->setValidator(validator);

    editName=new QLineEdit;

    QPushButton *btn_ok = new QPushButton(QWidget::tr("添加"), myDialog);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("取消"), myDialog);


    gridLayout->addWidget(lbN, 0, 0);
    gridLayout->addWidget(editName, 0, 1);

    gridLayout->addWidget(lbH, 1, 0);
    gridLayout->addWidget(editH, 1, 1);

    gridLayout->addWidget(lbS, 2, 0);
    gridLayout->addWidget(editS, 2, 1);

    gridLayout->addWidget(lbV, 3, 0);
    gridLayout->addWidget(editV, 3, 1);


    gridLayout->addWidget(btn_ok, 4, 0);
    gridLayout->addWidget(btn_cancel, 4, 1);
    addColorDialog->setLayout(gridLayout);
    addColorDialog->show();

    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(closeACDialog()));
    connect(btn_cancel, SIGNAL(clicked(bool)), this, SLOT(closeAddColorDialog()));
}

void MainWindow::showDCDialog(){
    deleteColorDialog=new QDialog;
    deleteComboBox=new QComboBox(deleteColorDialog);
    QGridLayout *gridLayout = new QGridLayout;

    for(int i=1;i<addColorNum+1;i++){
        deleteComboBox->addItem(allColor.colorName[i]);
    }

    QPixmap pix[31+addColorNum];
    QPixmap tempPix(100,100);
    deleteComboBox->setFixedHeight(22);
    deleteComboBox->setFixedWidth(200);

    for(int i=1;i<addColorNum+1;i++){
        pix[i]=tempPix;
        //qDebug11("%d",i);
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[30+i]);
        p.drawRect(0,0,200,100);
        deleteComboBox->setItemIcon(i-1,QIcon(pix[i]));
    }
    deleteComboBox->setIconSize(QSize(30,50));//(165,18));
    deleteComboBox->setCurrentIndex(0);
    QPushButton *btn_ok = new QPushButton(QWidget::tr("添加"), myDialog);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("取消"), myDialog);
    gridLayout->addWidget(deleteComboBox,0,0,1,2);
    gridLayout->addWidget(btn_ok,1,0);
    gridLayout->addWidget(btn_cancel,1,1);
    deleteColorDialog->setLayout(gridLayout);
    deleteColorDialog->show();
    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(closeDCDialog()));
    connect(btn_cancel, SIGNAL(clicked(bool)), this, SLOT(closeDelColorDialog()));
}

//打开图片
void MainWindow::openPicture(){
    //QString
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("打开图片"),
                "",
                tr("Images (*.png *.xpm *.jpg)"));
    // "/home/foxman","Images (*.png *.xpm *.jpg)",this
    if (!fileName.isNull()) { //用户选择了文件
        // 处理文件
        centralDraw->openPicture(fileName);
    } else {
        // 用户取消选择
    }
}



void MainWindow::saveCanvasF(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存工程"),
                                                    "",
                                                    tr("Config Files (*.spot)"));

    if (!fileName.isNull())
    {
        //fileName是文件名
        centralDraw->saveCanvasF(fileName);
    }
    else
    {
        //点的是取消
    }
    //centralDraw->saveCanvasF();
}


void MainWindow::setColorD(){
    myDialogColor = new QDialog;
    //myDialogColor->setWindowFlags(~&(Qt::WindowCloseButtonHint));
    //myDialogColor->setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);
    myDialogColor->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    allRadioColor=new QButtonGroup;
    size=new QButtonGroup;
    QGridLayout *gridLayout = new QGridLayout;


    //6:4
    QRadioButton *buttonSF = new QRadioButton(tr("比例为6:4"));
    QLabel *lb11 = new QLabel(QWidget::tr("比例为6的颜色:"));
    QLabel *lb12 = new QLabel(QWidget::tr("比例为4的颜色:"));
    //spotComboBoxD11=new QComboBox;
    spotComboBoxD11.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD11.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD11.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD11.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD11.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD11.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD11.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD11.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD11.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD11.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD11.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD11.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD11.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD11.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD11.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD11.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD11.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD11.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD11.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD11.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD11.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD11.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD11.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD11.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD11.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD11.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD11.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD11.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD11.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD11.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD11.addItem(allColor.colorName[i]);
    }
    //qDebug("ssssssssssssssssssssssssssss");
    qDebug()<<addColorNum;

    QPixmap pix[31+addColorNum];
    QPixmap tempPix(100,100);
    spotComboBoxD11.setFixedHeight(22);
    spotComboBoxD11.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD11.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD11.setIconSize(QSize(30,50));//(165,18));




    //spotComboBoxD12=new QComboBox;
    spotComboBoxD12.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD12.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD12.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD12.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD12.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD12.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD12.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD12.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD12.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD12.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD12.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD12.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD12.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD12.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD12.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD12.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD12.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD12.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD12.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD12.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD12.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD12.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD12.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD12.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD12.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD12.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD12.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD12.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD12.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD12.addItem(tr(" 白色   WN8384"));
    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD12.addItem(allColor.colorName[i]);
    }


    spotComboBoxD12.setFixedHeight(22);
    spotComboBoxD12.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD12.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD12.setIconSize(QSize(30,50));


    QLabel *lblEmpty= new QLabel(QWidget::tr(" "));
    gridLayout->addWidget(buttonSF,0,0);
    gridLayout->addWidget(lb11,1,0);
    gridLayout->addWidget(lb12,2,0);
    gridLayout->addWidget(&spotComboBoxD11,1,1);
    gridLayout->addWidget(&spotComboBoxD12,2,1);
    gridLayout->addWidget(lblEmpty,3,1,1,2);
    //////////////////////////////////////////////////
    //3:3:4
    QRadioButton *buttonSS = new QRadioButton(tr("设置颜色比例为3:3:4"));
    QLabel *lb21 = new QLabel(QWidget::tr("比例为3的颜色:"));
    QLabel *lb22 = new QLabel(QWidget::tr("比例为3的颜色:"));
    QLabel *lb23 = new QLabel(QWidget::tr("比例为4的颜色:"));
    //spotComboBoxD21=new QComboBox;
    spotComboBoxD21.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD21.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD21.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD21.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD21.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD21.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD21.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD21.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD21.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD21.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD21.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD21.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD21.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD21.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD21.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD21.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD21.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD21.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD21.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD21.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD21.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD21.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD21.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD21.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD21.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD21.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD21.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD21.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD21.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD21.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD21.addItem(allColor.colorName[i]);
    }

    spotComboBoxD21.setFixedHeight(22);
    spotComboBoxD21.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD21.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD21.setIconSize(QSize(30,50));//(165,18));

    //////////////////////////////////////////////////////////////////////
    //spotComboBoxD22=new QComboBox;
    spotComboBoxD22.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD22.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD22.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD22.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD22.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD22.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD22.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD22.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD22.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD22.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD22.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD22.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD22.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD22.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD22.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD22.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD22.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD22.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD22.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD22.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD22.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD22.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD22.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD22.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD22.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD22.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD22.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD22.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD22.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD22.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD22.addItem(allColor.colorName[i]);
    }

    spotComboBoxD22.setFixedHeight(22);
    spotComboBoxD22.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD22.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD22.setIconSize(QSize(30,50));
    /////////////////////////////////////////////////////////////////
    //spotComboBoxD23=new QComboBox;
    spotComboBoxD23.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD23.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD23.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD23.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD23.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD23.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD23.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD23.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD23.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD23.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD23.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD23.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD23.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD23.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD23.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD23.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD23.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD23.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD23.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD23.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD23.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD23.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD23.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD23.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD23.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD23.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD23.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD23.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD23.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD23.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD23.addItem(allColor.colorName[i]);
    }

    spotComboBoxD23.setFixedHeight(22);
    spotComboBoxD23.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD23.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD23.setIconSize(QSize(30,50));

    gridLayout->addWidget(buttonSS,4,0);
    gridLayout->addWidget(lb21,5,0);
    gridLayout->addWidget(lb22,6,0);
    gridLayout->addWidget(lb23,7,0);
    gridLayout->addWidget(&spotComboBoxD21,5,1);
    gridLayout->addWidget(&spotComboBoxD22,6,1);
    gridLayout->addWidget(&spotComboBoxD23,7,1);
    gridLayout->addWidget(lblEmpty,8,2);


    //////////////////////////////////////////////////////////////////
    //2:2:3:3
    QRadioButton *buttonST = new QRadioButton(tr("设置颜色比例为2:2:3:3"));
    QLabel *lb31 = new QLabel(QWidget::tr("比例为2的颜色:"));
    QLabel *lb32 = new QLabel(QWidget::tr("比例为2的颜色:"));
    QLabel *lb33 = new QLabel(QWidget::tr("比例为3的颜色:"));
    QLabel *lb34 = new QLabel(QWidget::tr("比例为3的颜色:"));
    //spotComboBoxD31=new QComboBox;
    spotComboBoxD31.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD31.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD31.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD31.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD31.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD31.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD31.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD31.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD31.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD31.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD31.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD31.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD31.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD31.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD31.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD31.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD31.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD31.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD31.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD31.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD31.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD31.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD31.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD31.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD31.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD31.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD31.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD31.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD31.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD31.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD31.addItem(allColor.colorName[i]);
    }

    spotComboBoxD31.setFixedHeight(22);
    spotComboBoxD31.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD31.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD31.setIconSize(QSize(30,50));//(165,18));

    //////////////////////////////////////////////////////////////////////
    //spotComboBoxD32=new QComboBox;
    spotComboBoxD32.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD32.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD32.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD32.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD32.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD32.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD32.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD32.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD32.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD32.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD32.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD32.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD32.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD32.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD32.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD32.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD32.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD32.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD32.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD32.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD32.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD32.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD32.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD32.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD32.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD32.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD32.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD32.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD32.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD32.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD32.addItem(allColor.colorName[i]);
    }

    spotComboBoxD32.setFixedHeight(22);
    spotComboBoxD32.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD32.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD32.setIconSize(QSize(30,50));
    /////////////////////////////////////////////////////////////////
    //spotComboBoxD33=new QComboBox;
    spotComboBoxD33.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD33.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD33.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD33.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD33.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD33.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD33.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD33.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD33.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD33.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD33.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD33.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD33.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD33.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD33.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD33.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD33.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD33.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD33.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD33.addItem(tr(" 黄土3  YE2738"));
    spotComboBoxD33.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD33.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD33.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD33.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD33.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD33.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD33.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD33.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD33.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD33.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD33.addItem(allColor.colorName[i]);
    }

    spotComboBoxD33.setFixedHeight(22);
    spotComboBoxD33.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD33.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD33.setIconSize(QSize(30,50));
    /////////////////////////////////////////////////////////////////////
    //spotComboBoxD34=new QComboBox;
    spotComboBoxD34.addItem(tr(" 深绿1  DG0730"));
    spotComboBoxD34.addItem(tr(" 深绿2  DG0730"));
    spotComboBoxD34.addItem(tr(" 中绿1  DG0730"));
    spotComboBoxD34.addItem(tr(" 中绿2  DG0730"));
    spotComboBoxD34.addItem(tr(" 翠绿1  DG0730"));
    spotComboBoxD34.addItem(tr(" 翠绿2  DG0730"));
    spotComboBoxD34.addItem(tr(" 黄绿1  YG1247"));
    spotComboBoxD34.addItem(tr(" 黄绿2  YG1560"));
    spotComboBoxD34.addItem(tr(" 褐土1  BE0811"));
    spotComboBoxD34.addItem(tr(" 褐土2  BE0922"));
    spotComboBoxD34.addItem(tr(" 褐土3  BE1130"));
    spotComboBoxD34.addItem(tr(" 褐土4  BE1225"));
    spotComboBoxD34.addItem(tr(" 褐土5  BE1230"));
    spotComboBoxD34.addItem(tr(" 褐土6  BE1732"));
    spotComboBoxD34.addItem(tr(" 褐土7  BE1824"));
    spotComboBoxD34.addItem(tr(" 红土1  RE1125"));
    spotComboBoxD34.addItem(tr(" 红土2  RE1328"));
    spotComboBoxD34.addItem(tr(" 黄土1  YE1624"));
    spotComboBoxD34.addItem(tr(" 黄土2  YE2344"));
    spotComboBoxD34.addItem(tr(" 黄土3  YE2738"));

    spotComboBoxD34.addItem(tr(" 黄土4  YE3249"));
    spotComboBoxD34.addItem(tr(" 黄土5  YE3559"));
    spotComboBoxD34.addItem(tr(" 沙土1  SE2139"));
    spotComboBoxD34.addItem(tr(" 沙土2  SE2232"));
    spotComboBoxD34.addItem(tr(" 沙土3  SE2425"));
    spotComboBoxD34.addItem(tr(" 沙土4  SE2635"));
    spotComboBoxD34.addItem(tr(" 沙土5  SE3340"));
    spotComboBoxD34.addItem(tr(" 沙土6  SE3948"));
    spotComboBoxD34.addItem(tr(" 黑色   BN0606"));
    spotComboBoxD34.addItem(tr(" 白色   WN8384"));

    for(int i=1;i<addColorNum+1;i++){
        spotComboBoxD34.addItem(allColor.colorName[i]);
    }

    spotComboBoxD34.setFixedHeight(22);
    spotComboBoxD34.setFixedWidth(200);
    for(int i=1;i<31+addColorNum;i++){
        pix[i]=tempPix;
        QPainter p(&pix[i]);
        p.setPen(Qt::NoPen);
        p.setBrush(iconColor[i]);
        p.drawRect(0,0,200,100);
        spotComboBoxD34.setItemIcon(i-1,QIcon(pix[i]));
    }
    spotComboBoxD34.setIconSize(QSize(30,50));

    gridLayout->addWidget(buttonST,9,0);
    gridLayout->addWidget(lb31,10,0);
    gridLayout->addWidget(lb32,11,0);
    gridLayout->addWidget(lb33,12,0);
    gridLayout->addWidget(lb34,13,0);
    gridLayout->addWidget(&spotComboBoxD31,10,1);
    gridLayout->addWidget(&spotComboBoxD32,11,1);
    gridLayout->addWidget(&spotComboBoxD33,12,1);
    gridLayout->addWidget(&spotComboBoxD34,13,1);
    gridLayout->addWidget(lblEmpty,14,2);
    ////////////////////////////////////////////////////////////////////
    QRadioButton *smallP = new QRadioButton(tr("     小斑点 "));
    QRadioButton *bigSmallP = new QRadioButton(tr("    大小斑点 "));

    size->addButton(smallP);
    size->addButton(bigSmallP);
    size->setId(smallP,0);
    size->setId(bigSmallP,1);

    gridLayout->addWidget(smallP,15,0);
    gridLayout->addWidget(bigSmallP,15,1);
    gridLayout->addWidget(lblEmpty,16,2);

    //////////////////////////////////////////////////////////////////
    QPushButton *btn_ok = new QPushButton(QWidget::tr("确定"), myDialogColor);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("取消"), myDialogColor);
    gridLayout->addWidget(btn_ok,17,0);
    gridLayout->addWidget(btn_cancel,17,1);
    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(closeDialogColor()));
    connect(btn_cancel, SIGNAL(clicked(bool)), this, SLOT(showNotingColor()));
    //connect(btn_cancel, SIGNAL(closeEvent()), this, SLOT(closeDialogColor()));
    //////////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////
    myDialogColor->setLayout(gridLayout);
    myDialogColor->setWindowTitle(QWidget::tr("斑点颜色设置"));

    allRadioColor->addButton(buttonSF);
    allRadioColor->addButton(buttonSS);
    allRadioColor->addButton(buttonST);
    allRadioColor->setId(buttonSF,0);
    allRadioColor->setId(buttonSS,1);
    allRadioColor->setId(buttonST,2);
    //myDialogColor->setBaseSize(600,600);


    myDialogColor->show();
}

void MainWindow::showVersion(){
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("版本信息"));
    msgBox.setText(tr("构建于2014年9月4日。版权北京工业大学，王勇实验室！"));
    msgBox.setMinimumSize(300,100);
    msgBox.exec();
}
void MainWindow::showNoting(){
    myDialog->close();
    delete myDialog;
    return;
}

void MainWindow::showDialog(){
    myDialog = new QDialog;
    allRadio=new QButtonGroup;
    QGridLayout *MainLayout = new QGridLayout;
    QGridLayout *gridLayout = new QGridLayout;
    QGridLayout *gridLayout1 = new QGridLayout;
    QGridLayout *gridLayout2 = new QGridLayout;
    QGridLayout *gridLayout3 = new QGridLayout;
    QGridLayout *gridLayout4 = new QGridLayout;
    QGroupBox *groupBox = new QGroupBox;
    QGridLayout *MainLayoutAll = new QGridLayout;

    QRadioButton *canvasB = new QRadioButton(tr("设置画布尺寸（单位：厘米）"));
    gridLayout->addWidget(canvasB, 0, 0);
    gridLayout->setColumnStretch(0,1);

    QLabel *lbl1 = new QLabel(QWidget::tr("长（厘米）:"));
    QValidator *validator=new QIntValidator(0,10000,this);
    edit1 = new QLineEdit;
    edit1->setValidator(validator);
    QLabel *lbl2 = new QLabel(QWidget::tr("宽（厘米）:"));
    QLabel *lblEmpty= new QLabel(QWidget::tr(" "));
    QLabel *lblEmpty2 = new QLabel(QWidget::tr(" "));
    edit2 = new QLineEdit;
    edit2->setValidator(validator);
    gridLayout1->setColumnStretch(0, 1);
    gridLayout1->setColumnStretch(1, 1);
    gridLayout1->setColumnStretch(2, 2);
    gridLayout1->addWidget(lbl1, 0, 0);
    gridLayout1->addWidget(edit1, 0, 1);
    gridLayout1->addWidget(lblEmpty2, 0, 2);
    gridLayout1->addWidget(lbl2, 1, 0);
    gridLayout1->addWidget(edit2, 1, 1);
    gridLayout1->addWidget(lblEmpty,1,2);

    QRadioButton *modelB = new QRadioButton(tr("设置为模型尺寸（单位：厘米）"));
    gridLayout2->addWidget(modelB, 0, 0);
    gridLayout2->setColumnStretch(0,1);

    QLabel *lbl3 = new QLabel(QWidget::tr("x:"));
    edit3 = new QLineEdit;
    edit3->setValidator(validator);
    QLabel *lbl4 = new QLabel(QWidget::tr("y:"));
    edit4 = new QLineEdit;
    edit4->setValidator(validator);
    QLabel *lbl5 = new QLabel(QWidget::tr("z:"));
    edit5 = new QLineEdit;
    edit5->setValidator(validator);
    QLabel *lblEmpty3 = new QLabel(QWidget::tr(" "));
    QLabel *lblEmpty4 = new QLabel(QWidget::tr(" "));
    QLabel *lblEmpty5 = new QLabel(QWidget::tr(" "));
    gridLayout3->setColumnStretch(0, 1);
    gridLayout3->setColumnStretch(1, 1);
    gridLayout3->setColumnStretch(2, 2);

    gridLayout3->addWidget(lbl3,0,0);
    gridLayout3->addWidget(edit3,0,1);
    gridLayout3->addWidget(lblEmpty3,0,2);

    gridLayout3->addWidget(lbl4,1,0);
    gridLayout3->addWidget(edit4,1,1);
    gridLayout3->addWidget(lblEmpty4,1,2);

    gridLayout3->addWidget(lbl5,2,0);
    gridLayout3->addWidget(edit5,2,1);
    gridLayout3->addWidget(lblEmpty5,2,2);

    QPushButton *btn_ok = new QPushButton(QWidget::tr("确定"), myDialog);
    QPushButton *btn_cancel = new QPushButton(QWidget::tr("取消"), myDialog);
    gridLayout4->setColumnStretch(0, 1);
    gridLayout4->setColumnStretch(1, 3);
    gridLayout4->setColumnStretch(2, 1);
    gridLayout4->setColumnStretch(3, 3);
    gridLayout4->setColumnStretch(4, 1);
    gridLayout4->addWidget(btn_ok,0,1);
    gridLayout4->addWidget(btn_cancel,0,3);

    MainLayout->addLayout(gridLayout,0,0);
    MainLayout->addLayout(gridLayout1,1,0);
    MainLayout->addLayout(gridLayout2,2,0);
    MainLayout->addLayout(gridLayout3,3,0);
    MainLayout->addLayout(gridLayout4,4,0);
    groupBox->setLayout(MainLayout);
    MainLayoutAll->addWidget(groupBox);

    myDialog->setLayout(MainLayoutAll);
    myDialog->setWindowTitle(QWidget::tr("画布尺寸设置"));
    myDialog->show();

    allRadio->addButton(canvasB);
    allRadio->addButton(modelB);
    allRadio->setId(canvasB,0);
    allRadio->setId(modelB,1);

    connect(btn_ok, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
    connect(btn_cancel, SIGNAL(clicked(bool)), this, SLOT(showNoting()));
}

void MainWindow::saveSpot(){
    centralDraw->saveSpotPoint();
}

void MainWindow::setChange(){
    //设置toolbar上的下拉框
    if(allColor.index[spotSelectedNum]<0){
        spotComboBox->setCurrentIndex(29);
    }
    else{
        spotComboBox->setCurrentIndex(allColor.index[spotSelectedNum]);
    }

    //设置左侧工具箱数值

    //addSpotEdit();
}

void MainWindow::spotSelected(){
    centralDraw->getCtrl(ctrlSize,spotSelectedCtrl);
    spotSelectedNum=centralDraw->getSpotSelectedNum();
    //qDebug("selected-------------------------------%d",ctrlSize);
    if(!ctrlSize){
        spotSelectedNum=centralDraw->getSpotSelectedNum();
    }
    addSpotEdit();
    addBackGroundEdit();
}

void MainWindow::setDrawFlag(){
    if(drawFlag==1){
        drawFlag=0;
        centralDraw->setDrawFlag(drawFlag);
    }
    else{
        drawFlag=1;
        centralDraw->setDrawFlag(drawFlag);
    }
}
void MainWindow::setOPointFlag(){
    if(OPointFlag==1){
        OPointFlag=0;
        centralDraw->setOPointFlag(OPointFlag);
    }
    else{
        OPointFlag=1;
        //qDebug("yi she zhi:%d",OPointFlag);
        centralDraw->setOPointFlag(OPointFlag);
    }
}

void MainWindow::setRadiusFlag(){
    if(radiusFlag==1){
        radiusFlag=0;
        centralDraw->setRadiusFlag(radiusFlag);
    }
    else{
        radiusFlag=1;
        centralDraw->setRadiusFlag(radiusFlag);
    }
}

void MainWindow::setSpotMoveFlag(){
    spotOperation=1;
    centralDraw->setSpotOperationFlag(spotOperation);
}

void MainWindow::setRoationFlag(){
    spotOperation=2;
    centralDraw->setSpotOperationFlag(spotOperation);
}

void MainWindow::setStretchFlag(){
    spotOperation=3;
    centralDraw->setSpotOperationFlag(spotOperation);
}

void MainWindow::showStretch(){
    if(preStr){
        delete preStr;
    }
    if(preLb){
        delete preLb;
        //qDebug("sdfsdf");
    }
    if(preLb1){
        delete preLb1;
    }

    if(!firstShow){//qDebug("ffffffffffffffff");
        str = new QLabel(QObject::tr("缩放："));
        preStr=str;//将这个label添加到状态栏中
        ui->statusBar->addPermanentWidget(str);

        QString stretch = QString("%1   ").arg(1/*centralDraw->getStretch()*/);
        lb = new QLabel(stretch);    //将这个label添加到状态栏中
        preLb=lb;
        QString a("    ");
        lb1 = new QLabel(a);    //将这个label添加到状态栏中
        preLb1=lb1;
        ui->statusBar->addPermanentWidget(lb);
        ui->statusBar->addPermanentWidget(lb1);
        firstShow=1;
    }
    else{
        str = new QLabel(QObject::tr("缩放："));
        preStr=str;//将这个label添加到状态栏中
        ui->statusBar->addPermanentWidget(str);

        QString stretch = QString("%1   ").arg(centralDraw->getStretch());
        lb = new QLabel(stretch);    //将这个label添加到状态栏中
        preLb=lb;
        QString a("    ");
        lb1 = new QLabel(a);    //将这个label添加到状态栏中
        preLb1=lb1;
        ui->statusBar->addPermanentWidget(lb);
        ui->statusBar->addPermanentWidget(lb1);
    }
}


void MainWindow::fiveOpenS(){
    windowScale=centralDraw->getWindowScale();
    if(fabs(windowScale-1)<0.001){
        centralDraw->getFiveImage();
        wumainWin *wm=new wumainWin();
        QString data = QString("%1").arg(modelStretch);
        QString str(QObject::tr("五面贴图，每个方格代表：")+data+QObject::tr("米"));
        //qDebug("mei ge fang ge shi: %f",modelStretch);
        wm->setWindowTitle(str);//QObject::tr(""));
        if(wm->flag==1)
            return;
        wm->showMaximized();
        qDebug("streth streth streth %f",modelStretch);
        wm->show();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前缩放比例必须为1        "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
    }
}

int MainWindow::returnGetSize(){
    return getSize;
}

void MainWindow::rightCpy(){
    centralDraw->rightCpy();
}
void MainWindow::rightCut(){
    //centralDraw->rightCut();
}
void MainWindow::rightPaste(){
    centralDraw->rightPaste();
}
void MainWindow::rightDelete(){
    centralDraw->clearOne();
}

void MainWindow::showSpotEdge(){
    if(ifShowSpotEdge==1){
        ifShowSpotEdge=0;
        centralDraw->showSpotEdge(ifShowSpotEdge);
    }
    else{
        ifShowSpotEdge=1;
        centralDraw->showSpotEdge(ifShowSpotEdge);
    }

}

void MainWindow::startThread(){
    //    threadMessageBox.set
    //    QMessageBox msgBox(this);
    //    msgBox.setWindowTitle(tr("提示"));
    //    msgBox.setText(tr("正在计算斑点生成方案，请稍后"));
    //    msgBox.setMinimumSize(200,100);
    //    msgBox.exec();
    //    QMessageBox msgBox(this);
    //    msgBox.setWindowTitle(tr("提示"));
    //    msgBox.setText(tr("正在计算斑点生成方案，请稍后"));
    //    msgBox.setMinimumSize(200,100);
    //    msgBox.exec();
}

void MainWindow::terminateThread(){
    //mThread->terminate();
    //if(mThread)
    //delete mThread;
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("提示"));
    msgBox.setText(tr("斑点生成成功！        "));
    msgBox.setMinimumSize(200,100);
    //msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox.exec();
}
