
#include "drawwidget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QCoreApplication>

DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{

    //初始化     -----xiaotian
    for(int i=0;i<1000;i++){
        graphArea[i] = 0;
        removeCurrentRow[i] = 0;
        removeCurrentCol[i] = 0;
        removeRow[i] = 0;
        removeCol[i] = 0;
        graphName[i] = "0";
    }
    nbFlag = 0;
    //allColor.flag=11;

    areaGet=1;//斑点该随机到哪个区域赋值
    //setAutoFillBackground(true);
    //setBackgroundMode(NoBackground);
    setPalette(QPalette(Qt::white));

    //yes=1;


    //赋值斑点数组
    for(int i=0;i<maxSize;i++){
        spotNum[i]=0;
    }

    preWidth=width();
    preHeight=height();
    isFirstResize=0;

    //画布初始赋值
    drawX=400;
    drawY=300;
    drawZ=0;

    canvasPath=new QPainterPath;
    drawCanvasFlag=0;
    windowScale=1;
    preWindowScale=1;//在读入一幅图时，可以初始化为1
    //wheelFlag=0;


    drawOk=0;
    markFlag=0;
    drawFlag=0;
    ifCanDraw=1;
    showOPoint=0;
    showDigital = 0;
    radiusFlag=0;
    spotOperation=1;//判断是斑点移动还是缩放还是旋转
    pointNum=0;//清空未画完残斑计数
    spotSelectedNum=0;
    oPointJudge=0;
    oPointMoveFlag=0;
    flag=0;
    ctrlFlag=0;
    ctrlSize=0;

    //斑点连接出颜色处理变量初始化：
    drawOk1=0,drawOk2=0,drawOk3=0,drawOk4=0;


    ifShowSpotEdge=0;//设置开始的时候显示不显示斑点边缘


    //成片选取
    mousePressFlag=0;
    xBegin=0,yBegin=0,xEnd=0,yEnd=0;


    selectedPoint=new(QPointF);
    //初始化斑点颜色
    for(int i=0;i<maxSize;i++){
        allColor.myColor[i].setRgb(255,255,255);
        //        allColor.myColor[i].setRgb(0,0,0);
        allColor.index[i]=29;
    }
    for(int j=0;j<maxSize;j++){
        areaRatio[j]=0;
    }
    backGroundColorIndex=29;
    backGroundColor=QColor(255,255,255);
    spotLineWidth=1;
    spotLineColor=QColor(0,0,255);
    keyPointSize=20;
    keyPointColor=QColor(255,0,255);
    handlePointSize=10;
    //hPointLineWidth=1;
    handlePointColor=QColor(0,0,255);
    markNum=100;//曲率稀疏度
    minResolution=30;//曲率半径

    AutoCADFlag=0;//初始化画布的时候，根据windowscale设置

    path=new(QPainterPath);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    //handlePointSize=10;
    //keyPointSize=8;
    spotColor.setRgb(255,255,255);

    //    widthChange=0;
    //    heightChange=0;
    firstFlag=0;//为了说明是drawCanvas中还没有将    widthChange=0;    heightChange=0;置0
    eventStyle=0;//与父窗口交互的变量，重新设画布的时候可以设为0
    addColorNum=0;

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
    temp.setRgb(255,255,255);iconColor[31]=temp;
    nowPlace=0;
    hasNumBF=0;
    cpyNum=0;
    rightX=0;
    rightY=0;
}


//打开图片
void DrawWidget::openPicture(QString fileName){
    //使用openCV读入图片，在五视图中显示。
    //IplImage* img=cvLoadImage(fileName.toLatin1().data());//加载图像，图像放在Debug文件夹里，这里是相对路径
    //IplImage *pResult=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,3);//创建用于显示的图像，二值图像
    IplImage* img = cvLoadImage(fileName.toLatin1().data(),-1);

    cvNamedWindow("图像显示",CV_WINDOW_AUTOSIZE);
    cvShowImage("图像显示",img);
}

void DrawWidget::addCtrlSpot(){
    list<int>::iterator oP=spotSelectedCtrl.begin();
    int flag=0;
    for(;oP!=spotSelectedCtrl.end();){
        if((*oP)==spotSelectedNum){
            spotSelectedCtrl.erase(oP);
            flag=1;
            ctrlSize--;
            //qDebug("MMMMMMMMM%d",ctrlSize);
            break;
        }
        else if((*oP)>spotSelectedNum){//对斑点进行从大到小排序，如果选中点比当前点小，则插入到当前点前边
            spotSelectedCtrl.insert(oP,spotSelectedNum);
            flag=1;
            ctrlSize++;
            //qDebug("AAAAAAAAA%d",ctrlSize);
            break;
        }
        else{
            oP++;
        }
    }

    if(!flag){
        spotSelectedCtrl.push_back(spotSelectedNum);
        ctrlSize++;
        //qDebug("AAAAAAAAAfter%d",ctrlSize);
    }

    //qDebug("~~~~~%d",ctrlSize);
}
void DrawWidget::addAreaSpot(){
    list<int>::iterator oP=spotSelectedCtrl.begin();
    int flag=0;
    for(;oP!=spotSelectedCtrl.end();){
        if((*oP)==spotSelectedNum){
            //spotSelectedCtrl.erase(oP);
            flag=1;
            //ctrlSize--;
            break;
        }
        else if((*oP)>spotSelectedNum){
            spotSelectedCtrl.insert(oP,spotSelectedNum);
            flag=1;
            ctrlSize++;
            break;
        }
        else{
            oP++;
        }
    }

    if(!flag){
        spotSelectedCtrl.push_back(spotSelectedNum);
        ctrlSize++;
    }
}

void DrawWidget::addImagePath(){
    //    list<QPointF*>::iterator oPTemp = oPointImageAll.begin();
    //    list<QPointF*>::iterator thePointTemp =thePointImageAll.begin();
    //    //list<QPainterPath*>pathImageAll;
    //    pathImageAll.clear();
    //    if(allPath.size()>0){
    //        for(int i=1;i<drawOk+1;i++){
    //            oPointImage.clear();
    //            thePointImage.clear();
    //            for(int j=1;j<spotNum[i]+1;j++){
    //                oPointImage.push_back(*oPTemp);
    //                ++oPTemp;
    //            }
    //            for(int j=1;j<2*spotNum[i]+1;j++){
    //                thePointImage.push_back(*thePointTemp);
    //                ++thePointTemp;
    //            }


    //    pathImage=new(QPainterPath);
    //    list<QPointF*>::iterator oP = oPointImage.begin();
    //    list<QPointF*>::iterator midP =thePointImage.begin();
    //    list<QPointF*>::iterator midPNext;
    //    list<QPointF*>::iterator oPNext;
    //    //midP =thePoint.begin();
    //    pathImage->moveTo((**oP).x(),(**oP).y());
    //    ++oP;
    //    midPNext=++midP;
    //    midP--;
    //    oPNext=++oP;
    //    oP--;
    //    for(;oP!=oPointImage.end();++oPNext){
    //                              pathImage->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
    //                              midP++;
    //                              midP++;
    //                              midPNext=++midP;
    //                              midP--;
    //                              oP++;
    //            }
    //    oP=oPointImage.begin();
    //    pathImage->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
    //    //list<QPainterPath*>pathImageAll;
    //    pathImageAll.push_back(pathImage);
    //        }
    //    }
    //    delete pathImage;
}
void DrawWidget::addSpotOrigin(int drawOk){
    list<QPointF*>::iterator oP = oPoint.begin();
    int count=0;
    spotOriginX[drawOk]=0;
    spotOriginY[drawOk]=0;
    //spotOriginXI[drawOk]=0;
    //spotOriginYI[drawOk]=0;
    for(;oP!=oPoint.end();++oP){
        //oPointAll.push_back(*oP);
        spotOriginX[drawOk]+=(**oP).x();
        spotOriginY[drawOk]+=(**oP).y();
        //qDebug("yyyy:%f",(**oP).y());
        count++;
    }
    //qDebug("ping jun ge shu %d",count);
    spotOriginX[drawOk]=spotOriginX[drawOk]/count;
    spotOriginY[drawOk]=spotOriginY[drawOk]/count;
    //spotOriginXI[drawOk]=spotOriginX[drawOk];
    //spotOriginYI[drawOk]=spotOriginY[drawOk];
    //qDebug("now   :%f %f",spotOriginX[drawOk],spotOriginY[drawOk]);

    //qDebug("origin:%d %d",width()/2,height()/2);
    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;

    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    //qDebug("endy:%d",spotOriginY[drawOk]);
}
void DrawWidget::addSpotPoint(){
    list<QPointF*>::iterator oP = oPoint.begin();
    //QPointF *temp;
    for(;oP!=oPoint.end();++oP){
        //temp=()
        //qDebug("%f  %f",(**oP).x(),(**oP).y());
        (**oP).setX((**oP).x()-spotOriginX[drawOk]);
        (**oP).setY((**oP).y()-spotOriginY[drawOk]);
        oPointAll.push_back(*oP);
        //qDebug("%f  %f",(**oP).x(),(**oP).y());
    }
    //qDebug(" ");
    //qDebug(" ");
    //saveSpotPoint();
    //qDebug("jia ru ge shu :%d",oPoint.size());
    //oPoint.clear();

}
void DrawWidget::addSpecialPath(){//spotMove用
    list<QPointF*>::iterator oP1= oPointAll.begin();
    list<QPointF*>::iterator handleP= handlePointAll.begin();

    list<QPointF*>oPointTempAddSpecial;
    list<QPointF*>thePointTempAdd;

    //找到移动斑点的原点所在区间
    for(int i=1;i<spotSelectedNum;i++){//spotSelectedNum
        for(int j=1;j<spotNum[i]+1;j++){
            ++oP1;
        }
    }

    //将移动斑点的原点压栈到计算链表
    for(int j=1;j<spotNum[spotSelectedNum]+1;j++){
        oPointTempAddSpecial.push_back(*oP1);
        ++oP1;
    }


    //找到移动斑点的控制点所在区间
    for(int i=1;i<spotSelectedNum;i++){
        for(int j=1;j<2*spotNum[i]+1;j++){
            ++handleP;
        }
    }

    //将移动斑点的控制点压栈到计算链表
    for(int j=1;j<2*spotNum[spotSelectedNum]+1;j++){
        thePointTempAdd.push_back(*handleP);
        ++handleP;
    }



    //计算移动斑点的路径
    path=new(QPainterPath);
    oP1 = oPointTempAddSpecial.begin();
    list<QPointF*>::iterator midP =thePointTempAdd.begin();

    list<QPointF*>::iterator midPNext;
    list<QPointF*>::iterator oPNext;

    path->moveTo((**oP1).x(),(**oP1).y());
    ++oP1;

    midPNext=++midP;
    midP--;
    oPNext=++oP1;
    oP1--;


    for(;oP1!=oPointTempAddSpecial.end();++oPNext){
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
        midP++;
        midP++;
        midPNext=++midP;
        midP--;
        oP1++;
    }
    oP1=oPointTempAddSpecial.begin();
    path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());


    //将移动斑点的路径在allPath中替换为移动之后的斑点路径
    list<QPainterPath*>::iterator tempPath;
    QPainterPath *tempPathDelete;

    tempPath=allPath.begin();
    for(int j=1;j<spotSelectedNum;j++)
        tempPath++;
    tempPathDelete=*tempPath;
    allPath.erase(tempPath);
    tempPath=allPath.begin();
    for(int j=1;j<spotSelectedNum;j++)
        tempPath++;
    allPath.insert(tempPath,path);
    oPointTemp.clear();
    delete tempPathDelete;
}

void DrawWidget::addHandlePath(){
    list<QPointF*>::iterator oP = oPointAll.begin();
    list<QPointF*>::iterator oPHandle = handlePointAll.begin();

    oPHandle = handlePointAll.begin();
    oPointTemp.clear();
    thePoint.clear();
    int ok;int count;
    QPainterPath *tempPathDelete;

    //qDebug("%d",spotSelectedNum);

    //移动的是第一个控制点
    if(flag==4){
        count=0;
        ok=0;
        for(int i=1;i<drawOk+1;i++){//先找到控制点所在区段
            for(int j=1;j<2*spotNum[i]+1;j++){
                //qDebug("@@%f    %f",handleA.x(),handleA.y());
                //qDebug("##%f    %f",(**oPHandle).x()/2,(**oPHandle).y()/2);
                //qDebug("$$%d    %d",spotOriginX[spotSelectedNum],spotOriginY[spotSelectedNum]);
                //qDebug("   ");
                if(fabs(handleA.x()-spotOriginX[spotSelectedNum]-(**oPHandle).x())<0.001&&fabs(handleA.y()-spotOriginY[spotSelectedNum]-(**oPHandle).y())<0.001){
                    ok=1;
                    //qDebug("sssssssss");
                    count=i;
                    break;
                }
                oPHandle++;
            }
            if(ok)
                break;
        }

        //遍历原点到找到的区段
        oP = oPointAll.begin();
        for(int i=1;i<count;i++)
            for(int j=1;j<spotNum[i]+1;j++){
                oP++;
            }

        //遍历控制点到找到的区段
        oPHandle = handlePointAll.begin();
        for(int i=1;i<count;i++)
            for(int j=1;j<2*spotNum[i]+1;j++){
                oPHandle++;
            }

        //转移原点到计算路径的链表
        //qDebug("%d  %d",count,spotNum[count]);
        for(int j=1;j<spotNum[count]+1;j++){
            oPointTemp.push_back(*oP);
            ++oP;
        }
        //转移控制点到计算路径的链表
        //qDebug("%d  %d",count,spotNum[count]);
        for(int j=1;j<2*spotNum[count]+1;j++){
            thePoint.push_back(*oPHandle);
            ++oPHandle;
        }

        //计算路径
        path=new(QPainterPath);
        list<QPointF*>::iterator midP =thePoint.begin();
        oP = oPointTemp.begin();
        list<QPointF*>::iterator midPNext;
        list<QPointF*>::iterator oPNext;
        path->moveTo((**oP).x(),(**oP).y());
        ++oP;


        midPNext=++midP;
        midP--;
        oPNext=++oP;
        oP--;

        for(;oP!=oPointTemp.end();++oPNext){
            path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
            midP++;
            midP++;
            midPNext=++midP;
            midP--;
            oP++;
        }
        oP=oPointTemp.begin();
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());

        list<QPainterPath*>::iterator tempPath;

        tempPath=allPath.begin();
        for(int j=1;j<count;j++)
            tempPath++;
        tempPathDelete=*tempPath;
        allPath.erase(tempPath);

        tempPath=allPath.begin();
        for(int j=1;j<count;j++)
            tempPath++;
        allPath.insert(tempPath,path);
        delete tempPathDelete;
        return;
    }




    //移动的是第二个控制点，同上
    if(flag==5){
        count=0;
        ok=0;

        for(int i=1;i<drawOk+1;i++){//先找到控制点所在区段
            for(int j=1;j<2*spotNum[i]+1;j++){
                if(fabs(handleB.x()-spotOriginX[spotSelectedNum]-(**oPHandle).x())<0.001&&fabs(handleB.y()-spotOriginY[spotSelectedNum]-(**oPHandle).y())<0.001){
                    ok=1;
                    count=i;
                    break;
                }
                oPHandle++;
            }
            if(ok)
                break;
        }


        oP = oPointAll.begin();
        for(int i=1;i<count;i++)
            for(int j=1;j<spotNum[i]+1;j++){
                oP++;
            }

        oPHandle = handlePointAll.begin();
        for(int i=1;i<count;i++)
            for(int j=1;j<2*spotNum[i]+1;j++){
                oPHandle++;
            }

        for(int j=1;j<spotNum[count]+1;j++){
            oPointTemp.push_back(*oP);
            ++oP;
        }

        for(int j=1;j<2*spotNum[count]+1;j++){
            thePoint.push_back(*oPHandle);
            ++oPHandle;
        }


        path=new(QPainterPath);
        oP = oPointTemp.begin();
        list<QPointF*>::iterator midP =thePoint.begin();
        oP = oPointTemp.begin();
        midP =thePoint.begin();
        list<QPointF*>::iterator midPNext;
        list<QPointF*>::iterator oPNext;
        path->moveTo((**oP).x(),(**oP).y());
        ++oP;


        midPNext=++midP;
        midP--;
        oPNext=++oP;
        oP--;

        for(;oP!=oPointTemp.end();++oPNext){
            path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
            midP++;
            midP++;
            midPNext=++midP;
            midP--;
            oP++;
        }
        oP=oPointTemp.begin();
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());

        list<QPainterPath*>::iterator tempPath;
        tempPath=allPath.begin();
        for(int j=1;j<count;j++)
            tempPath++;
        tempPathDelete=*tempPath;
        allPath.erase(tempPath);
        tempPath=allPath.begin();
        for(int j=1;j<count;j++)
            tempPath++;
        allPath.insert(tempPath,path);
        delete tempPathDelete;
        return;
    }

    //清理工作
    //thePoint.clear();
    //oPointTemp.clear();
}
void DrawWidget::areaSelected(){

    list<QPainterPath*>::iterator temp = allPath.end();
    temp--;

    int count=allPath.size();

    float x,y;
    while(count>0){
        x=spotOriginX[count]*cos(rotation[count]/180*PI)*stretch[count]/windowScale-spotOriginY[count]*sin(rotation[count]/180*PI)*stretch[count]/windowScale;
        y=spotOriginX[count]*sin(rotation[count]/180*PI)*stretch[count]/windowScale+spotOriginY[count]*cos(rotation[count]/180*PI)*stretch[count]/windowScale;
        //        qDebug("xxxxxxxxxxxxx%f   %f",x,y);

        //        x1=(xBegin-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(yBegin-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        //        y1=(xBegin-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(yBegin-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

        //        x2=(xEnd-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(yEnd-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        //        y2=(xEnd-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(yEnd-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];
        QRectF tempRect(xBegin,yBegin,xEnd-xBegin,yEnd-yBegin);
        //QPointF tempPoint(spotOriginX[count],spotOriginY[count]);
        if(tempRect.contains(spotOriginX[count],spotOriginY[count])){
            //selectedPoint->setX(currentPoint1->x());
            //selectedPoint->setY(currentPoint1->y());
            flag=6;
            markFlag=4;
            spotSelectedNum=count;
            //            qDebug("zuo shang:%d  %d",xBegin,yBegin);
            //            qDebug("you   xia:%d  %d",xEnd,yEnd);
            //            qDebug("oo      o:%f  %f",x,y);
            //            qDebug("yuanlai : %f   %f",spotOriginX[count],spotOriginY[count]);
            //            qDebug("xian zai xuan zhong:%d",count);
            //if(ctrlFlag){
            //addCtrlSpot();
            addAreaSpot();
            //}
            eventStyle=2;
            emit spotSelected_S();
            //return 1;
        }
        count--;
        temp--;
    }
    cout<<"选中"<<endl;
}

void DrawWidget::backWardF(){
    if(nowPlace<2){
        return;
    }
    else{
        nowPlace--;
        //qDebug("backWardF    %d",nowPlace);
        readStation();
    }
}
void DrawWidget::forWardF(){
    if(hasNumBF<2){
        return;
    }
    else if(nowPlace<hasNumBF){
        nowPlace++;
        //qDebug("forWardF     %d",nowPlace);
        readStation();
    }
}
void DrawWidget::saveStation(){
    nowPlace++;
    if(nowPlace>10){
        for(int i=2;i<11;i++){
            backForward[i-1]=backForward[i];
        }
        nowPlace--;
    }

    hasNumBF=nowPlace;



    backForward[hasNumBF].setDrawOk(drawOk);
    backForward[hasNumBF].setSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    backForward[hasNumBF].setCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    backForward[hasNumBF].setWidHei(width(),height());
    backForward[hasNumBF].setSpotNum(spotNum);
    backForward[hasNumBF].setStretch(stretch);
    backForward[hasNumBF].setRotation(rotation);
    backForward[hasNumBF].setOpointAll(oPointAll);
    backForward[hasNumBF].setHandlePointAll(handlePointAll);
    backForward[hasNumBF].setAllColorIndex(allColor.index,backGroundColorIndex);
    backForward[hasNumBF].setAllPath(allPath);
    backForward[hasNumBF].setCanvas(drawX,drawY,drawZ);
    //qDebug("~~~~~~~~~~~~~~~~~~~~bao cun z shi:%f",drawZ);
    backForward[hasNumBF].setWindowScale(windowScale);

}
void DrawWidget::readStation(){
    //qDebug("nowPlace:%d",nowPlace);
    clear();
    float tempWidth=0,tempHeight=0;
    //qDebug(".......%d",nowPlace);
    drawOk=backForward[nowPlace].getDrawOk();
    backForward[nowPlace].getWidHei(tempWidth,tempHeight);
    backForward[nowPlace].getSpotNum(spotNum);
    backForward[nowPlace].getSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    backForward[nowPlace].getCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    backForward[nowPlace].getStretch(stretch);
    backForward[nowPlace].getRotation(rotation);
    backForward[nowPlace].getOpointAll(oPointAll);
    //qDebug("neibu&&&,,,,,,:%d",handlePointAll.size());
    backForward[nowPlace].getHandlePointAll(handlePointAll);
    backForward[nowPlace].getAllColorIndex(allColor.index,backGroundColorIndex);
    backForward[nowPlace].getAllPath(allPath);
    backForward[nowPlace].getBackGroundColor(backGroundColor);
    float x,y,z;
    backForward[nowPlace].getCanvas(x,y,z);
    //qDebug("***:  %f  %f  %f",x,y,z);
    backForward[nowPlace].getWindowScale(windowScale);
    //qDebug("neibu,,,,,,:%d",handlePointAll.size());
    midWidth=tempWidth/2;
    midHeight=tempHeight/2;
    //通过index初始化颜色
    for(int i=1;i<drawOk+1;i++){
        allColor.myColor[i]=iconColor[allColor.index[i]+1];
    }
    backGroundColor=iconColor[backGroundColorIndex+1];
    if(fabs(z)<0.001){
        drawX=x;drawY=y;drawZ=0;
        drawCanvasFlag=1;
        AutoCADFlag=0;
    }
    else{
        drawX=x;drawY=y;drawZ=z;
        //qDebug("ssssssss");
        AutoCADFlag=1;
    }
    this->setGeometry(0,0,tempWidth,tempHeight);
    this->update();
}

void DrawWidget::caculateCanvasPath(){
    list<QPointF*>::iterator oP= oPointAll.begin();
    list<QPointF*>::iterator handleP= handlePointAll.begin();



    //找到移动斑点的原点所在区间
    for(int count=1;count<drawOk+1;count++){
        list<QPointF*>oPointTempAddSpecial;
        list<QPointF*>thePointTempAdd;

        //将移动斑点的原点压栈到计算链表
        for(int j=1;j<spotNum[count]+1;j++){
            oPointTempAddSpecial.push_back(*oP);
            ++oP;
        }


        //将移动斑点的控制点压栈到计算链表
        for(int j=1;j<2*spotNum[count]+1;j++){
            thePointTempAdd.push_back(*handleP);
            ++handleP;
        }



        //计算移动斑点的路径
        path=new(QPainterPath);
        list<QPointF*>::iterator oP1 = oPointTempAddSpecial.begin();
        list<QPointF*>::iterator midP =thePointTempAdd.begin();

        list<QPointF*>::iterator midPNext;
        list<QPointF*>::iterator oPNext;

        path->moveTo((**oP1).x(),(**oP1).y());
        ++oP1;

        midPNext=++midP;
        midP--;
        oPNext=++oP1;
        oP1--;


        for(;oP1!=oPointTempAddSpecial.end();++oPNext){
            path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
            midP++;
            midP++;
            midPNext=++midP;
            midP--;
            oP1++;
        }
        oP1=oPointTempAddSpecial.begin();
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());


        //将移动斑点的路径在allPath中替换为移动之后的斑点路径
        allPath.push_back(path);
    }

}

//添加一个flag      --------xiaotian
void DrawWidget::caculateOneCurve2(int uflag){
    path=new(QPainterPath);
    list<QPointF*>midM;
    list<QPointF*>midPoint;
    list<QPointF*>tranCoo;
    list<QPointF*>thePoint;

    midPoint.clear();
    midM.clear();
    tranCoo.clear();
    thePoint.clear();
    use.getMid(oPoint,midPoint,midM);
    use.getTraCoo(oPoint,midM,tranCoo);
    use.getThePoint(midPoint,tranCoo,thePoint);

    //先把控制点进行压栈
    list<QPointF*>::iterator oP1 = thePoint.begin();
    for(;oP1!=thePoint.end();++oP1){
        handlePointAll.push_back(*oP1);
    }

    //计算出刚画出斑点的path
    list<QPointF*>::iterator oP;
    oP = oPoint.begin();
    list<QPointF*>::iterator midP =thePoint.begin();
    list<QPointF*>::iterator midPNext;
    list<QPointF*>::iterator oPNext;



    path->moveTo((**oP).x(),(**oP).y());

    ++oP;

    midPNext=++midP;
    midP--;
    oPNext=++oP;
    oP--;

    for(;oP!=oPoint.end();++oPNext){
        //---------xiaotian  cubicTo  改成  lineTo
        //path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
        path->lineTo((**oP).x(),(**oP).y());
        midP++;
        midP++;
        midPNext=++midP;
        midP--;
        oP++;
    }
    oP=oPoint.begin();

    //---------xiaotian  cubicTo  改成  lineTo
    //path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
    path->lineTo((**oP).x(),(**oP).y());

    if(!uflag){
        allPath.push_back(path);
        forAutoSpotP[drawOk]=path;
    }
    //--------------xiaotian

    //qDebug("push");
    oPoint.clear();
    thePoint.clear();
    ///////////////////////////////////////清理内存
    list<QPointF*>::iterator tempDelete;
    QPointF *tempDeletePoint;

    tempDelete=midPoint.begin();
    for(;tempDelete!=midPoint.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    midPoint.clear();

    tempDelete=midM.begin();
    for(;tempDelete!=midM.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    midM.clear();


    tempDelete=tranCoo.begin();
    for(;tempDelete!=tranCoo.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    tranCoo.clear();
}

void DrawWidget::caculateOneCurve(){
    path=new(QPainterPath);
    list<QPointF*>midM;
    list<QPointF*>midPoint;
    list<QPointF*>tranCoo;
    list<QPointF*>thePoint;

    midPoint.clear();
    midM.clear();
    tranCoo.clear();
    thePoint.clear();
    use.getMid(oPoint,midPoint,midM);
    use.getTraCoo(oPoint,midM,tranCoo);
    use.getThePoint(midPoint,tranCoo,thePoint);

    //先把控制点进行压栈
    list<QPointF*>::iterator oP1 = thePoint.begin();
    for(;oP1!=thePoint.end();++oP1){
        handlePointAll.push_back(*oP1);
    }

    //计算出刚画出斑点的path
    list<QPointF*>::iterator oP;
    oP = oPoint.begin();
    list<QPointF*>::iterator midP =thePoint.begin();
    list<QPointF*>::iterator midPNext;
    list<QPointF*>::iterator oPNext;



    path->moveTo((**oP).x(),(**oP).y());

    ++oP;

    midPNext=++midP;
    midP--;
    oPNext=++oP;
    oP--;






    for(;oP!=oPoint.end();++oPNext){
        //---------xiaotian  cubicTo  改成  lineTo
        if(saveGet.digitalFlag == 1){
            path->lineTo((**oP).x(),(**oP).y());
        }else{
            path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
        }
        //path->lineTo((**oP).x(),(**oP).y());
        //cout<<(**oP).x()/4<<' '<<(**oP).y()/4<<endl;
        midP++;
        midP++;
        midPNext=++midP;
        midP--;
        oP++;
    }
    oP=oPoint.begin();

    //---------xiaotian  cubicTo  改成  lineTo
    if(saveGet.digitalFlag == 1){
        path->lineTo((**oP).x(),(**oP).y());
    }else{
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
    }


    allPath.push_back(path);
    //---------------xiaotian
    // QPainterPath *pathCenter=new(QPainterPath);
    // pathCenter->addRect(spotOriginX[drawOk],spotOriginY[drawOk],10,10);
    //allPath.push_back(pathCenter);


    forAutoSpotP[drawOk]=path;
    //--------------xiaotian
    //forAutoSpotP[++drawOk] = pathCenter;
    //qDebug("push");
    oPoint.clear();
    thePoint.clear();
    ///////////////////////////////////////清理内存
    list<QPointF*>::iterator tempDelete;
    QPointF *tempDeletePoint;

    tempDelete=midPoint.begin();
    for(;tempDelete!=midPoint.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    midPoint.clear();

    tempDelete=midM.begin();
    for(;tempDelete!=midM.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    midM.clear();


    tempDelete=tranCoo.begin();
    for(;tempDelete!=tranCoo.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    tranCoo.clear();
}
void DrawWidget::caculateAreaRatio(){
    list<QPainterPath*>::iterator temp = allPath.begin();
    int count;
    QPointF tempPoint;
    float x,y;

    for(int j=0;j<maxSize;j++){
        areaRatio[j]=0;
    }

    if(!AutoCADFlag){
        for(float i=midWidth-0.5*canvasX+canvasX/50;i<midWidth+0.5*canvasX+0.001;i+=canvasX/50){
            for(float j=midHeight-0.5*canvasY+canvasY/50;j<midHeight+0.5*canvasY+0.001;j+=canvasY/50){
                temp = allPath.begin();
                count=1;
                for(;temp!=allPath.end();++temp){
                    ////真实的点到某个斑点的坐标系
                    x=(i-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];
                    tempPoint.setX(x);
                    tempPoint.setY(y);
                    if((*temp)->contains(tempPoint)){
                        areaRatio[count]+=0.04;
                        break;
                    }
                    count++;
                }
            }
        }
    }
    else{
        float area1,area2,area3;
        area1=drawX*drawZ/(2*drawX*drawZ+2*drawY*drawZ+drawX*drawY)*100;
        area2=(drawY*drawZ+drawX*drawY+drawY*drawZ)/(2*drawX*drawZ+2*drawY*drawZ+drawX*drawY)*100;
        area3=area1;
        //qDebug("%f",area1);
        //第一部分面积
        for(float i=midWidth-drawX/2+drawX/50;i<midWidth+drawX/2+0.001;i+=drawX/50){
            for(float j=midHeight-0.5*drawY-drawZ+drawZ/50;j<midHeight-0.5*drawY+0.001;j+=drawZ/50){
                temp = allPath.begin();
                count=1;
                for(;temp!=allPath.end();++temp){
                    x=(i-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];
                    tempPoint.setX(x);
                    tempPoint.setY(y);
                    if((*temp)->contains(tempPoint)){
                        //qDebug("ssss");
                        areaRatio[count]+=area1/2500;
                        break;
                    }
                    count++;
                }
            }
        }
        //第三部分面积
        for(float i=midWidth-drawX/2;i<midWidth+drawX/2+0.001;i+=drawX/50){
            for(float j=midHeight+0.5*drawY+drawZ/50;j<midHeight+0.5*drawY+drawZ+0.001;j+=drawZ/50){
                temp = allPath.begin();
                count=1;
                for(;temp!=allPath.end();++temp){
                    x=(i-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];
                    tempPoint.setX(x);
                    tempPoint.setY(y);
                    if((*temp)->contains(tempPoint)){
                        areaRatio[count]+=area3/2500;//qDebug("ssss");
                        break;
                    }
                    count++;
                }
            }
        }
        //第二部分面积
        for(float i=midWidth-drawX/2-drawZ+(drawX+2*drawZ)/50;i<midWidth+drawX/2+drawZ+0.001;i+=(drawX+drawZ*2)/50){
            for(float j=midHeight-0.5*drawY+drawY/50;j<midHeight+0.5*drawY+0.001;j+=drawY/50){
                temp = allPath.begin();
                count=1;
                for(;temp!=allPath.end();++temp){
                    x=(i-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];
                    tempPoint.setX(x);
                    tempPoint.setY(y);
                    if((*temp)->contains(tempPoint)){
                        areaRatio[count]+=area2/2500;//qDebug("ssss");
                        break;
                    }
                    count++;
                }
            }
        }
    }

    for(int a=1;a<drawOk+1;a++){
        if(areaRatio[a]!=0);
        //qDebug("di%dge:  %f",a,areaRatio[a]);
    }
    //qDebug(" ");
}
void DrawWidget::clear(){
    //在清除所有之前，保存起来，以便回退
    //saveStation();
    saveGet.digitalFlag = 0;
    cpyNum=0;
    widthChange=0;
    heightChange=0;
    preWidth=width();
    preHeight=height();
    isFirstResize=0;
    flag=0;
    markFlag=0;
    spotOperation=1;
    drawOk=0;
    oPoint.clear();
    oPointImage.clear();
    thePointImage.clear();
    oPointImageAll.clear();
    midPoint.clear();
    midM.clear();
    tranCoo.clear();
    thePoint.clear();
    thePointImageAll.clear();
    path=new(QPainterPath);
    spotColor.setRgb(255,255,255);;
    pointNum=0;
    oPointAll.clear();
    allPath.clear();
    oPointTemp.clear();
    thePointTempDraw.clear();
    thePointTemp.clear();
    spotSelectedNum=0;
    ctrlSize=0;
    spotSelectedCtrl.clear();
    oPointJudge=0;
    oPointMoveFlag=0;
    handlePointAll.clear();
    for(int i=0;i<maxSize;i++){
        allColor.myColor[i].setRgb(255,255,255);
        allColor.index[i]=29;
    }
    for(int j=0;j<maxSize;j++){
        areaRatio[j]=0;
    }
    firstFlag=0;
    //wheelFlag=0;
    eventStyle=0;
    backGroundColor=QColor(255,255,255);;
    spotLineWidth=2;
    spotLineColor=QColor(0,0,255);
    //keyPointSize=8;
    keyPointColor=QColor(255,0,255);;
    //handlePointSize=10;
    handlePointColor=QColor(0,0,255);
    markNum=100;
    minResolution=30;
    drawOk1=0,drawOk2=0,drawOk3=0,drawOk4=0;
    //radiusFlag=0;


    //shuma micai
    showDigital = false;
    emit ChildWindowEvent();
}
void DrawWidget::clearOne(){
    deleteSpot();
}

void DrawWidget::changeSpotOrign(){
    float tempX;
    float tempY;
    //qDebug("%f  %f",spotOriginPOX[drawOk],spotOriginPOY[drawOk]);
    //qDebug("%f  %f",spotOriginOX[drawOk],spotOriginOY[drawOk]);
    //qDebug("  ");
    //qDebug("bbb%f  %f",tempX,tempY);
    //qDebug("%d %d",width()/2,height()/2);
    for(int i=1;i<drawOk+1;i++){
        tempX=spotOriginOX[i]-spotOriginPOX[i];
        tempY=spotOriginOY[i]-spotOriginPOY[i];
        spotOriginPOX[i]=spotOriginOX[i];
        spotOriginPOX[i]=spotOriginOX[i];
        spotOriginX[i]+=tempX;
        spotOriginY[i]+=tempY;
        //spotOriginXI[i]+=tempX;
        //spotOriginYI[i]+=tempY;
    }
    //spotOriginX[drawOk]=spotOriginOX[drawOk]+midWidth;
    //spotOriginY[drawOk]=spotOriginOX[drawOk]+midHeight;
}

void DrawWidget::ChildWindowEventSlot(){
    delete cWindow;
}
int DrawWidget::collisonDetection(int num,float saveP[300][2]){
    QPointF tempPoint;
    int n;
    //for(int i=0;i<180;i+=18){
    int i=0;
    for(n=1;n<num+1;n++){//对得到的斑点的所有点做检测
        float x1=saveP[n][0]*cos(i/180*PI)*windowScale/4-saveP[n][1]*sin(i/180*PI)*windowScale/4;
        float y1=saveP[n][0]*sin(i/180*PI)*windowScale/4+saveP[n][1]*cos(i/180*PI)*windowScale/4;

        x1+=+spotOriginX[drawOk];
        y1+=+spotOriginY[drawOk];
        //qDebug("x:%f  ,  y:%f",x1,y1);

        for(int j=1;j<drawOk;j++){
            float x=(x1-spotOriginX[j])*cos(-rotation[j]/180*PI)/stretch[j]-(y1-spotOriginY[j])*sin(-rotation[j]/180*PI)/stretch[j];
            float y=(x1-spotOriginX[j])*sin(-rotation[j]/180*PI)/stretch[j]+(y1-spotOriginY[j])*cos(-rotation[j]/180*PI)/stretch[j];
            //qDebug("x:%f  ,  y:%f",x,y);
            tempPoint.setX(x);
            tempPoint.setY(y);
            if(forAutoSpotP[j]->contains(tempPoint)){
                //break;
                //qDebug("被第%d个斑点包含",j);
                return 0;
            }
        }
    }
    //if(n==num+1){
    //qDebug("chenggong了");
    return 1;
    //}
    //}
    return 0;
}

void DrawWidget::deleteSpot(){
    if(ctrlSize){
        saveStation();
        int tempNum;
        list<int>::iterator oPNum=spotSelectedCtrl.begin();
        list<QPointF*>::iterator oP;
        list<QPointF*>::iterator handleP;
        for(int ii=1;ii<ctrlSize+1;ii++,oPNum++){
            tempNum=*oPNum;
            oP= oPointAll.begin();
            handleP= handlePointAll.begin();

            for(int j=1;j<spotNum[tempNum-ii+1]+1;j++){
                oP= oPointAll.begin();
                for(int i=1;i<tempNum-ii+1;i++){//spotSelectedNum
                    for(int j=1;j<spotNum[i]+1;j++){
                        ++oP;
                    }
                }
                oPointAll.erase(oP);
            }
            //将移动斑点的原点压栈到计算链表



            //找到移动斑点的控制点所在区间
            for(int j=1;j<2*spotNum[tempNum-ii+1]+1;j++){
                handleP= handlePointAll.begin();
                for(int i=1;i<tempNum-ii+1;i++){
                    for(int j=1;j<2*spotNum[i]+1;j++){
                        ++handleP;
                    }
                }
                handlePointAll.erase(handleP);
            }


            //删除路径信息
            list<QPainterPath*>::iterator tempPath;
            QPainterPath *tempPathDelete;
            tempPath=allPath.begin();
            for(int j=1;j<tempNum-ii+1;j++)
                tempPath++;
            tempPathDelete=*tempPath;
            allPath.erase(tempPath);
            //delete tempPathDelete;


            //删除spot的其它信息
            for(int i=tempNum-ii+1;i<drawOk;i++){
                spotNum[i]=spotNum[i+1];
                stretch[i]=stretch[i+1];
                rotation[i]=rotation[i+1];
                allColor.myColor[i]=allColor.myColor[i+1];
                allColor.index[i]=allColor.index[i+1];
                spotOriginX[i]=spotOriginX[i+1];
                spotOriginY[i]=spotOriginY[i+1];
                spotOriginOX[i]=spotOriginOX[i+1];
                spotOriginOY[i]=spotOriginOY[i+1];
                spotOriginPOX[i]=spotOriginPOX[i+1];
                spotOriginPOY[i]=spotOriginPOY[i+1];
            }
            spotSelectedNum=0;
            markFlag=0;
            drawOk--;
            //oP++;
        }
        ctrlSize=0;
        spotSelectedCtrl.clear();
        this->update();
    }
    else if(spotSelectedNum){
        saveStation();
        //颜色，index
        //找到移动斑点的原点所在区间
        list<QPointF*>::iterator oP= oPointAll.begin();
        list<QPointF*>::iterator handleP= handlePointAll.begin();
        for(int j=1;j<spotNum[spotSelectedNum]+1;j++){
            oP= oPointAll.begin();
            for(int i=1;i<spotSelectedNum;i++){//spotSelectedNum
                for(int j=1;j<spotNum[i]+1;j++){
                    ++oP;
                }
            }
            oPointAll.erase(oP);
        }
        //将移动斑点的原点压栈到计算链表



        //找到移动斑点的控制点所在区间
        for(int j=1;j<2*spotNum[spotSelectedNum]+1;j++){
            handleP= handlePointAll.begin();
            for(int i=1;i<spotSelectedNum;i++){
                for(int j=1;j<2*spotNum[i]+1;j++){
                    ++handleP;
                }
            }
            handlePointAll.erase(handleP);
        }


        //删除路径信息
        list<QPainterPath*>::iterator tempPath;
        QPainterPath *tempPathDelete;
        tempPath=allPath.begin();
        for(int j=1;j<spotSelectedNum;j++)
            tempPath++;
        tempPathDelete=*tempPath;
        allPath.erase(tempPath);
        //delete tempPathDelete;


        //删除spot的其它信息
        for(int i=spotSelectedNum;i<drawOk;i++){
            spotNum[i]=spotNum[i+1];
            stretch[i]=stretch[i+1];
            rotation[i]=rotation[i+1];
            allColor.myColor[i]=allColor.myColor[i+1];
            allColor.index[i]=allColor.index[i+1];
            spotOriginX[i]=spotOriginX[i+1];
            spotOriginY[i]=spotOriginY[i+1];
            //spotOriginXI[i]=spotOriginX[i+1];
            //spotOriginYI[i]=spotOriginY[i+1];
            spotOriginOX[i]=spotOriginOX[i+1];
            spotOriginOY[i]=spotOriginOY[i+1];
            spotOriginPOX[i]=spotOriginPOX[i+1];
            spotOriginPOY[i]=spotOriginPOY[i+1];
        }
        spotSelectedNum=0;
        markFlag=0;
        drawOk--;
        this->update();
    }
}

void DrawWidget::drawOPoint(QPainter &p){
    //p.translate(spotOriginX[drawOk],spotOriginY[drawOk]);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::NoBrush);
    p.setPen(QPen(keyPointColor,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    //p.setPen(QPen(QColor(255,0,255),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    list<QPointF*>::iterator oP;
    list<QPointF*>::iterator oPAll;

    if(oPoint.size()>0){
        oP = oPoint.begin();
        for(;oP!=oPoint.end();++oP){
            //p.drawEllipse((**oP).x()-keyPointSize/2,(**oP).y()-keyPointSize/2,keyPointSize,keyPointSize);
            if(markFlag==1&&fabs((**oP).x()-selectedPoint->x())<0.001&&fabs((**oP).y()-selectedPoint->y())<0.001){
                p.setBrush(QBrush(QColor(255,0,0),Qt::Dense4Pattern));
                p.drawEllipse(selectedPoint->x()-25,selectedPoint->y()-25,50,50);
                p.drawEllipse((**oP).x()-keyPointSize/2,(**oP).y()-keyPointSize/2,keyPointSize,keyPointSize);
                //qDebug("-------sssssssssssss");
                p.setBrush(Qt::NoBrush);
            }
            else{
                p.drawEllipse((**oP).x()-keyPointSize/2,(**oP).y()-keyPointSize/2,keyPointSize,keyPointSize);
            }
        }
    }

    if(drawOk){
        oPAll=oPointAll.begin();
        int t=1;
        int n=1;
        for(;t<drawOk+1;t++){
            p.translate(spotOriginX[t],spotOriginY[t]);
            p.rotate(rotation[t]);
            p.scale(stretch[t],stretch[t]);
            //         p.translate(spotOriginX[t],spotOriginY[t]);
            //         p.rotate(90);
            //         p.scale(0.5,0.5);
            n=1;
            for(;n<spotNum[t]+1;n++){
                //qDebug("%f   %f",(**oPAll).x(),(**oPAll).y());
                //qDebug("--  %f   %f",spotOriginX[spotSelectedNum],spotOriginY[spotSelectedNum]);
                //qDebug("cha1  %f   %f",(**oPAll).x()-(selectedPoint->x()-spotOriginX[spotSelectedNum]),(**oPAll).y()-(selectedPoint->y()-spotOriginY[spotSelectedNum]));
                if(markFlag==1&&fabs((**oPAll).x()-(selectedPoint->x()-spotOriginX[spotSelectedNum]))<0.001&&fabs((**oPAll).y()-(selectedPoint->y()-spotOriginY[spotSelectedNum]))<0.001&&oPointJudge==t){
                    p.setBrush(QBrush(QColor(255,0,0)));
                    p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
                    //p.drawEllipse(x-15,y-15,30,30);
                    //p.drawEllipse(x1-5,y1-5,10,10);
                    //qDebug("-------sssssssssssss");
                    p.setBrush(Qt::NoBrush);
                }
                else{
                    p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
                }
                oPAll++;
            }

            //        p.scale(0.5,0.5);
            //        p.setBrush(QBrush(QColor(255,0,0)));
            //        p.drawEllipse(200,200,30,30);
            //        p.setBrush(Qt::NoBrush);
            //        p.scale(2,2);
            p.scale(1/stretch[t],1/stretch[t]);
            p.rotate(-rotation[t]);
            p.translate(-spotOriginX[t],-spotOriginY[t]);
            //        p.translate(spotOriginX[t],spotOriginY[t]);
            //        p.rotate(-90);
            //        p.scale(2,2);
        }

        //    for(;oPAll!=oPointAll.end();++oPAll){
        //       if(markFlag==1&&(**oPAll).x()==selectedPoint->x()&&(**oPAll).y()==selectedPoint->y()){
        //                      p.setBrush(QBrush(QColor(255,0,255),Qt::Dense4Pattern));
        //                      p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
        //                      p.setBrush(Qt::NoBrush);
        //                  }
        //       else{
        //                      p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
        //                  }
        //        }
    }
    //p.translate(-spotOriginX[drawOk],-spotOriginY[drawOk]);
}

void DrawWidget::drawScaleLine(QPainter &p){
    p.setPen(Qt::NoPen);
    QPen tempPen;
    tempPen.setColor(Qt::black);
    p.setPen(tempPen);
    QFont font;
    if(windowScale<0.25)
        font.setPointSize(6);
    else
        font.setPointSize(8);
    p.setFont(font);


    //int temp=showArea->viewport()->width();
    //qDebug("%d",temp);

    p.drawLine(QPointF(0,20),QPointF(this->width(),20));

    //横向标尺
    float length=0;int count=0;
    while(length<this->width()){
        //qDebug("sssssssssssssssss");
        p.drawLine(QPointF(length+4,14),QPointF(length+4,20));
        QRectF rect1(length,0,40,40);
        QString CM1 = QString("%1").arg(count);
        if(windowScale<0.25){
            if(count%2<0.001)
                p.drawText(rect1,Qt::AlignLeft,CM1);
        }
        else{
            p.drawText(rect1,Qt::AlignLeft,CM1);
        }
        if(windowScale>1.414){
            for(int i=1;i<5;i++){
                QRectF rect(length+20*i*windowScale,0,40,40);
                float temp=0.2*i+count;
                QString CM2 = QString("%1").arg(temp);
                p.drawText(rect,Qt::AlignLeft,CM2);
                p.drawLine(QPointF(length+4+20*i*windowScale,14),QPointF(length+4+20*i*windowScale,20));
            }
        }
        length+=100*windowScale;
        count++;
    }

    //纵向标尺
    p.drawLine(QPointF(8,0),QPointF(8,this->height()));
    float length1=0;float count1=0;
    while(length1<this->height()){
        p.drawLine(QPointF(0,length1+4),QPointF(8,length1+4));

        QRectF rect11(10,length1-3,40,40);
        QString CM11 = QString("%1").arg(count1);
        p.drawText(rect11,Qt::AlignLeft,CM11);
        if(windowScale>1.414){
            for(int i=1;i<5;i++){
                QRectF rect1(10,length1+20*i*windowScale-3,40,40);
                float temp1=0.2*i+count1;
                QString CM21 = QString("%1").arg(temp1);
                p.drawText(rect1,Qt::AlignLeft,CM21);
                p.drawLine(QPointF(0,length1+4+20*i*windowScale),QPointF(8,length1+4+20*i*windowScale));
            }
        }
        length1+=100*windowScale;
        count1++;
    }
}

void DrawWidget::drawHandlePoint(QPainter &p){
    list<QPointF*>::iterator oP = handlePointAll.begin();
    list<QPointF*>::iterator temp;
    list<QPointF*>::iterator tempN;



    //    list<QPointF*>::iterator temp11;
    //    temp11=handlePointAll.begin();
    //    p.translate(spotOriginX[1],spotOriginY[1]);
    //    for(;temp11!=handlePointAll.end();temp11++){
    //        p.drawEllipse(**temp11,10,10);
    //    }
    //    p.translate(-spotOriginX[1],-spotOriginY[1]);



    for(int i=1;i<drawOk+1;i++){
        thePointTempDraw.clear();
        for(int j=1;j<2*spotNum[i]+1;j++){//分区段遍历控制点，并将每一段放到判断链表中，去做判断
            thePointTempDraw.push_back(*oP);
            ++oP;
        }

        p.translate(spotOriginX[i],spotOriginY[i]);
        p.rotate(rotation[i]);
        p.scale(stretch[i],stretch[i]);
        //        p.translate(spotOriginX[t],spotOriginY[t]);
        //        p.rotate(90);
        //        p.scale(0.5,0.5);

        temp =thePointTempDraw.begin();
        ++temp;
        tempN =++temp;
        temp--;

        p.setBrush(Qt::NoBrush);
        p.setPen(Qt::NoPen);
        p.setPen(QPen(handlePointColor,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        for(;tempN!=thePointTempDraw.end();){
            if(markFlag==2&&fabs((**temp).x()-(selectedPoint->x()-spotOriginX[i]))<0.001&&fabs((**temp).y()-(selectedPoint->y()-spotOriginY[i]))<0.001){
                //如果所遍历的点被选中，且为控制点中的A控制点
                //qDebug("-----1111111111");
                p.setBrush(QBrush(QColor(205,0,255)));//p.setBrush(QBrush(QColor(255,0,0),Qt::Dense4Pattern));
                p.drawLine(**temp,**tempN);
                p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.setBrush(Qt::NoBrush);
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
            }
            else if(markFlag==3&&fabs((**tempN).x()-(selectedPoint->x()-spotOriginX[i]))<0.001&&fabs((**tempN).y()-(selectedPoint->y()-spotOriginY[i]))<.001){
                //如果所遍历的点被选中，且为控制点中的B控制点
                //qDebug("-----2222222222");
                p.setBrush(QBrush(QColor(205,0,255)));
                p.drawLine(**temp,**tempN);
                p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.setBrush(Qt::NoBrush);
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
            }
            else{//普通绘点
                p.drawLine(**temp,**tempN);
                //p.setBrush(QBrush(QColor(205,0,255)));
                p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
                p.setBrush(Qt::NoBrush);
                //p.setBrush(Qt::NoBrush);
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
                ++tempN;
                if(tempN!=thePointTempDraw.end())
                    ++temp;
                else
                    break;
            }
        }

        tempN=thePointTempDraw.begin();
        temp=thePointTempDraw.end();
        temp--;
        p.setBrush(Qt::NoBrush);
        p.setPen(Qt::NoPen);
        p.setPen(QPen(handlePointColor,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        //如果最后一个控制点被选中
        if(markFlag==2&&fabs((**temp).x()-(selectedPoint->x()-spotOriginX[i]))<0.001&&fabs((**temp).y()-(selectedPoint->y()-spotOriginY[i]))<.001){
            //qDebug("---------33333333333");
            p.setBrush(QBrush(QColor(205,0,255)));
            p.drawLine(**temp,**tempN);
            p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
            p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
            p.setBrush(Qt::NoBrush);
        }
        else if(markFlag==3&&fabs((**tempN).x()-(selectedPoint->x()-spotOriginX[i]))<0.001&&fabs((**tempN).y()-(selectedPoint->y()-spotOriginY[i]))<.001){
            //qDebug("-------444444444444");
            p.setBrush(QBrush(QColor(205,0,255)));
            p.drawLine(**temp,**tempN);
            p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
            p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
            p.setBrush(Qt::NoBrush);
        }
        else{
            p.drawLine(**temp,**tempN);
            p.drawEllipse((**temp).x()-handlePointSize/2,(**temp).y()-handlePointSize/2,handlePointSize,handlePointSize);
            p.drawEllipse((**tempN).x()-handlePointSize/2,(**tempN).y()-handlePointSize/2,handlePointSize,handlePointSize);
        }
        p.scale(1/stretch[i],1/stretch[i]);
        p.rotate(-rotation[i]);
        p.translate(-spotOriginX[i],-spotOriginY[i]);
        //      p.translate(spotOriginX[t],spotOriginY[t]);
        //      p.rotate(-90);
        //      p.scale(2,2);
    }

}

void DrawWidget::drawProcessLine(QPainter &p){
    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::NoPen);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    list<QPointF*>::iterator oP = oPoint.begin();
    list<QPointF*>::iterator oPN=++oP;
    --oP;
    for(;oPN!=oPoint.end();++oPN,++oP){
        p.drawLine((**oP),(**oPN));
    }
}

void DrawWidget::drawBackground(QPainter &p){
    //p.setBrush(Qt::white);
    //p.setPen(Qt::NoPen);
    //p.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

    //backRect=new(QPainterPath);
    //QPainterPath *path5=new(QPainterPath);
    //backRect->addRect(0, 0,width(),height());
    //p.drawPath(*backRect);
    //int oX=width()/2;
    //int oY=height()/2;
    //*path5=backRect->intersected(*path4);//绘制画布
    //QBrush f(backGroundColor);
    //p.setBrush(f);
    //p.drawPath(*path5);
}
void DrawWidget::drawBlank(QPainter &p){
    p.setPen(QPen(Qt::white,1/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    //p.setPen(QPen(Qt::black,1/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    p.setBrush(QBrush(QColor(255,255,255)));

    QPainterPath *preCanvasPath;
    preCanvasPath=canvasPath;
    canvasPath=new QPainterPath;

    canvasPath->addRect(-drawX/2-drawZ-500,-drawZ-drawY/2,drawZ+500,drawZ);
    //canvasPath->addRect(-drawX/2-drawZ,-drawY/2,drawZ,drawY);
    //canvasPath->addRect(-drawX/2,-drawY/2,drawX,drawY);
    //canvasPath->addRect(drawX/2,-drawY/2,drawZ,drawY);
    //canvasPath->addRect(-drawX/2,drawY/2,drawX,drawZ);
    canvasPath->addRect(drawX/2,-drawY/2-drawZ,drawZ+500,drawZ);
    canvasPath->addRect(-drawX/2-drawZ,drawY/2,drawZ,drawZ);
    canvasPath->addRect(drawX/2,drawY/2,drawZ+500,drawZ+500);

    canvasPath->addRect(-drawX/2-500,-drawY/2-drawZ-500,drawX+1000,500);
    canvasPath->addRect(-drawX/2-drawZ-500,-drawY/2,500,drawY);
    canvasPath->addRect(-drawX/2-500,drawY/2+drawZ,1000+drawX,500);
    canvasPath->addRect(drawX/2+drawZ,-drawY/2,500,drawY);
    //canvasPath->addRect(drawX/2,drawY/2,drawZ,drawZ);

    //canvasX=2*drawZ+drawX;
    //canvasY=2*drawZ+drawY;

    p.translate(midWidth,midHeight);
    p.scale(windowScale,windowScale);
    p.drawPath(*canvasPath);

    p.scale(1/windowScale,1/windowScale);
    p.translate(-midWidth,-midHeight);
    delete preCanvasPath;

    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::NoPen);
}
void DrawWidget::drawEdgeLine(QPainter &p){
    //p.setPen(QPen(Qt::white,1/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    p.setPen(QPen(Qt::black,1/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    //p.setBrush(QBrush(QColor(255,255,255)));

    QPainterPath *preCanvasPath;
    preCanvasPath=canvasPath;
    canvasPath=new QPainterPath;
    p.translate(midWidth,midHeight);
    p.scale(windowScale,windowScale);
    p.drawPath(*canvasPath);
    /////////////////////////////////////////////////////////////////////////////////
    p.drawLine(QPointF(-drawX/2,-drawY/2-drawZ),QPointF(drawX/2,-drawY/2-drawZ));
    p.drawLine(QPointF(-drawX/2,-drawY/2),QPointF(drawX/2,-drawY/2));
    p.drawLine(QPointF(-drawX/2,drawY/2),QPointF(drawX/2,drawY/2));
    p.drawLine(QPointF(-drawX/2,drawZ+drawY/2),QPointF(drawX/2,drawZ+drawY/2));
    /////////////////////////////////////////////////////////////////////////////////
    p.drawLine(QPointF(-drawX/2-drawZ,-drawY/2),QPointF(-drawX/2-drawZ,drawY/2));
    p.drawLine(QPointF(drawX/2+drawZ,-drawY/2),QPointF(drawX/2+drawZ,drawY/2));
    /////////////////////////////////////////////////////////////////////////////////
    p.drawLine(QPointF(-drawX/2,-drawY/2-drawZ),QPointF(-drawX/2,-drawY/2));
    p.drawLine(QPointF(drawX/2,-drawY/2-drawZ),QPointF(drawX/2,-drawY/2));

    p.drawLine(QPointF(-drawZ-drawX/2,-drawY/2),QPointF(-drawX/2,-drawY/2));
    p.drawLine(QPointF(-drawZ-drawX/2,drawY/2),QPointF(-drawX/2,drawY/2));

    p.drawLine(QPointF(drawX/2,-drawY/2),QPointF(drawX/2+drawZ,-drawY/2));
    p.drawLine(QPointF(drawX/2,drawY/2),QPointF(drawX/2+drawZ,drawY/2));

    p.drawLine(QPointF(-drawX/2,drawY/2),QPointF(-drawX/2,drawY/2+drawZ));
    p.drawLine(QPointF(drawX/2,drawY/2),QPointF(drawX/2,drawY/2+drawZ));


    p.scale(1/windowScale,1/windowScale);
    p.translate(-midWidth,-midHeight);
    delete preCanvasPath;

    //p.setBrush(Qt::NoBrush);
    p.setPen(Qt::NoPen);
}

void DrawWidget::drawCanvas(QPainter &p){
    if(oPoint.empty()&&oPointAll.empty()&&!firstFlag){//第一次设置画布用,firstFlag表示是为0表示是第一次画
        firstFlag=1;
        midWidth=width()/2;
        midHeight=height()/2;
        //qDebug("@@@@@@%f",midWidth);
        preMidWidth=midWidth;
        preMidHeight=midHeight;
    }

    //qDebug("nei bu shi :%d",backGroundColorIndex);
    p.setPen(Qt::NoPen);

    p.setPen(QPen(Qt::black,1/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));


    p.setBrush(QBrush(backGroundColor));

    QPainterPath *preCanvasPath;
    preCanvasPath=canvasPath;
    canvasPath=new QPainterPath;

    if(drawCanvasFlag==0){
        canvasPath->addRect(-drawX/2/*-widthChange*/,-drawY/2/*-heightChange*/,drawX,drawY);
        canvasX=drawX;
        canvasY=drawY;
    }
    else if(drawCanvasFlag==1){
        canvasPath->addRect(-drawX/2/*-widthChange*/,-drawY/2/*-heightChange*/,drawX,drawY);
        canvasX=drawX;
        canvasY=drawY;
        //qDebug("drawCavas1:%f",canvasY);
    }
    else if(drawCanvasFlag==2){

        canvasPath->addRect(-drawX/2,-drawZ-drawY/2,drawX,drawZ);
        canvasPath->addRect(-drawX/2-drawZ,-drawY/2,drawZ,drawY);
        canvasPath->addRect(-drawX/2,-drawY/2,drawX,drawY);
        canvasPath->addRect(drawX/2,-drawY/2,drawZ,drawY);
        canvasPath->addRect(-drawX/2,drawY/2,drawX,drawZ);

        //------------------xiaotian  打印五面视图的左上角点坐标

        /*
        cout<<"上视图左上角坐标"<<(-drawX/2)<<' '<<(-drawZ-drawY/2)<<endl;
        cout<<"左视图左上角坐标"<<(-drawX/2-drawZ)<<' '<<(-drawZ,-drawY/2)<<endl;
        cout<<"中视图左上角坐标"<<(-drawX/2)<<' '<<(-drawY/2)<<endl;
        cout<<"右视图左上角坐标"<<(drawX/2)<<' '<<(-drawY/2)<<endl;
        cout<<"下视图左上角坐标"<<(-drawX/2)<<' '<<(drawY/2)<<endl;
        */

        canvasX=2*drawZ+drawX;
        canvasY=2*drawZ+drawY;
        //drawBlank(p,canvasPath);
        //qDebug("drawCavas2:%f",canvasY);
    }


    p.translate(midWidth,midHeight);
    p.scale(windowScale,windowScale);
    p.drawPath(*canvasPath);
    //p.setPen(Qt::NoPen);


    //------------------------xiaotian    budongde
    p.scale(1/windowScale,1/windowScale);
    p.translate(-midWidth,-midHeight);
    delete preCanvasPath;

    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::NoPen);



    //qDebug("~~~%f  %f",canvasX,canvasY);
    //qDebug("%f  %f",midWidth,midHeight);
}
void DrawWidget::drawCLine(QPainter &p){
    //    for(float i=midWidth-0.5*drawX;i<midWidth+0.5*drawX;i+=rectSize){
    //        for(float j=midHeight-0.5*drawY-drawZ;j<midHeight-0.5*drawY;j+=rectSize){
    //            p.drawLine(QPointF(i,j),QPointF(i+draw));
    //        }
    //    }
    midWidth=width()/2;
    midHeight=height()/2;
    for(float i=midWidth-0.5*drawX;i<midWidth+0.5*drawX;i+=rectSize){
        p.drawLine(QPointF(i,midHeight-0.5*drawY-drawZ),QPointF(i,midHeight+0.5*drawY+drawZ));
    }
    for(float j=midHeight-0.5*drawY-drawZ;j<midHeight+0.5*drawY+drawZ;j+=rectSize){
        p.drawLine(QPointF(midWidth - 0.5*drawX,j),QPointF(midWidth + 0.5*drawX,j));
    }

    for(float i=midWidth-0.5*drawX-drawZ;i<midWidth-0.5*drawX;i+=rectSize){
        p.drawLine(QPointF(i,midHeight-0.5*drawY),QPointF(i,midHeight+0.5*drawY));
    }
    for(float j=midHeight-0.5*drawY;j<midHeight+0.5*drawY;j+=rectSize){
        p.drawLine(QPointF(midWidth - 0.5*drawX-drawZ,j),QPointF(midWidth - 0.5*drawX,j));
    }

    for(float i=midWidth+0.5*drawX;i<midWidth+0.5*drawX+drawZ;i+=rectSize){
        p.drawLine(QPointF(i,midHeight-0.5*drawY),QPointF(i,midHeight+0.5*drawY));
    }
    for(float j=midHeight-0.5*drawY;j<midHeight+0.5*drawY;j+=rectSize){
        p.drawLine(QPointF(midWidth + 0.5*drawX,j),QPointF(midWidth + 0.5*drawX + drawZ,j));
    }

}

void DrawWidget::drawCanvasX(QPainter &p){
    QPainterPath *preCanvasPath;
    preCanvasPath=canvasPath;
    canvasPath=new QPainterPath;
    midWidth=width()/2;
    midHeight=height()/2;
    canvasPath->addRect(-canvasX/2-widthChange,-canvasY/2-heightChange,canvasX,canvasY);
    delete preCanvasPath;
}

void DrawWidget::drawMark(QPainter &p1){
    float p[4][2];
    double ta,tb,tc,td,xt,yt;
    int rate=100;
    float CurvatureX1,CurvatureY1,CurvatureX2,CurvatureY2,Curvature,Curvature1,Curvature2;
    p1.setPen(QPen(QColor(0,200,200)));

    //大循环用
    list<QPointF*>::iterator oP;
    oP = oPointAll.begin();
    list<QPointF*>::iterator oPH ;
    oPH = handlePointAll.begin();

    //小循环用
    list<QPointF*>::iterator oP1;
    list<QPointF*>::iterator oPH1 ;


    //int temp=1;
    for(int i=1;i<drawOk+1;i++){
        list<QPointF*>oPointTemp;
        list<QPointF*>thePointTemp;

        //把点放到链表中
        for(int j=1;j<spotNum[i]+1;j++){
            oPointTemp.push_back(*oP);
            thePointTemp.push_back(*oPH);
            oPH++;
            thePointTemp.push_back(*oPH);
            oPH++;
            oP++;
        }


        oP1=oPointTemp.begin();
        oPH1=thePointTemp.begin();
        p1.translate(spotOriginX[i],spotOriginY[i]);
        p1.rotate(rotation[i]);
        p1.scale(stretch[i],stretch[i]);

        //计算最后一个点之前的曲率半径
        for(;oP1!=oPointTemp.end();++oP1){
            p[0][0]=(**oP1).x();
            p[0][1]=(**oP1).y();
            ++oP1;
            if(oP1==oPointTemp.end())
                break;
            p[3][0]=(**oP1).x();
            p[3][1]=(**oP1).y();

            p[1][0]=(**oPH1).x();
            p[1][1]=(**oPH1).y();
            ++oPH1;
            p[2][0]=(**oPH1).x();
            p[2][1]=(**oPH1).y();
            ++oPH1;
            --oP1;


            for(float t=0;t<=1;t+=1.0/rate){
                ta=(1-t)*(1-t)*(1-t);
                tb=3*t*(1-t)*(1-t);
                tc=3*t*t*(1-t);
                td=t*t*t;
                xt=p[0][0]*ta+p[1][0]*tb+p[2][0]*tc+p[3][0]*td;
                yt=p[0][1]*ta+p[1][1]*tb+p[2][1]*tc+p[3][1]*td;

                CurvatureX1=3*(p[1][0]-p[0][0])*(1-t)*(1-t)+6*(p[2][0]-p[1][0])*t*(1-t)+3*(p[3][0]-p[2][0])*t*t;
                CurvatureY1=3*(p[1][1]-p[0][1])*(1-t)*(1-t)+6*(p[2][1]-p[1][1])*t*(1-t)+3*(p[3][1]-p[2][1])*t*t;
                CurvatureX2=6*(p[2][0]-2*p[1][0]+p[0][0])*(1-t)+6*(p[3][0]-2*p[2][0]+p[1][0])*t;
                CurvatureY2=6*(p[2][1]-2*p[1][1]+p[0][1])*(1-t)+6*(p[3][1]-2*p[2][1]+p[1][1])*t;
                Curvature1=pow(CurvatureX1*CurvatureX1+CurvatureY1*CurvatureY1,1.5);
                Curvature2=fabs(CurvatureX1*CurvatureY2-CurvatureX2*CurvatureY1);
                Curvature=Curvature1/Curvature2;
                //qDebug("di %f ge dian:%f",10*t+1,Curvature);
                //qDebug("%f %f",xt,yt);
                //qDebug("%f",CurvatureY1/CurvatureX1);
                if(Curvature<minResolution)
                {
                    p1.drawEllipse(xt-keyPointSize/6,yt-keyPointSize/6,keyPointSize/3,keyPointSize/3);
                }
                //if(temp==3)
                //p1.drawEllipse(xt-2-t*5,yt-2-t*5,4+t*10,4+t*10);
                //p1.drawEllipse(xt-2,yt-2,4,4);
                //p1.drawEllipse(xt-1,yt-1,2,2);
            }
            //temp++;
        }

        //计算最后一个点的曲率半径
        --oP1;
        p[0][0]=(**oP1).x();
        p[0][1]=(**oP1).y();
        oP1=oPointTemp.begin();
        p[3][0]=(**oP1).x();
        p[3][1]=(**oP1).y();

        p[1][0]=(**oPH1).x();
        p[1][1]=(**oPH1).y();
        ++oPH1;
        p[2][0]=(**oPH1).x();
        p[2][1]=(**oPH1).y();


        for(float t=0;t<=1;t+=1.0/rate){
            ta=(1-t)*(1-t)*(1-t);
            tb=3*t*(1-t)*(1-t);
            tc=3*t*t*(1-t);
            td=t*t*t;
            xt=p[0][0]*ta+p[1][0]*tb+p[2][0]*tc+p[3][0]*td;
            yt=p[0][1]*ta+p[1][1]*tb+p[2][1]*tc+p[3][1]*td;

            CurvatureX1=3*(p[1][0]-p[0][0])*(1-t)*(1-t)+6*(p[2][0]-p[1][0])*t*(1-t)+3*(p[3][0]-p[2][0])*t*t;
            CurvatureY1=3*(p[1][1]-p[0][1])*(1-t)*(1-t)+6*(p[2][1]-p[1][1])*t*(1-t)+3*(p[3][1]-p[2][1])*t*t;
            CurvatureX2=6*(p[2][0]-2*p[1][0]+p[0][0])*(1-t)+6*(p[3][0]-2*p[2][0]+p[1][0])*t;
            CurvatureY2=6*(p[2][1]-2*p[1][1]+p[0][1])*(1-t)+6*(p[3][1]-2*p[2][1]+p[1][1])*t;
            Curvature1=pow(CurvatureX1*CurvatureX1+CurvatureY1*CurvatureY1,1.5);
            Curvature2=fabs(CurvatureX1*CurvatureY2-CurvatureX2*CurvatureY1);
            Curvature=Curvature1/Curvature2;

            if(Curvature<minResolution)
            {
                //qDebug("%d",minResolution);
                p1.drawEllipse(xt-keyPointSize/6,yt-keyPointSize/6,keyPointSize/3,keyPointSize/3);
            }
        }
        p1.scale(1/stretch[i],1/stretch[i]);
        p1.rotate(-rotation[i]);
        p1.translate(-spotOriginX[i],-spotOriginY[i]);

    }//循环斑点个数
    p1.setPen(Qt::NoPen);
}

//-------------------------xiaotian   画数码迷彩斑点，使用矩阵的画法
void DrawWidget::drawDigitalSpot(QPainter &p){
    list<QPainterPath*>::iterator tempDraw = allPath.begin();
    if(ctrlSize){
        p.setPen(QPen(spotLineColor,8*spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        //p.setPen(Qt::NoPen);
        int tempCount=1;//用来判断现在循环到哪个斑点
        list<int>::iterator ctrlOP=spotSelectedCtrl.begin();
        for(;ctrlOP!=spotSelectedCtrl.end();ctrlOP++){
            while(tempCount<*ctrlOP){
                tempCount++;
                tempDraw++;
            }
            //设置新的坐标原点
            p.translate(spotOriginX[tempCount],spotOriginY[tempCount]);
            //旋转角度
            p.rotate(rotation[tempCount]);
            //改变刻度长度
            p.scale(stretch[tempCount],stretch[tempCount]);
            //-----------xiaotian
            //            p.scale(1,-1);



            p.drawPath(**tempDraw);

            p.scale(1/stretch[tempCount],1/stretch[tempCount]);
            //--------------xiaotian
            //            p.scale(1,-1);
            p.rotate(-rotation[tempCount]);
            p.translate(-spotOriginX[tempCount],-spotOriginY[tempCount]);
            tempCount++;
            tempDraw++;
        }
    }
    else if(markFlag==4){
        for(int i=1;i<spotSelectedNum;i++){
            tempDraw++;
        }
        p.translate(spotOriginX[spotSelectedNum],spotOriginY[spotSelectedNum]);
        p.rotate(rotation[spotSelectedNum]);
        p.scale(stretch[spotSelectedNum],stretch[spotSelectedNum]);
        //--------------xiaotian
        //        p.scale(1,-1);



        p.setPen(QPen(spotLineColor,8*spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

        p.drawPath(**tempDraw);

        p.scale(1/stretch[spotSelectedNum],1/stretch[spotSelectedNum]);
        //----------xiaotian
        //        p.scale(1,-1);
        p.rotate(-rotation[spotSelectedNum]);
        p.translate(-spotOriginX[spotSelectedNum],-spotOriginY[spotSelectedNum]);
    }



    p.setPen(Qt::NoPen);
    p.setBrush(Qt::NoBrush);
    //绘制所有斑点，上边是绘制选中斑点边缘
    list<QPainterPath*>::iterator temp = allPath.begin();
    int count=1;
    int t=1;
    p.setPen(QPen(spotLineColor,spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if(!ifShowSpotEdge){
        p.setPen(Qt::NoPen);
    }
    for(;t<drawOk+1;t++){
        p.translate(spotOriginX[t],spotOriginY[t]);
        p.rotate(rotation[t]);
        p.scale(stretch[t],stretch[t]);

        //令y轴朝上为正，朝下为负   ---------xiaotian
        //         p.scale(1,-1);


        getSpotColor(count);
        QBrush b(spotColor);
        p.setBrush(b);
        p.drawPath(**temp);
        //qDebug("aaaaaaaaaaaaa");
        //qDebug("num de ge shu shi:%d",spotNum[t]);

        count++;
        temp++;
        p.scale(1/stretch[t],1/stretch[t]);
        //---------------xiaotian
        //         p.scale(1,-1);

        p.rotate(-rotation[t]);
        p.translate(-spotOriginX[t],-spotOriginY[t]);
    }
}



// ------------------------xiaotian真正开始画斑点的方法
void DrawWidget::drawSpot(QPainter &p){
    list<QPainterPath*>::iterator tempDraw = allPath.begin();
    if(ctrlSize){
        p.setPen(QPen(spotLineColor,8*spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        //p.setPen(Qt::NoPen);
        int tempCount=1;//用来判断现在循环到哪个斑点
        list<int>::iterator ctrlOP=spotSelectedCtrl.begin();
        for(;ctrlOP!=spotSelectedCtrl.end();ctrlOP++){
            while(tempCount<*ctrlOP){
                tempCount++;
                tempDraw++;
            }
            //设置新的坐标原点
            p.translate(spotOriginX[tempCount],spotOriginY[tempCount]);
            //旋转角度
            p.rotate(rotation[tempCount]);
            //改变刻度长度
            p.scale(stretch[tempCount],stretch[tempCount]);
            //-----------xiaotian
            p.scale(1,-1);



            p.drawPath(**tempDraw);

            p.scale(1/stretch[tempCount],1/stretch[tempCount]);
            //--------------xiaotian
            p.scale(1,-1);
            p.rotate(-rotation[tempCount]);
            p.translate(-spotOriginX[tempCount],-spotOriginY[tempCount]);
            tempCount++;
            tempDraw++;
        }
    }
    else if(markFlag==4){
        for(int i=1;i<spotSelectedNum;i++){
            tempDraw++;
        }
        p.translate(spotOriginX[spotSelectedNum],spotOriginY[spotSelectedNum]);
        p.rotate(rotation[spotSelectedNum]);
        p.scale(stretch[spotSelectedNum],stretch[spotSelectedNum]);
        //--------------xiaotian
        p.scale(1,-1);



        p.setPen(QPen(spotLineColor,8*spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

        p.drawPath(**tempDraw);

        p.scale(1/stretch[spotSelectedNum],1/stretch[spotSelectedNum]);
        //----------xiaotian
        p.scale(1,-1);
        p.rotate(-rotation[spotSelectedNum]);
        p.translate(-spotOriginX[spotSelectedNum],-spotOriginY[spotSelectedNum]);
    }



    p.setPen(Qt::NoPen);
    p.setBrush(Qt::NoBrush);
    //绘制所有斑点，上边是绘制选中斑点边缘
    list<QPainterPath*>::iterator temp = allPath.begin();
    int count=1;
    int t=1;
    p.setPen(QPen(spotLineColor,spotLineWidth/windowScale,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    if(!ifShowSpotEdge){
        p.setPen(Qt::NoPen);
    }
    for(;t<drawOk+1;t++){
        p.translate(spotOriginX[t],spotOriginY[t]);
        p.rotate(rotation[t]);
        p.scale(stretch[t],stretch[t]);

        //令y轴朝上为正，朝下为负   ---------xiaotian
        p.scale(1,-1);


        getSpotColor(count);
        QBrush b(spotColor);
        p.setBrush(b);
        p.drawPath(**temp);
        //qDebug("aaaaaaaaaaaaa");
        //qDebug("num de ge shu shi:%d",spotNum[t]);

        count++;
        temp++;
        p.scale(1/stretch[t],1/stretch[t]);
        //---------------xiaotian
        p.scale(1,-1);

        p.rotate(-rotation[t]);
        p.translate(-spotOriginX[t],-spotOriginY[t]);
    }
}

void DrawWidget::drawDigital(QPainter &p){
    p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    if(mousePressFlag){
        p.drawRect(xBegin,yBegin,xEnd-xBegin,yEnd-yBegin);
    }


    if(showOPoint)
        drawOPoint(p);

    if(oPoint.size()>1){//绘制过程直线
        drawProcessLine(p);
    }

    if(drawOk){

        drawSpot(p);

        if(showOPoint){
            drawOPoint(p);
            drawOrign(p);//绘制斑点中间那个点
        }
        if(radiusFlag){
            drawMark(p);
        }
    }

    drawEdgeLine(p);
    drawScaleLine(p);


}

void DrawWidget::drawOrign(QPainter &p){
    //qDebug :%d",drawOk);
    for(int j=1;j<drawOk+1;j++){
        p.drawEllipse(spotOriginX[j]-3,spotOriginY[j]-3,6,6);
    }
}
void DrawWidget::getAllColor(spotColorAll&allColorF,int &backGroundColorIndexF,QColor &backGroundColorF){
    for(int i=1;i<drawOk+1;i++){
        allColorF.myColor[i]=allColor.myColor[i];
        allColorF.index[i]=allColor.index[i];
    }
    backGroundColorIndexF=backGroundColorIndex;
    backGroundColorF=backGroundColor;
}

void DrawWidget::getAutoCAD(){

    //int num[5][100],hasNum/*记录斑点个数*/;
    int num[5][1000],hasNum/*记录斑点个数*/;


    //第一部分
    judgeIntersection(num,0,&hasNum,midWidth-drawX/2,midHeight-drawY/2-drawZ,drawX,drawZ);
    getThePoint(num,hasNum,0);
    getThePointAll(num,hasNum,0);

    //第二部分
    judgeIntersection(num,1,&hasNum,midWidth-drawX/2-drawZ,midHeight-drawY/2,drawZ,drawY);
    getThePoint(num,hasNum,1);
    getThePointAll(num,hasNum,1);

    //第三部分
    judgeIntersection(num,2,&hasNum,midWidth-drawX/2,midHeight-drawY/2,drawX,drawY);
    getThePoint(num,hasNum,2);
    getThePointAll(num,hasNum,2);

    //第四部分
    judgeIntersection(num,3,&hasNum,midWidth+drawX/2,midHeight-drawY/2,drawZ,drawY);
    getThePoint(num,hasNum,3);
    getThePointAll(num,hasNum,3);

    //第五部分
    judgeIntersection(num,4,&hasNum,midWidth-drawX/2,midHeight+drawY/2,drawX,drawZ);
    getThePoint(num,hasNum,4);
    getThePointAll(num,hasNum,4);

    saveGet.autoCADAll();
}

//void DrawWidget::getThePoint(int (*num)[100],int hasNum,int area){
void DrawWidget::getThePoint(int (*num)[1000],int hasNum,int area){
    list<QPointF*>::iterator oP;
    float x,y;
    QPointF *tempP[5000][100];//最多有5000个斑点,5个区域,每个斑点最多有100个点
    QPointF *temp;
    //找到移动斑点的原点所在区间
    for(int a=0;a<hasNum;a++){
        oP= oPointAll.begin();
        for(int i=1;i<num[area][a];i++){//spotSelectedNum
            for(int j=1;j<spotNum[i]+1;j++){
                ++oP;
            }
        }
        //将斑点的原点放入数组,原点是从下表1开始放的
        for(int j=1;j<spotNum[num[area][a]]+1;j++){

            //--------------xiaotian    修改cad
            x=(**oP).x()*cos(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale-(**oP).y()*sin(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale;
            y=(**oP).x()*sin(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale+(**oP).y()*cos(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale;
            //            x=(**oP).x()/windowScale-(**oP).y()/windowScale;
            //            y=(**oP).x()/windowScale+(**oP).y()/windowScale;
            if(area==0){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight-drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight-drawY/2/**/);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==1){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2+drawZ);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2+drawZ/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==2){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==3){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth-drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth-drawX/2/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==4){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2+drawZ);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2+drawZ/**/);
                tempP[a][j]=temp;
                ++oP;
            }

        }
    }
    if(area==0){
        saveGet.getAutoCAD(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawZ);
    }
    if(area==1){
        saveGet.getAutoCAD(hasNum,spotNum,allColor.index,num,tempP,area,drawZ,drawY);
    }
    if(area==2){
        saveGet.getAutoCAD(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY);
    }
    if(area==3){
        saveGet.getAutoCAD(hasNum,spotNum,allColor.index,num,tempP,area,drawZ,drawY);
    }
    if(area==4){
        saveGet.getAutoCAD(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawZ);
    }

}

void DrawWidget::getThePointAll(int (*num)[1000],int hasNum,int area){
    list<QPointF*>::iterator oP;
    float x,y;
    QPointF *tempP[5000][100];//最多有5000个斑点,5个区域,每个斑点最多有100个点
    QPointF *temp;
    //找到移动斑点的原点所在区间
    for(int a=0;a<hasNum;a++){
        oP= oPointAll.begin();
        for(int i=1;i<num[area][a];i++){//spotSelectedNum
            for(int j=1;j<spotNum[i]+1;j++){
                ++oP;
            }
        }
        //将斑点的原点放入数组,原点是从下表1开始放的
        for(int j=1;j<spotNum[num[area][a]]+1;j++){
            //------xiaotian   修改cad
            x=(**oP).x()*cos(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale-(**oP).y()*sin(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale;
            y=(**oP).x()*sin(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale+(**oP).y()*cos(rotation[num[area][a]]/180*PI)*stretch[num[area][a]]/windowScale;
            //            x=(**oP).x()/windowScale-(**oP).y()/windowScale;
            //            y=(**oP).x()/windowScale+(**oP).y()/windowScale;

            if(area==0){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight-drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/+drawZ);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight-drawY/2/**/+drawY+drawZ);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==1){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2+drawZ);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2+drawZ/**/);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/+drawZ);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==2){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/+drawZ);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/+drawZ);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==3){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth-drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth-drawX/2/**/+drawZ+drawX);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2/**/+drawZ);
                tempP[a][j]=temp;
                ++oP;
            }
            if(area==4){
                //tempP[a][j].setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2);
                //tempP[a][j].setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2+drawZ);
                temp=new QPointF;
                temp->setX(x+spotOriginX[num[area][a]]-midWidth+drawX/2/**/+drawZ);
                temp->setY(-y-spotOriginY[num[area][a]]+midHeight+drawY/2+drawZ/**/);
                tempP[a][j]=temp;
                ++oP;
            }

        }
    }
    if(area==0){
        saveGet.getAutoCADAll(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY,drawZ);
    }
    if(area==1){
        saveGet.getAutoCADAll(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY,drawZ);
    }
    if(area==2){
        saveGet.getAutoCADAll(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY,drawZ);
    }
    if(area==3){
        saveGet.getAutoCADAll(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY,drawZ);
    }
    if(area==4){
        saveGet.getAutoCADAll(hasNum,spotNum,allColor.index,num,tempP,area,drawX,drawY,drawZ);
    }

}

void DrawWidget::getSpotColor(int count){
    //qDebug("%d",count);
    spotColor=allColor.myColor[count];
}
void DrawWidget::getCtrl(int & tempSize, list<int> &tempSelectedCtrl){
    tempSize=ctrlSize;
    tempSelectedCtrl.clear();
    list<int>::iterator oP=spotSelectedCtrl.begin();
    for(int i=1;i<ctrlSize+1;i++,oP++){
        tempSelectedCtrl.push_back(*oP);
    }
}

int DrawWidget::handleSelected(){
    list<QPointF*>::iterator oP = handlePointAll.begin();
    list<QPointF*>::iterator oP1 = oPointAll.begin();
    float x,y;

    for(int i=1;i<drawOk+1;i++){
        thePointTemp.clear();
        oPointTemp.clear();
        for(int j=1;j<2*spotNum[i]+1;j++){
            thePointTemp.push_back(*oP);
            ++oP;
        }


        for(int j=1;j<spotNum[i]+1;j++){
            oPointTemp.push_back(*oP1);
            ++oP1;
        }


        handleSelectedO=oPointTemp.begin();
        ++handleSelectedO;
        handleSelectedA=thePointTemp.begin();
        ++handleSelectedA;
        handleSelectedB=++handleSelectedA;
        --handleSelectedA;

        int t=2;
        while(handleSelectedB!=thePointTemp.end()){
            cPath=new(QPainterPath);
            //((**temp).x()-keyPointSize/2)/2+spotOriginX[t];
            //x=(**handleSelectedA).x()*cos(rotation[i]/180*PI)/stretch[i]-(**handleSelectedA).y()*sin(rotation[i]/180*PI)/stretch[i]+spotOriginX[i]-handlePointSize/2/stretch[i];
            //y=(**handleSelectedA).x()*sin(rotation[i]/180*PI)/stretch[i]+(**handleSelectedA).y()*cos(rotation[i]/180*PI)/stretch[i]+spotOriginY[i]-handlePointSize/2/stretch[i];
            x=(**handleSelectedA).x()*cos(rotation[i]/180*PI)*stretch[i]-(**handleSelectedA).y()*sin(rotation[i]/180*PI)*stretch[i]+spotOriginX[i]-handlePointSize/2*stretch[i];
            y=(**handleSelectedA).x()*sin(rotation[i]/180*PI)*stretch[i]+(**handleSelectedA).y()*cos(rotation[i]/180*PI)*stretch[i]+spotOriginY[i]-handlePointSize/2*stretch[i];
            //cPath->addEllipse(((**handleSelectedA).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedA).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
            cPath->addEllipse(x,y,handlePointSize*stretch[i],handlePointSize*stretch[i]);
            if(cPath->contains(*currentPoint)){//如果if为真,责点重合
                flag=4;
                markFlag=2;
                //qDebug("11111111");
                spotSelectedNum=i;
                selectedPoint=new(QPointF);
                selectedPoint->setX((**handleSelectedA).x()+spotOriginX[i]);
                selectedPoint->setY((**handleSelectedA).y()+spotOriginY[i]);
                //addForcePointEdit();


                handleA.setX((**handleSelectedA).x()+spotOriginX[i]);
                handleA.setY((**handleSelectedA).y()+spotOriginY[i]);
                handleB.setX((**handleSelectedB).x()+spotOriginX[i]);
                handleB.setY((**handleSelectedB).y()+spotOriginY[i]);
                handleO.setX((**handleSelectedO).x());
                handleO.setY((**handleSelectedO).y());//qDebug("oooo %f  %f",handleO.x(),handleO.y());
                delete cPath;
                return 1;
            }
            delete cPath;

            cPath=new(QPainterPath);
            x=(**handleSelectedB).x()*cos(rotation[i]/180*PI)*stretch[i]-(**handleSelectedB).y()*sin(rotation[i]/180*PI)*stretch[i]+spotOriginX[i]-handlePointSize/2*stretch[i];
            y=(**handleSelectedB).x()*sin(rotation[i]/180*PI)*stretch[i]+(**handleSelectedB).y()*cos(rotation[i]/180*PI)*stretch[i]+spotOriginY[i]-handlePointSize/2*stretch[i];
            //cPath->addEllipse(((**handleSelectedA).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedA).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
            cPath->addEllipse(x,y,handlePointSize*stretch[i],handlePointSize*stretch[i]);
            //cPath->addEllipse(((**handleSelectedB).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedB).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
            if(cPath->contains(*currentPoint)){//如果if为真,责点重合
                flag=5;
                markFlag=3;
                //qDebug("22222222222");
                spotSelectedNum=i;
                selectedPoint=new(QPointF);
                selectedPoint->setX((**handleSelectedB).x()+spotOriginX[i]);
                selectedPoint->setY((**handleSelectedB).y()+spotOriginY[i]);
                //addForcePointEdit();

                handleA.setX((**handleSelectedA).x()+spotOriginX[i]);
                handleA.setY((**handleSelectedA).y()+spotOriginY[i]);
                handleB.setX((**handleSelectedB).x()+spotOriginX[i]);
                handleB.setY((**handleSelectedB).y()+spotOriginY[i]);
                handleO.setX((**handleSelectedO).x());
                handleO.setY((**handleSelectedO).y());
                delete cPath;
                return 1;
            }
            delete cPath;
            ++handleSelectedA;
            ++handleSelectedA;
            ++handleSelectedB;
            ++handleSelectedB;
            ++handleSelectedO;
            t++;
        }

        handleSelectedA=thePointTemp.end();
        handleSelectedA--;
        handleSelectedB=thePointTemp.begin();
        handleSelectedO=oPointTemp.begin();


        cPath=new(QPainterPath);
        x=(**handleSelectedA).x()*cos(rotation[i]/180*PI)*stretch[i]-(**handleSelectedA).y()*sin(rotation[i]/180*PI)*stretch[i]+spotOriginX[i]-handlePointSize/2*stretch[i];
        y=(**handleSelectedA).x()*sin(rotation[i]/180*PI)*stretch[i]+(**handleSelectedA).y()*cos(rotation[i]/180*PI)*stretch[i]+spotOriginY[i]-handlePointSize/2*stretch[i];
        //cPath->addEllipse(((**handleSelectedA).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedA).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
        cPath->addEllipse(x,y,handlePointSize*stretch[i],handlePointSize*stretch[i]);
        //cPath->addEllipse(((**handleSelectedA).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedA).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
        if(cPath->contains(*currentPoint)){//如果if为真,责点重合
            flag=4;
            markFlag=2;//qDebug("333333333");
            spotSelectedNum=i;
            selectedPoint=new(QPointF);
            selectedPoint->setX((**handleSelectedA).x()+spotOriginX[i]);
            selectedPoint->setY((**handleSelectedA).y()+spotOriginY[i]);
            handleA.setX((**handleSelectedA).x()+spotOriginX[i]);
            handleA.setY((**handleSelectedA).y()+spotOriginY[i]);
            handleB.setX((**handleSelectedB).x()+spotOriginX[i]);
            handleB.setY((**handleSelectedB).y()+spotOriginY[i]);
            handleO.setX((**handleSelectedO).x());
            handleO.setY((**handleSelectedO).y());
            delete cPath;
            return 1;
        }
        delete cPath;


        cPath=new(QPainterPath);
        x=(**handleSelectedB).x()*cos(rotation[i]/180*PI)*stretch[i]-(**handleSelectedB).y()*sin(rotation[i]/180*PI)*stretch[i]+spotOriginX[i]-handlePointSize/2*stretch[i];
        y=(**handleSelectedB).x()*sin(rotation[i]/180*PI)*stretch[i]+(**handleSelectedB).y()*cos(rotation[i]/180*PI)*stretch[i]+spotOriginY[i]-handlePointSize/2*stretch[i];
        //cPath->addEllipse(((**handleSelectedA).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedA).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
        cPath->addEllipse(x,y,handlePointSize*stretch[i],handlePointSize*stretch[i]);
        //cPath->addEllipse(((**handleSelectedB).x()-handlePointSize/2)/2+spotOriginX[i],((**handleSelectedB).y()-handlePointSize/2)/2+spotOriginY[i],handlePointSize,handlePointSize);
        if(cPath->contains(*currentPoint)){//如果if为真,责点重合
            flag=5;
            markFlag=3;//qDebug("4444444444");
            spotSelectedNum=i;
            selectedPoint=new(QPointF);
            selectedPoint->setX((**handleSelectedB).x()+spotOriginX[i]);
            selectedPoint->setY((**handleSelectedB).y()+spotOriginY[i]);
            handleA.setX((**handleSelectedA).x()+spotOriginX[i]);
            handleA.setY((**handleSelectedA).y()+spotOriginY[i]);
            handleB.setX((**handleSelectedB).x()+spotOriginX[i]);
            handleB.setY((**handleSelectedB).y()+spotOriginY[i]);
            handleO.setX((**handleSelectedO).x());
            handleO.setY((**handleSelectedO).y());
            delete cPath;
            return 1;
        }
        delete cPath;
    }
    return 0;

}

void DrawWidget::getPointStyle(int bigDrawOk[600], int &bigDrawOkNum, int smallDrawOk[600], int &smallDrawOkNum,int&smallAll){
    bigDrawOkNum=0;
    smallDrawOkNum=0;
    for(int i=1;i<drawOk+1;i++){
        if(spotNum[i]>30){
            bigDrawOk[++bigDrawOkNum]=i;
        }
        else{
            smallDrawOk[++smallDrawOkNum]=i;
        }
    }
    //ok1=drawOk1,ok2=drawOk2,ok3=drawOk3,ok4=drawOk4;
    smallAll=drawOk1+drawOk2+drawOk3+drawOk4;
}

void DrawWidget::getMainArea(MainWindow *mainTemp,QScrollArea *show){
    mainWin=mainTemp;
    showArea=show;
    this->setGeometry(0,0,showArea->width()-5,showArea->height()-5);
    this->update();
    //connect(showArea,SIGNAL(resizeEvent(QResizeEvent *)),this,SLOT(QScrollAreaResize()));
}
int DrawWidget::getEventStyle(){
    return eventStyle;
}
int DrawWidget::getDrawOk(){
    return drawOk;
}


int DrawWidget::getSpotSelectedNum(){
    return spotSelectedNum;
}
void DrawWidget::getSpotNum(int *temp){
    //temp=spotNum;
    for(int i=1;i<drawOk+1;i++){
        temp[i]=spotNum[i];
    }

}

void DrawWidget::getAreaRatio(float *temp){
    caculateAreaRatio();
    for(int i=1;i<drawOk+1;i++){
        temp[i]=areaRatio[i];
    }
}

void DrawWidget::getFiveImage(){
    if(fabs(windowScale-1)<0.001){
        //int num[5][100],hasNum/*记录斑点个数*/;//五个区域，每个区域最多有200个点
        int num[5][1000],hasNum/*记录斑点个数*/;//五个区域，每个区域最多有1000个点
        list<QPainterPath*>::iterator tempPath;
        float oX,oY;
        QPen pen(backGroundColor,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

        //第一副图
        judgeIntersection(num,0,&hasNum,midWidth-drawX/2,midHeight-drawY/2-drawZ,drawX,drawZ);
        QPixmap pix1(drawX,drawZ);
        QPainter p1(&pix1);
        p1.setBrush(backGroundColor);

        p1.setPen(pen);
        p1.drawRect(0,0,drawX,drawZ);

        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[0][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[0][i]]-(midHeight-drawY/2-drawZ);

            p1.translate(oX,oY);
            p1.scale(stretch[num[0][i]],stretch[num[0][i]]);
            p1.rotate(rotation[num[0][i]]);
            //qDebug("jiaodu: %f",rotation[num[0][i]]);
            //qDebug("!!!!!!!!!%f",stretch[num[0][i]]/windowScale);

            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[0][i];j++){
                tempPath++;
            }
            getSpotColor(num[0][i]);
            p1.setBrush(spotColor);
            p1.drawPath(**tempPath);
            p1.setBrush(Qt::NoBrush);

            p1.scale(1/stretch[num[0][i]],1/stretch[num[0][i]]);
            p1.rotate(-rotation[num[0][i]]);
            p1.translate(-oX,-oY);

        }
        p1.end();
        // pix1.save("image/1.png");


        //第二幅图
        judgeIntersection(num,1,&hasNum,midWidth-drawX/2-drawZ,midHeight-drawY/2,drawZ,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix2(drawZ,drawY);
        QPainter p2(&pix2);
        p2.setBrush(backGroundColor);

        p2.setPen(pen);
        p2.drawRect(0,0,drawZ,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[1][0],num[1][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[1][i]]-(midWidth-drawX/2-drawZ);
            oY=spotOriginY[num[1][i]]-(midHeight-drawY/2);

            p2.translate(oX,oY);
            p2.scale(stretch[num[1][i]],stretch[num[1][i]]/windowScale);
            p2.rotate(rotation[num[1][i]]);



            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[1][i];j++){
                tempPath++;
            }
            getSpotColor(num[1][i]);
            p2.setBrush(spotColor);
            p2.drawPath(**tempPath);
            p2.setBrush(Qt::NoBrush);

            p2.scale(1/stretch[num[1][i]],1/stretch[num[1][i]]);
            p2.rotate(-rotation[num[1][i]]);
            p2.translate(-oX,-oY);

        }
        p2.end();
        //pix2.save("image/2.png");


        //第三幅图
        judgeIntersection(num,2,&hasNum,midWidth-drawX/2,midHeight-drawY/2,drawX,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix3(drawX,drawY);
        QPainter p3(&pix3);
        p3.setBrush(backGroundColor);

        p3.setPen(pen);
        p3.drawRect(0,0,drawX,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);

        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[2][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[2][i]]-(midHeight-drawY/2);

            p3.translate(oX,oY);
            p3.scale(stretch[num[2][i]],stretch[num[2][i]]);
            p3.rotate(rotation[num[2][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[2][i];j++){
                tempPath++;
            }
            getSpotColor(num[2][i]);
            p3.setBrush(spotColor);
            p3.drawPath(**tempPath);
            p3.setBrush(Qt::NoBrush);

            p3.scale(1/stretch[num[2][i]],1/stretch[num[2][i]]);
            p3.rotate(-rotation[num[2][i]]);
            p3.translate(-oX,-oY);

        }
        p3.end();
        //pix3.save("image/3.png");






        //第四幅图
        judgeIntersection(num,3,&hasNum,midWidth+drawX/2,midHeight-drawY/2,drawZ,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix4(drawZ,drawY);
        QPainter p4(&pix4);
        p4.setBrush(backGroundColor);

        p4.setPen(pen);
        p4.drawRect(0,0,drawZ,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[3][i]]-(midWidth+drawX/2);
            oY=spotOriginY[num[3][i]]-(midHeight-drawY/2);

            p4.translate(oX,oY);
            p4.scale(stretch[num[3][i]],stretch[num[3][i]]);
            p4.rotate(rotation[num[3][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[3][i];j++){
                tempPath++;
            }
            getSpotColor(num[3][i]);
            p4.setBrush(spotColor);
            p4.drawPath(**tempPath);
            p4.setBrush(Qt::NoBrush);

            p4.scale(1/stretch[num[3][i]],1/stretch[num[3][i]]);
            p4.rotate(-rotation[num[3][i]]);
            p4.translate(-oX,-oY);

        }
        p4.end();
        //pix4.save("image/4.png");




        //第五幅图
        judgeIntersection(num,4,&hasNum,midWidth-drawX/2,midHeight+drawY/2,drawX,drawZ);
        //qDebug("%d",hasNum);
        QPixmap pix5(drawX,drawZ);
        QPainter p5(&pix5);
        p5.setBrush(backGroundColor);

        p5.setPen(pen);
        p5.drawRect(0,0,drawX,drawZ);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[4][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[4][i]]-(midHeight+drawY/2);

            p5.translate(oX,oY);
            p5.scale(stretch[num[4][i]],stretch[num[4][i]]);
            p5.rotate(rotation[num[4][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[4][i];j++){
                tempPath++;
            }
            getSpotColor(num[4][i]);
            p5.setBrush(spotColor);
            p5.drawPath(**tempPath);
            p5.setBrush(Qt::NoBrush);

            p5.scale(1/stretch[num[4][i]],1/stretch[num[4][i]]);
            p5.rotate(-rotation[num[4][i]]);
            p5.translate(-oX,-oY);

        }
        p5.end();
        //pix5.save("image/5.png");
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前缩放比例必须为1        "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
    }
}
//-----------xiaotian   测试数码迷彩单个斑点
void DrawWidget::getDigitalSpotPoint(){
    if(AutoCADFlag){
        //        float saveP[300][2];
        //        int num;
        //        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用

        //        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        showDigital = 1;

        //        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用

        //        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        ++drawOk;
        int edge[10][10];
        int spotReadNum;
        int debugNum=1;
        saveGet.readDigitalSpotPoint(edge,spotReadNum,debugNum);
        pointNum=0;//清空未画完斑点计数器

        int areaCount=areaGet%5+1;//qDebug("*******%d",areaCount);
        int tempX=drawX*windowScale,tempY=drawY*windowScale;
        int ranX,ranY;
        srand(time(0));
        if(areaCount==1){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranY;
        }

        tempX=drawZ*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==2){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawX*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==3){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawZ*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==4){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth+drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth+drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawX*windowScale;
        tempY=drawZ*windowScale;
        if(areaCount==5){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight+drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight+drawY/2*windowScale+ranY;
        }


        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        //        //把刚绘制完斑点的点保存起来
        //        QPointF *tempPoint;
        //        oPoint.clear();
        //        for(int t=1;t<num+1;t++){
        //            tempPoint=new QPointF;
        //            tempPoint->setX(saveP[t][0]);
        //            tempPoint->setY(saveP[t][1]);
        //            oPoint.push_back(tempPoint);
        //            oPointAll.push_back(tempPoint);
        //                }
        //        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        int oriX = spotOriginX[drawOk];
        int oriY = spotOriginY[drawOk];
        int edgeW = 10;
        int rowS = 10;
        int colS = 10;
        caculateOneCurveByDigital(edge,oriX,oriY,edgeW,rowS,colS);
        update();
        eventStyle=1;
        emit ChildWindowEvent();
        areaGet++;
    }else{
        showDigital = 1;

        //        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用

        //        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        ++drawOk;
        int edge[10][10];
        int spotReadNum;
        int debugNum=1;
        saveGet.readDigitalSpotPoint(edge,spotReadNum,debugNum);
        pointNum=0;//清空未画完斑点计数器
        int tempX=drawX*windowScale,tempY=drawY*windowScale;
        int ranX,ranY;
        srand(time(0));
        ranX=rand()%tempX+1;
        ranY=rand()%tempY+1;
        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
        spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
        //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
        //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;

        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        //        stretch[drawOk]=windowScale/4;
        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        //把刚绘制完斑点的点保存起来
        //        QPointF *tempPoint;
        //        oPoint.clear();
        //        for(int t=1;t<num+1;t++){
        //            tempPoint=new QPointF;
        //            tempPoint->setX(saveP[t][0]);
        //            tempPoint->setY(saveP[t][1]);
        //            oPoint.push_back(tempPoint);
        //            oPointAll.push_back(tempPoint);
        //                }
        //caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        int oriX = spotOriginX[drawOk];
        int oriY = spotOriginY[drawOk];
        int edgeW = 10;
        int rowS = 10;
        int colS = 10;
        caculateOneCurveByDigital(edge,oriX,oriY,edgeW,rowS,colS);
        update();
        eventStyle=1;
        emit ChildWindowEvent();
        areaGet++;
    }
    saveStation();
}
//-----------xiaotian   数码迷彩绘制斑点路径
void DrawWidget::caculateOneCurveByDigital(int edge[10][10],int oriX, int oriY, int edgeW, int rowS, int colS){

    //存储坐标
    oPoint.clear();


    path=new(QPainterPath);
    edgeW = edgeW*4;
    float oriRow = rowS/2.0;
    float oriCol = colS/2.0;

    //QPainterPath path;
    for (int i=0;i<rowS;i++)
    {
        for (int j=0;j<colS;j++)
        {
            if(edge[i][j] == 1){
                QPoint Point;
                QPointF *tempPoint;
                Point.setX((j-oriCol)*edgeW);
                Point.setY((i-oriRow)*edgeW);
                path->moveTo(Point);


                tempPoint=new QPointF;
                tempPoint->setX(Point.x());
                tempPoint->setY(Point.y());
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
                //                Point.setX((j*edgeW+oriX)*4);
                //                Point.setY((i*edgeW+oriY)*4);


                //                Point.setX((j*edgeW+oriX)*4);
                //                Point.setY(((i+1)*edgeW+oriY)*4);
                Point.setX(Point.x()+edgeW);
                Point.setY(Point.y());
                path->lineTo(Point);

                tempPoint=new QPointF;
                tempPoint->setX(Point.x());
                tempPoint->setY(Point.y());
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
                //                Point.setX(((j+1)*edgeW+oriX)*4);
                //                Point.setY(((i+1)*edgeW+oriY)*4);
                Point.setX(Point.x());
                Point.setY(Point.y()+edgeW);
                path->lineTo(Point);

                tempPoint=new QPointF;
                tempPoint->setX(Point.x());
                tempPoint->setY(Point.y());
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
                //                Point.setX(((j+1)*edgeW+oriX)*4);
                //                Point.setY((i*edgeW+oriY)*4);
                Point.setX(Point.x()-edgeW);
                Point.setY(Point.y());
                path->lineTo(Point);

                tempPoint=new QPointF;
                tempPoint->setX(Point.x());
                tempPoint->setY(Point.y());
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
                //                Point.setX((j*edgeW+oriX)*4);
                //                Point.setY((i*edgeW+oriY)*4);
                Point.setX(Point.x());
                Point.setY(Point.y()-edgeW);
                path->lineTo(Point);


            }
        }

    }
    allPath.push_back(path);
    forAutoSpotP[drawOk]=path;
}



void DrawWidget::getSpotPoint(){
    int spotReadNum;
    int debugNum=1;
    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用

        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        pointNum=0;//清空未画完斑点计数器

        int areaCount=areaGet%5+1;//qDebug("*******%d",areaCount);
        int tempX=drawX*windowScale,tempY=drawY*windowScale;
        int ranX,ranY;
        srand(time(0));
        if(areaCount==1){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranY;
        }

        tempX=drawZ*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==2){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawX*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==3){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawZ*windowScale;
        tempY=drawY*windowScale;
        if(areaCount==4){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            //qDebug("xxxxxx:%d",ranX);
            spotOriginX[drawOk]=midWidth+drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth+drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;
        }

        tempX=drawX*windowScale;
        tempY=drawZ*windowScale;
        if(areaCount==5){
            ranX=rand()%tempX+1;
            ranY=rand()%tempY+1;
            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
            spotOriginY[drawOk]=midHeight+drawY/2*windowScale+ranY;
            //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
            //spotOriginYI[drawOk]=midHeight+drawY/2*windowScale+ranY;
        }


        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        //把刚绘制完斑点的点保存起来
        QPointF *tempPoint;
        oPoint.clear();
        for(int t=1;t<num+1;t++){
            tempPoint=new QPointF;
            tempPoint->setX(saveP[t][0]);
            tempPoint->setY(saveP[t][1]);
            oPoint.push_back(tempPoint);
            oPointAll.push_back(tempPoint);
        }
        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        update();
        eventStyle=1;
        emit ChildWindowEvent();
        areaGet++;
    }
    else{
        float saveP[300][2];
        int num;
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用

        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        pointNum=0;//清空未画完斑点计数器

        int tempX=drawX*windowScale,tempY=drawY*windowScale;
        int ranX,ranY;
        srand(time(0));
        ranX=rand()%tempX+1;
        ranY=rand()%tempY+1;
        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+ranX;
        spotOriginY[drawOk]=midHeight-drawY/2*windowScale+ranY;
        //spotOriginXI[drawOk]=midWidth-drawX/2*windowScale+ranX;
        //spotOriginYI[drawOk]=midHeight-drawY/2*windowScale+ranY;

        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        //把刚绘制完斑点的点保存起来
        QPointF *tempPoint;
        oPoint.clear();
        for(int t=1;t<num+1;t++){
            tempPoint=new QPointF;
            tempPoint->setX(saveP[t][0]);
            tempPoint->setY(saveP[t][1]);
            oPoint.push_back(tempPoint);
            oPointAll.push_back(tempPoint);
        }
        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        update();
        eventStyle=1;
        emit ChildWindowEvent();
        areaGet++;
    }
    saveStation();
    //qDebug("1111111111111111");
}
void DrawWidget::getCanvasPoint(int num1,int num2){
    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        int spotReadNum;
        int debugNum=0;
        //getCanvasBigPoint();
        //    update();
        getEdgePoint();

        //    //分三个区域随机斑点，上中下



        //最左边部分
        //for(int w=1;w<drawX+2*drawZ;w+=100){
        for(int w=1;w<drawZ;w+=num1/*90*//*80*/){
            for(int h=20;h<drawY-50;h+=num2/*80*//*70*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }
        ////原来的80为100，40为50
        //    for(int w=1;w<drawZ;w+=100){
        //        for(int h=50;h<drawY-50;h+=100){
        //            saveGet.readSpotPoint(2,&num,saveP);//第一个参数没用
        //            spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //            pointNum=0;//清空未画完斑点计数器

        //            spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+w*windowScale+50*windowScale;
        //            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+50*windowScale;
        //            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //            stretch[drawOk]=windowScale/4;
        //            rotation[drawOk]=0;

        //            //把刚绘制完斑点的点保存起来
        //            QPointF *tempPoint;
        //            oPoint.clear();
        //            for(int t=1;t<num+1;t++){
        //                tempPoint=new QPointF;
        //                tempPoint->setX(saveP[t][0]);
        //                tempPoint->setY(saveP[t][1]);
        //                oPoint.push_back(tempPoint);
        //                oPointAll.push_back(tempPoint);
        //                    }
        //            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //        }
        //    }

        //最右边部分
        for(int w=1;w<drawZ;w+=num1/*90*//*80*/){
            for(int h=20;h<drawY-50;h+=num2/*80*//*70*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }





        //最上边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*90*//*80*/){
            for(int h=1;h<drawZ;h+=num2/*80*//*70*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }

                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                //        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
                //        }
            }
        }


        //中间部分
        for(int w=1;w<drawX;w+=num1/*90*//*80*/){
            for(int h=1;h<drawY;h+=num2/*80*//*70*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }

        //最下边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*90*//*80*/){
            for(int h=1;h<drawZ;h+=num2/*80*//*70*/){

                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }
        update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    saveStation();
}


//-----------xiaotian  计算图案面积比列   ---totalArea总面积
void DrawWidget::getAreaRa(float areaRa[1000]){
    for(int i=0;i<=graphCount;i++){
        areaRa[i] = graphArea[i]/uptotalArea;
        cout<<"图案:"<<i+1<<"面积占比:"<<areaRa[i]<<endl;
    }

}


//移除图案，并重新添加小图案
void DrawWidget::removePath(int index){
    list<QPainterPath*>::iterator pathIndex = allPath.begin();
    int i=0;
    QPainterPath *removepath;
    for(pathIndex;pathIndex!=allPath.end();++pathIndex){
        if(i == index){
            removepath = *pathIndex;
        }
        i++;
    }

    allPath.remove(removepath);
    delete removepath;
    //移除第几个图案
    drawOk--;
    //中心点数组前移  下标从1开始。
    //记录移除的中心点坐标和当前移除图案的长度和宽度
    int removeX = spotOriginX[index+1];
    int removeY = spotOriginY[index+1];




    int currentRow = removeCurrentRow[index];
    int currentCol = removeCurrentCol[index];
    int row = removeRow[index];
    int col = removeCol[index];

    cout<<"当前行："<<currentRow<<"当前列"<<currentCol<<"行数"<<row<<"列数"<<col<<endl;

    for(int i=index+1;i<maxSize;i++){
        spotOriginX[i] = spotOriginX[i+1];
        spotOriginY[i] = spotOriginY[i+1];
        //做放大缩小用的
        spotOriginOX[i] = spotOriginOX[i+1];
        spotOriginOY[i] = spotOriginOY[i+1];
        spotOriginPOX[i] = spotOriginPOX[i+1];
        spotOriginPOY[i]=spotOriginPOY[i+1];
    }





    //重新插入图案。中心点，图案大小。  插入的图案应该为单位大小。单位大小为4个方块格。
    //按照当前中心点重新插入图案.

    /*
    path = new(QPainterPath);
    path->addRect(-20,20,40,-40);
    allPath.push_back(path);
    drawOk++;
    spotOriginX[drawOk] = removeX;
    spotOriginY[drawOk] = removeY;
    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    //压缩4 -----------------------xiaotian  调成不压缩
    stretch[drawOk]=windowScale/4;
    rotation[drawOk]=0;
    */


}

//--------------xiaotian    计算颜色矩阵
void DrawWidget::getColorRation(int colorJZ[500][500],int count,int value){

    int colorValue = 0;
    for(int i=0;i<drawOk;i++){
        //colorValue = 0;
        //取出颜色对应的数字值
        getSpotColor(i+1);
        //找出颜色对应的allcolor的index值，将index值+1即为颜色编码值
        for(int i=0;i<1000;i++){
            if(allColor.myColor[i].red() == spotColor.red() &&allColor.myColor[i].green() == spotColor.green()
                    &&allColor.myColor[i].blue() == spotColor.blue()){
                colorValue = allColor.index[i];
                break;
            }
        }

        if(colorValue == 29){
            colorValue = 0;
        }else{
            colorValue +=  1;
        }

        int currentRowNum = removeCurrentRow[i];
        int currentColNum = removeCurrentCol[i];
        int rowNum = removeRow[i];
        int colNum = removeCol[i];
        string filename = graphName[i];
        list<QString> jzpoints;
        float spotWidth;
        float spotHeigh;

        jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,filename);
        int edge[rowNum][colNum];
        for(int i=0;i<rowNum;i++){
            for(int j=0;j<colNum;j++){
                edge[i][j] = 0;
            }
        }


        list<QString>::iterator jzindex = jzpoints.begin();

        int poi=0;
        for(;jzindex!=jzpoints.end();++jzindex){
            int poj=0;
            QString str = *jzindex;
            QStringList strs = str.split(",");
            QList<QString>::Iterator it = strs.begin();
            for(;it!=strs.end();++it){
                QString valuestr = *it;

                int value = 0;
                if(valuestr == "1")
                    value = 1;
                edge[poi][poj] = value;
                ++poj;
            }
            ++poi;
        }


        //记录颜色矩阵
        int rowbegin = currentRowNum;
        int colbegin = currentColNum;
        int rowend = rowbegin + rowNum;
        int colend = colbegin + colNum;


        int m=0;
        for(int i=rowbegin;i<rowend;i++){
            int n = 0;
            for(int j=colbegin;j<colend;j++){
                if(edge[m][n] == 1){
                    colorJZ[i][j] = colorValue;//--------颜色编码值
                    colorJ[i][j] = colorValue;
                }
                n++;
            }
            m++;
        }

    }


}

//----------xiaotian  数码迷彩图案生成算法
string DrawWidget::drawBlock(int upRowNum, int upColNum,int fff)
{
    string mid = "";

    int spotReadNum;
    int debugNum=0;
    float spotWidth = 0;
    float spotHeigh = 0;
    uptotalArea = 0;
    //最上边部分
    float w=spotWidth/2.0;
    float h=spotHeigh/2.0;
    float preWidth = 0.0;
    float preHeigh = 0.0;
    float maxHeigh = 0;
    float minHeigh = 99999;
    int count = 0;

    int k = 0;
    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            colorJ[i][j] = 0;
        }
    }
    //上边
    //初始化上画布的二维数组。
    for(int currentRowNum=0;currentRowNum<upRowNum;){
        w = 0;
        preWidth = 0;
        h = k;
        preHeigh = 0;
        maxHeigh = 0;
        minHeigh = 99999;
        //线程死锁 ------------------xiaotian
        int minRowNum = 99999;
        int maxRowNum = 0;
        for(int currentColNum = 0;currentColNum<upColNum;){
            list<QPainterPath*>::iterator temp = allPath.end();
            temp--;
            int shouldFlag=1;
            list<QString> jzpoints;

            if(shouldFlag){
                int edgeO[10][10];
                //函数将文件下一个随机矩阵读入edgeO中，mid为随机矩阵的文件标号
                mid = saveGet.readDigitalSpotPoint(edgeO,spotReadNum,debugNum);
                //读出图案的长和宽，这个函数和上面的函数可以进行合并
                jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                debugNum++;
                cout<<spotWidth<<" "<<spotHeigh<<endl;
                preWidth += spotWidth;

                w =preWidth - spotWidth/2.0;
                h = spotHeigh/2.0;
                if(spotHeigh<minHeigh){
                    minHeigh = spotHeigh;
                }
                if(maxHeigh<spotHeigh){
                    maxHeigh = spotHeigh;
                }

                int colNum = spotWidth/10;

                int rowNum = spotHeigh/10;
                //
                int countValueOne = 0;
                //
                //记录图案的面积
                int graphC = 0;
                for(int i=0;i<rowNum;i++){
                    for(int j=0;j<colNum;j++){
                        if(edgeO[i][j] == 1){
                            graphC++;
                        }
                    }
                }
                spotNum[++drawOk]=graphC*4;//把斑点含点个数保存起来
                //每个图案的面积 40*40

                graphArea[graphCount] = graphC*100;
                countValueOne=graphC;
                int m = 0;
                int maxcurrentRowNum = currentRowNum+rowNum;
                int maxcurrentColNum = currentColNum+colNum;



                int rowbegin = currentRowNum;
                int colbegin = currentColNum;
                if(maxcurrentRowNum>=upRowNum){
                    rowbegin = upRowNum - rowNum;
                    maxcurrentRowNum = upRowNum;
                }
                if(maxcurrentColNum>=upColNum){
                    colbegin = upColNum - colNum;
                    maxcurrentColNum = upColNum;
                }

                //用作生成颜色矩阵的
                //--------------------------------------------------------------------------
                if(fff==1){
                    //用作生成颜色矩阵的  上
                    removeCurrentRow[graphCount] = rowbegin;
                    removeCurrentCol[graphCount] = colbegin + drawZ/10;
                }else if(fff==2){
                    //用作生成颜色矩阵的 中
                    removeCurrentRow[graphCount] = rowbegin+drawZ/10;
                    removeCurrentCol[graphCount] = colbegin;
                }else{
                    //用作生成颜色矩阵的  下
                    removeCurrentRow[graphCount] = rowbegin+(drawZ+drawY)/10;
                    removeCurrentCol[graphCount] = colbegin+drawZ/10;
                }

                removeRow[graphCount] = rowNum;
                removeCol[graphCount] = colNum;
                graphName[graphCount] = mid;
                cout<<"图案:"<<graphCount<<"面积:"<<graphArea[graphCount];
                graphCount++;

                if(rowNum<minRowNum){
                    minRowNum = rowNum;
                }
                if(rowNum>maxRowNum){
                    maxRowNum = rowNum;
                }
                currentColNum +=  colNum;
                //--------------xiaotian  计算图案中心点坐标


                midWidth=width()/2;
                midHeight=height()/2;
                if(fff==1){
                    //上边
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale+drawZ-k);
                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;
                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }

                    if((k+spotHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawZ);
                    }
                }else if(fff==2){
                    //中间
                    float lupointX =midWidth-(drawX/2+drawZ)*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale-k);
                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;
                    if((w+spotWidth/2.0)>(drawX+2*drawZ)){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-(drawX+2*drawZ));
                    }
                    if((k+spotHeigh)>drawY){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawY);
                    }

                }else{
                    //下边
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight+(drawY/2*windowScale+k);
                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;
                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }
                    if((k+spotHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawZ);
                    }
                }
                cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                //压缩4 -----------------------xiaotian  调成不压缩
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;
                showDigital = flag;
                caculateOneCurveByDigital(edgeO,spotOriginX[drawOk],spotOriginY[drawOk],10,rowNum,colNum);
                //update();    //--------xiaotian  一次性update

            }else{
                QMessageBox msgBox(this);
                msgBox.setWindowTitle(tr("提示"));
                msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                msgBox.setMinimumSize(200,100);
                msgBox.exec();
                //                return -1;
            }
            saveStation();
        }

        k+=minHeigh;
        currentRowNum +=minRowNum;
        //update();
    }
    //    uptotalArea = drawX * drawZ;

    return mid;
}

int DrawWidget::getCanvasDigital(){

    int upRowNum = 0;
    int upColNum = 0;
    //上面
    upRowNum = drawZ/10;
    upColNum = drawX/10;
    string mid1 = drawBlock(upRowNum, upColNum,1);
    uptotalArea = drawX * drawZ;
    //中间
    upRowNum = drawY/10;
    upColNum = (drawX+2*drawZ)/10;
    string mid2 = drawBlock(upRowNum, upColNum,2);
    uptotalArea += (drawX+2*drawZ) * drawY;
    //下
    upRowNum = drawZ/10;
    upColNum = drawX/10;
    string mid3 = drawBlock(upRowNum,upColNum,3);
    uptotalArea += drawX * drawZ;
    return (drawOk + 1);
}



//-----------xiaotian    测试颜色分配与斑点生成
int DrawWidget::getCanvasPointSTestByControl(int num1,int num2){
    saveGet.digitalFlag = 1;
    int spotReadNum;
    int debugNum=0;
    graphCount = 0;
    uptotalArea = 0;

    for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            colorJ[i][j] = 0;
        }
    }

    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        float spotWidth = 0;
        float spotHeigh = 0;
        string mid = "";

        //最上边部分
        float w=spotWidth/2.0;
        float h=spotHeigh/2.0;
        float preWidth = 0.0;
        float preHeigh = 0.0;
        float maxHeigh = 0;
        float minHeigh = 99999;

        int count = 0;
        int k = 0;


        //----------xiaotian    画布的二维矩阵数组
        int upRowNum = 0;
        int upColNum = 0;
        upRowNum = drawZ/10;
        upColNum = drawX/10;

        int up[upRowNum][upColNum];


        //上边
        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                up[i][j] = 0;
            }
        }

        //只画一行
        //int currentRowNum = 0;
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            //for(int i=0;i<2;i++){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }

                    //记录图案的面积
                    int graphC = 0;
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            if(edge[i][j] == 1){
                                graphC++;
                            }
                        }
                    }
                    //每个图案的面积 40*40

                    graphArea[graphCount] = graphC*100;

                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }

                    //用作生成颜色矩阵的
                    removeCurrentRow[graphCount] = rowbegin;
                    removeCurrentCol[graphCount] = colbegin + drawZ/10;
                    removeRow[graphCount] = rowNum;
                    removeCol[graphCount] = colNum;
                    graphName[graphCount] = mid;
                    cout<<"图案:"<<graphCount<<"面积:"<<graphArea[graphCount];
                    graphCount++;

                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            up[i][j] = up[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }

                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;
                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale+drawZ-k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;

                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }

                    //改成minHeigh
                    if((k+spotHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawZ);
                    }
                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();    //--------xiaotian  一次性update

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return -1;
                }
                saveStation();
            }

            k+=minHeigh;
            currentRowNum +=minRowNum;
            //update();
        }
        uptotalArea = drawX * drawZ;





        //中间
        k=0;
        upRowNum = drawY/10;
        upColNum = (drawX+2*drawZ)/10;

        int center[upRowNum][upColNum];

        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                center[i][j] = 0;
            }
        }
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;




                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }


                    //记录图案的面积
                    int graphC = 0;
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            if(edge[i][j] == 1){
                                graphC++;
                            }
                        }
                    }
                    //每个图案的面积 40*40

                    graphArea[graphCount] = graphC*100;


                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }
                    //用作生成颜色矩阵的
                    removeCurrentRow[graphCount] = rowbegin+drawZ/10;
                    removeCurrentCol[graphCount] = colbegin;
                    removeRow[graphCount] = rowNum;
                    removeCol[graphCount] = colNum;
                    graphName[graphCount] = mid;
                    cout<<"图案:"<<graphCount<<"面积:"<<graphArea[graphCount];
                    graphCount++;

                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            center[i][j] = center[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }


                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;



                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-(drawX/2+drawZ)*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale-k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;




                    if((w+spotWidth/2.0)>(drawX+2*drawZ)){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-(drawX+2*drawZ));
                    }

                    if((k+spotHeigh)>drawY){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawY);
                    }


                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return -1;
                }
                saveStation();
            }

            cout<<"第"<<++count<<"行图案"<<endl;
            /*
           k+= maxHeigh;
           currentRowNum += maxRowNum;
           */
            k+= minHeigh;
            currentRowNum += minRowNum;
        }

        uptotalArea += (drawX+2*drawZ) * drawY;





        //下边
        k=0;
        upRowNum = drawZ/10;
        upColNum = drawX/10;

        int down[upRowNum][upColNum];

        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                down[i][j] = 0;
            }
        }
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }

                    //记录图案的面积
                    int graphC = 0;
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            if(edge[i][j] == 1){
                                graphC++;
                            }
                        }
                    }
                    //每个图案的面积 40*40

                    graphArea[graphCount] = graphC*100;

                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }

                    //用作生成颜色矩阵的
                    removeCurrentRow[graphCount] = rowbegin+(drawZ+drawY)/10;
                    removeCurrentCol[graphCount] = colbegin+drawZ/10;
                    removeRow[graphCount] = rowNum;
                    removeCol[graphCount] = colNum;
                    graphName[graphCount] = mid;
                    cout<<"图案:"<<graphCount<<"面积:"<<graphArea[graphCount];
                    graphCount++;



                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            down[i][j] = down[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }



                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;



                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight+(drawY/2*windowScale+k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;

                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }

                    if((k+spotHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +spotHeigh - drawZ);
                    }


                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();       //---------xiaotian    一次性update

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return -1;
                }
                saveStation();
            }

            cout<<"第"<<++count<<"行图案"<<endl;

            k+=minHeigh;
            currentRowNum +=minRowNum;

        }
        uptotalArea += drawX * drawZ;

    }


    return (drawOk + 1);
}










//迷彩斑点图测试  ---------------xiaotian
//迷彩边长为10
void DrawWidget::getCanvasPointSTest(int num1,int num2){
    int spotReadNum;
    int debugNum=0;
    if(AutoCADFlag){
        float saveP[300][2];
        int num;

        //getCanvasBigPoint();
        //    update();

        //分布边缘的点
        //getEdgePoint();

        //    //分三个区域随机斑点，上中下






        float spotWidth = 0;
        float spotHeigh = 0;
        string mid = "";

        //最上边部分
        //int w=spotWidth/2;
        float w=spotWidth/2.0;
        float h=spotHeigh/2.0;
        float preWidth = 0.0;
        float preHeigh = 0.0;
        float maxHeigh = 0;
        float minHeigh = 99999;

        int count = 0;
        int k = 0;


        //----------xiaotian    画布的二维矩阵数组
        int upRowNum = 0;
        int upColNum = 0;
        upRowNum = drawZ/10;
        upColNum = drawX/10;

        int up[upRowNum][upColNum];


        //上边
        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                up[i][j] = 0;
            }
        }

        //for(int i=0;i<1;i++){
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }



                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }

                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            up[i][j] = up[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }



                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;

                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale+drawZ-k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;

                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }

                    //改为minHeigh
                    if((k+maxHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +maxHeigh - drawZ);
                    }


                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();    //--------xiaotian  一次性update

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return;
                }
                saveStation();
            }

            cout<<"第"<<++count<<"行图案"<<endl;
            //---------xiaotian   按照最高的
            /*
       k+= maxHeigh;
       currentRowNum += maxRowNum;
       */
            k+=minHeigh;
            currentRowNum +=minRowNum;

        }

        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                cout<<up[i][j]<<' ';
            }
            cout<<endl;
        }

        //中间部分   取最矮的重新排列
        k=0;
        upRowNum = drawY/10;
        upColNum = (drawX+2*drawZ)/10;

        int center[upRowNum][upColNum];

        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                center[i][j] = 0;
            }
        }
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;




                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }



                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }

                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            center[i][j] = center[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }


                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;

                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-(drawX/2+drawZ)*windowScale;
                    float lupointY =midHeight-(drawY/2*windowScale-k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;




                    if((w+spotWidth/2.0)>(drawX+2*drawZ)){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-(drawX+2*drawZ));
                    }

                    if((k+maxHeigh)>drawY){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +maxHeigh - drawY);
                    }


                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return;
                }
                saveStation();
            }

            cout<<"第"<<++count<<"行图案"<<endl;
            /*
           k+= maxHeigh;
           currentRowNum += maxRowNum;
           */
            k+= minHeigh;
            currentRowNum += minRowNum;
        }

        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                cout<<center[i][j]<<' ';
            }
            cout<<endl;
        }

        //28行7列画出矩形框.--------xiaotian     实验内包

        /*
        int centerX = midWidth-(drawX/2+drawZ)*windowScale;
        int centerY = midHeight-(drawY/2*windowScale);
        int rectX =centerX+ ((7-1)*10+5);
        int rectY = centerY + ((27-1)*10)+5;

        QPainterPath *path=new(QPainterPath);
        path->addRect(rectX,rectY,40,40);

        //allPath.push_back(path);
        //update();
        */





        //下边
        k=0;
        upRowNum = drawZ/10;
        upColNum = drawX/10;

        int down[upRowNum][upColNum];

        //初始化上画布的二维数组。
        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                down[i][j] = 0;
            }
        }
        for(int currentRowNum=0;currentRowNum<upRowNum;){
            w = 0;
            preWidth = 0;
            h = k;
            preHeigh = 0;
            maxHeigh = 0;
            minHeigh = 99999;
            //线程死锁 ------------------xiaotian
            int minRowNum = 99999;
            int maxRowNum = 0;
            for(int currentColNum = 0;currentColNum<upColNum;){
                //for(int j=0;j<2;j++){
                //while(w<drawX){
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                list<QString> jzpoints;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;

                    preWidth += spotWidth;
                    //preHeigh += spotHeigh;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    //计算最小的heigh
                    if(spotHeigh<minHeigh){
                        minHeigh = spotHeigh;
                    }
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    int colNum = spotWidth/10;
                    int rowNum = spotHeigh/10;
                    int edge[rowNum][colNum];
                    for(int i=0;i<rowNum;i++){
                        for(int j=0;j<colNum;j++){
                            edge[i][j] = 0;
                        }
                    }

                    list<QString>::iterator jzindex = jzpoints.begin();

                    int poi=0;
                    for(;jzindex!=jzpoints.end();++jzindex){
                        int poj=0;
                        QString str = *jzindex;
                        QStringList strs = str.split(",");
                        QList<QString>::Iterator it = strs.begin();
                        for(;it!=strs.end();++it){
                            QString valuestr = *it;

                            int value = 0;
                            if(valuestr == "1")
                                value = 1;
                            edge[poi][poj] = value;
                            ++poj;
                        }
                        ++poi;
                    }



                    int m = 0;
                    int maxcurrentRowNum = currentRowNum+rowNum;
                    int maxcurrentColNum = currentColNum+colNum;



                    int rowbegin = currentRowNum;
                    int colbegin = currentColNum;
                    if(maxcurrentRowNum>=upRowNum){
                        rowbegin = upRowNum - rowNum;
                        maxcurrentRowNum = upRowNum;
                    }
                    if(maxcurrentColNum>=upColNum){
                        colbegin = upColNum - colNum;
                        maxcurrentColNum = upColNum;
                    }

                    for(int i=rowbegin;i<maxcurrentRowNum;i++){
                        int n = 0;
                        for(int j=colbegin;j<maxcurrentColNum;j++){
                            down[i][j] = down[i][j] + edge[m][n];
                            n++;
                        }
                        m++;
                    }



                    if(rowNum<minRowNum){
                        minRowNum = rowNum;
                    }
                    if(rowNum>maxRowNum){
                        maxRowNum = rowNum;
                    }
                    currentColNum +=  colNum;

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;

                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                    midWidth=width()/2;
                    midHeight=height()/2;
                    float lupointX =midWidth-drawX/2*windowScale;
                    float lupointY =midHeight+(drawY/2*windowScale+k);

                    spotOriginX[drawOk] = lupointX + w;
                    spotOriginY[drawOk] = lupointY + h;

                    if((w+spotWidth/2.0)>drawX){
                        spotOriginX[drawOk] = spotOriginX[drawOk] - (w+spotWidth/2.0-drawX);
                    }

                    if((k+maxHeigh)>drawZ){
                        spotOriginY[drawOk] = spotOriginY[drawOk] - (k +maxHeigh - drawZ);
                    }


                    cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    //压缩4 -----------------------xiaotian  调成不压缩
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    showDigital = flag;

                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                    //update();       //---------xiaotian    一次性update

                }else{
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle(tr("提示"));
                    msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                    msgBox.setMinimumSize(200,100);
                    msgBox.exec();
                    return;
                }
                saveStation();
            }

            cout<<"第"<<++count<<"行图案"<<endl;
            /*
       k+= maxHeigh;
       currentRowNum += maxRowNum;
       */
            k+=minHeigh;
            currentRowNum +=minRowNum;

        }

        for(int i=0;i<upRowNum;i++){
            for(int j=0;j<upColNum;j++){
                cout<<down[i][j]<<' ';
            }
            cout<<endl;
        }


        /*
    k=0;
    //中间部分
    for(int k=0;k<(drawZ+drawY);){
    //for(int j=0;j<4;j++){
        w = 0;
        preWidth = 0;

        //h = k;
        //使用do while试试，否则线程死锁
        for(;w<drawX;){

                int currentk = k;
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;
                    preWidth += spotWidth;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;





                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                        midWidth=width()/2;
                        midHeight=height()/2;
                        float lupointX =midWidth-drawX/2*windowScale;
                        float lupointY =midHeight-(drawY/2*windowScale-k);

                        spotOriginX[drawOk] = lupointX + w;
                        spotOriginY[drawOk] = lupointY + h;


                        cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                        //压缩4 -----------------------xiaotian  调成不压缩
                        stretch[drawOk]=windowScale/4;
                        rotation[drawOk]=0;
                        //把刚绘制完斑点的点保存起来
                        QPointF *tempPoint;
                        oPoint.clear();
                        for(int t=1;t<num+1;t++){
                            tempPoint=new QPointF;
                            tempPoint->setX(saveP[t][0]);
                            tempPoint->setY(saveP[t][1]);
                            oPoint.push_back(tempPoint);
                            oPointAll.push_back(tempPoint);
                         }
                        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                        showDigital = flag;
                        update();
                   }else{
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle(tr("提示"));
                        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                        msgBox.setMinimumSize(200,100);
                        msgBox.exec();
                        return;
                    }
                    saveStation();
        }


       cout<<"第"<<++count<<"行图案"<<endl;

       k += maxHeigh;
    }



    //下边部分
    k=0;
    for(int k=0;k<drawZ;){
    //for(int j=0;j<2;j++){
        w = 0;
        preWidth = 0;

        //h = k;
        //使用do while试试，否则线程死锁
        for(;w<drawX;){

                int currentk = k;
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;
                    preWidth += spotWidth;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;




                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标
                        midWidth=width()/2;
                        midHeight=height()/2;
                        float lupointX =midWidth-drawX/2*windowScale;
                        float lupointY =midHeight+(drawY/2*windowScale+k);

                        spotOriginX[drawOk] = lupointX + w;
                        spotOriginY[drawOk] = lupointY + h;


                        cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                        //压缩4 -----------------------xiaotian  调成不压缩
                        stretch[drawOk]=windowScale/4;
                        rotation[drawOk]=0;
                        //把刚绘制完斑点的点保存起来
                        QPointF *tempPoint;
                        oPoint.clear();
                        for(int t=1;t<num+1;t++){
                            tempPoint=new QPointF;
                            tempPoint->setX(saveP[t][0]);
                            tempPoint->setY(saveP[t][1]);
                            oPoint.push_back(tempPoint);
                            oPointAll.push_back(tempPoint);
                         }
                        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                        showDigital = flag;
                        update();
                   }else{
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle(tr("提示"));
                        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                        msgBox.setMinimumSize(200,100);
                        msgBox.exec();
                        return;
                    }
                    saveStation();
        }


       cout<<"第"<<++count<<"行图案"<<endl;

       k += maxHeigh;
    }




    //左边部分
    k=0;
    for(int k=0;k<drawY;){
    //for(int j=0;j<2;j++){
        w = 0;
        preWidth = 0;

        //h = k;
        //使用do while试试，否则线程死锁
        for(;w<drawZ;){

                int currentk = k;
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;
                    preWidth += spotWidth;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;





                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                        midWidth=width()/2;
                        midHeight=height()/2;
                        float lupointX =midWidth-(drawX/2+drawZ)*windowScale;
                        float lupointY =midHeight-(drawY/2*windowScale-k);

                        spotOriginX[drawOk] = lupointX + w;
                        spotOriginY[drawOk] = lupointY + h;


                        cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                        //压缩4 -----------------------xiaotian  调成不压缩
                        stretch[drawOk]=windowScale/4;
                        rotation[drawOk]=0;
                        //把刚绘制完斑点的点保存起来
                        QPointF *tempPoint;
                        oPoint.clear();
                        for(int t=1;t<num+1;t++){
                            tempPoint=new QPointF;
                            tempPoint->setX(saveP[t][0]);
                            tempPoint->setY(saveP[t][1]);
                            oPoint.push_back(tempPoint);
                            oPointAll.push_back(tempPoint);
                         }
                        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                        showDigital = flag;
                        update();
                   }else{
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle(tr("提示"));
                        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                        msgBox.setMinimumSize(200,100);
                        msgBox.exec();
                        return;
                    }
                    saveStation();
        }


       cout<<"第"<<++count<<"行图案"<<endl;

       k += maxHeigh;
    }

    //右边
    k=0;
    for(int k=0;k<drawY;){
    //for(int j=0;j<2;j++){
        w = 0;
        preWidth = 0;

        //h = k;
        //使用do while试试，否则线程死锁
        for(;w<drawZ;){

                int currentk = k;
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;

                if(shouldFlag){
                    mid = saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    saveGet.readOrig(&spotWidth,&spotHeigh,mid);
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                    //cout<<"宽度为:"<<midWidth<<"高度为:"<<midHeight<<endl;
                    //preHeigh += spotHeigh;
                    preWidth += spotWidth;
                    w =preWidth - spotWidth/2.0;
                    //h = preHeigh - spotHeigh/2;
                    h = spotHeigh/2.0;
                    if(maxHeigh<spotHeigh){
                        maxHeigh = spotHeigh;
                    }

                    cout<<"w:"<<w<<"drawX为:"<<drawX<<endl;





                    //cout<<preWidth<<' '<<spotHeigh<<endl;
                    //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    //spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

                    //--------------xiaotian  计算图案中心点坐标


                        midWidth=width()/2;
                        midHeight=height()/2;
                        float lupointX =midWidth+(drawX/2)*windowScale;
                        float lupointY =midHeight-(drawY/2*windowScale-k);

                        spotOriginX[drawOk] = lupointX + w;
                        spotOriginY[drawOk] = lupointY + h;


                        cout<<"中心点x :"<<spotOriginX[drawOk]<<"中心点y:"<<spotOriginY[drawOk]<<endl;

                        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                        //压缩4 -----------------------xiaotian  调成不压缩
                        stretch[drawOk]=windowScale/4;
                        rotation[drawOk]=0;
                        //把刚绘制完斑点的点保存起来
                        QPointF *tempPoint;
                        oPoint.clear();
                        for(int t=1;t<num+1;t++){
                            tempPoint=new QPointF;
                            tempPoint->setX(saveP[t][0]);
                            tempPoint->setY(saveP[t][1]);
                            oPoint.push_back(tempPoint);
                            oPointAll.push_back(tempPoint);
                         }
                        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                        showDigital = flag;
                        update();
                   }else{
                        QMessageBox msgBox(this);
                        msgBox.setWindowTitle(tr("提示"));
                        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
                        msgBox.setMinimumSize(200,100);
                        msgBox.exec();
                        return;
                    }
                    saveStation();
        }


       cout<<"第"<<++count<<"行图案"<<endl;

       k += maxHeigh;
    }

    */
    }





    //最上边部分

    /*
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1){
            for(int h=1;h<drawZ;h+=num2){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                int x1,y1;

                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }


        if(shouldFlag){
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
        debugNum++;
        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        pointNum=0;//清空未画完斑点计数器

        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;

        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        //把刚绘制完斑点的点保存起来
        QPointF *tempPoint;
        oPoint.clear();
        for(int t=1;t<num+1;t++){
            tempPoint=new QPointF;
            tempPoint->setX(saveP[t][0]);
            tempPoint->setY(saveP[t][1]);
            oPoint.push_back(tempPoint);
            oPointAll.push_back(tempPoint);
                }
        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
//        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
//        }
            }
        }


//中间部分


//最下边部分


    //设置是数码迷彩还是仿造迷彩
showDigital = flag;
update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
       //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    saveStation();
    */
}



void DrawWidget::getCanvasPointS(int num1,int num2){
    int spotReadNum;
    int debugNum=0;
    if(AutoCADFlag){
        float saveP[300][2];
        int num;

        //getCanvasBigPoint();
        //    update();

        //分布边缘的点
        getEdgePoint();

        //    //分三个区域随机斑点，上中下



        //最左边部分
        //for(int w=1;w<drawX+2*drawZ;w+=100){
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;

                //qDebug("shhhhhhhhhhhhhhhhhhhhhhhhh:%f",windowScale);

                //这个地方中心点是按照当前应该绘制的位置设定
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;

                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;//斑点入库的时候是按照4米算的，缩小四倍正好是100，即斑点大小1米
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }


        //最右边部分
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }





        //最上边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*100*/){//120
            for(int h=1;h<drawZ;h+=num2/*100*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }

                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                //        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
                //        }
            }
        }


        //中间部分
        for(int w=60;w<drawX;w+=num1/*100*/){
            for(int h=1;h<drawY;h+=num2/*100*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;

                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }

        //最下边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*100*/){
            for(int h=1;h<drawZ;h+=num2/*100*/){

                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }
        //设置是数码迷彩还是仿造迷彩
        showDigital = flag;
        update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    saveStation();
}

//自动生成数码迷彩
void DrawWidget::getCanvasPointS2(int num1,int num2){
    int spotReadNum;
    int debugNum=0;
    if(AutoCADFlag){
        float saveP[300][2];
        int num;

        //getCanvasBigPoint();
        //    update();

        //分布边缘的点
        getEdgePoint();

        //    //分三个区域随机斑点，上中下



        //最左边部分
        //for(int w=1;w<drawX+2*drawZ;w+=100){
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;

                //qDebug("shhhhhhhhhhhhhhhhhhhhhhhhh:%f",windowScale);

                //这个地方中心点是按照当前应该绘制的位置设定
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;

                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;//斑点入库的时候是按照4米算的，缩小四倍正好是100，即斑点大小1米
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }


        //最右边部分
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }





        //最上边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*100*/){//120
            for(int h=1;h<drawZ;h+=num2/*100*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }

                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                //        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
                //        }
            }
        }


        //中间部分
        for(int w=60;w<drawX;w+=num1/*100*/){
            for(int h=1;h<drawY;h+=num2/*100*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;

                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }

        //最下边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*100*/){
            for(int h=1;h<drawZ;h+=num2/*100*/){

                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }
        //设置是数码迷彩还是仿造迷彩
        showDigital = !flag;
        update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    saveStation();
}





void DrawWidget::getCanvasPointT(int num1,int num2){
    int debugNum=0;
    int spotReadNum;
    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        //getCanvasBigPoint();
        //    update();
        getEdgePoint();

        //    //分三个区域随机斑点，上中下



        //最左边部分
        //for(int w=1;w<drawX+2*drawZ;w+=100){
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*90*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }


        //最右边部分
        for(int w=1;w<drawZ;w+=num1/*100*/){
            for(int h=20;h<drawY-50;h+=num2/*90*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //把刚绘制完斑点的点保存起来
                QPointF *tempPoint;
                oPoint.clear();
                for(int t=1;t<num+1;t++){
                    tempPoint=new QPointF;
                    tempPoint->setX(saveP[t][0]);
                    tempPoint->setY(saveP[t][1]);
                    oPoint.push_back(tempPoint);
                    oPointAll.push_back(tempPoint);
                }
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
            }
        }





        //最上边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*120*/){
            for(int h=1;h<drawZ;h+=num2/*120*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }

                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                //        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
                //        }
            }
        }


        //中间部分
        for(int w=60;w<drawX-60;w+=num1/*100*/){
            for(int h=60;h<drawY;h+=num2/*120*/){
                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }

        //最下边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=50;w<drawX-50;w+=num1/*120*/){
            for(int h=1;h<drawZ;h+=num2/*120*/){

                //检测所要填充的点是不是在已有斑点内部
                list<QPainterPath*>::iterator temp = allPath.end();
                temp--;
                int count=allPath.size();
                //qDebug("xian zai ge shu shi:%d",count);
                QPointF tempPoint1;
                int shouldFlag=1;
                float tempX,tempY;
                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                tempY=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                int x1,y1;
                while(count>0){
                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

                    tempPoint1.setX(x1);
                    tempPoint1.setY(y1);
                    if((*temp)->contains(tempPoint1)){
                        shouldFlag=0;
                        //qDebug("ssssssssssssssss");
                        break;
                    }
                    count--;
                    temp--;
                }



                if(shouldFlag){
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器

                    spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                    spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                    spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                    spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                    spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                    spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                    stretch[drawOk]=windowScale/4;
                    rotation[drawOk]=0;

                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
            }
        }
        update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    //saveStation();
}
void DrawWidget::getCanvasPointNew(){
    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        int spotReadNum;

        int debugNum=1;

        //分布边缘的点
        getEdgePoint();

        if(mainWin->returnGetSize()){
            getCanvasBigPoint();
        }


        //    update();



        //    //分三个区域随机斑点，上中下


        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        //最左边部分
        //for(int w=1;w<drawX+2*drawZ;w+=100){
        for(int w=1;w<drawZ;w+=8/*100*/){
            for(int h=2;h<drawY-10;h+=8/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                if(debugNum==1){
                    //qDebug("首个点：%d",spotReadNum);
                }
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2-drawZ+w+40;
                spotOriginY[drawOk]=midHeight-drawY/2+h+40;

                //这个地方中心点是按照当前应该绘制的位置设定
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                //spotOriginPOX和spotOriginPOY是为了实现随窗口放大缩小用的
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;//斑点入库的时候是按照4米算的，缩小四倍正好是100，即斑点大小1米
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }
                //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////

        //最右边部分


        for(int w=1;w<drawZ;w+=8/*100*/){
            for(int h=2;h<drawY-50;h+=8/*100*/){
                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }
                //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }
            }
        }


        //    for(int w=1;w<drawZ;w+=num1/*100*/){
        //        for(int h=20;h<drawY-50;h+=num2/*100*/){
        //            saveGet.readSpotPoint(2,&num,saveP);//第一个参数没用
        //            spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //            pointNum=0;//清空未画完斑点计数器

        //            spotOriginX[drawOk]=midWidth+drawX/2*windowScale+w*windowScale+40*windowScale;
        //            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+40*windowScale;
        //            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //            stretch[drawOk]=windowScale/4;
        //            rotation[drawOk]=0;

        //            //把刚绘制完斑点的点保存起来
        //            QPointF *tempPoint;
        //            oPoint.clear();
        //            for(int t=1;t<num+1;t++){
        //                tempPoint=new QPointF;
        //                tempPoint->setX(saveP[t][0]);
        //                tempPoint->setY(saveP[t][1]);
        //                oPoint.push_back(tempPoint);
        //                oPointAll.push_back(tempPoint);
        //                    }
        //            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //        }
        //    }




        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////

        //最上边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=5;w<drawX-50;w+=8/*100*/){//120
            for(int h=1;h<drawZ;h+=8/*100*/){

                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }
                //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }
            }
        }


        //        //最上边部分
        //        //for(int w=1;w<drawX;w+=100){
        //        for(int w=50;w<drawX-50;w+=num1/*100*/){//120
        //            for(int h=1;h<drawZ;h+=num2/*100*/){
        //                //检测所要填充的点是不是在已有斑点内部
        //                list<QPainterPath*>::iterator temp = allPath.end();
        //                temp--;
        //                int count=allPath.size();
        //                //qDebug("xian zai ge shu shi:%d",count);
        //                QPointF tempPoint1;
        //                int shouldFlag=1;
        //                float tempX,tempY;
        //                tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //                tempY=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
        //                int x1,y1;
        //                while(count>0){
        //                    x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        //                    y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

        //                    tempPoint1.setX(x1);
        //                    tempPoint1.setY(y1);
        //                    if((*temp)->contains(tempPoint1)){
        //                        shouldFlag=0;
        //                        //qDebug("ssssssssssssssss");
        //                        break;
        //                    }
        //                    count--;
        //                    temp--;
        //                }

        //        if(shouldFlag){
        //        saveGet.readSpotPoint(2,&num,saveP);//第一个参数没用
        //        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //        pointNum=0;//清空未画完斑点计数器

        //        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //        spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale+5*windowScale;
        //        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //        stretch[drawOk]=windowScale/4;
        //        rotation[drawOk]=0;

        //        //把刚绘制完斑点的点保存起来
        //        QPointF *tempPoint;
        //        oPoint.clear();
        //        for(int t=1;t<num+1;t++){
        //            tempPoint=new QPointF;
        //            tempPoint->setX(saveP[t][0]);
        //            tempPoint->setY(saveP[t][1]);
        //            oPoint.push_back(tempPoint);
        //            oPointAll.push_back(tempPoint);
        //                }
        //        caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //                }
        ////        else{qDebug("bu hua  bu hua  bu hua  bu hua  bu hua  ");
        ////        }
        //            }
        //        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        //中间部分
        for(int w=6;w<drawX-10;w+=8/*100*/){
            for(int h=1;h<drawY;h+=8/*100*/){

                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }

                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }
            }
        }

        ////中间部分
        //    for(int w=60;w<drawX-60;w+=num1/*100*/){
        //        for(int h=1;h<drawY;h+=num2/*100*/){
        //            //检测所要填充的点是不是在已有斑点内部
        //            list<QPainterPath*>::iterator temp = allPath.end();
        //            temp--;
        //            int count=allPath.size();
        //            //qDebug("xian zai ge shu shi:%d",count);
        //            QPointF tempPoint1;
        //            int shouldFlag=1;
        //            float tempX,tempY;
        //            tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //            tempY=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
        //            int x1,y1;
        //            while(count>0){
        //                x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        //                y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

        //                tempPoint1.setX(x1);
        //                tempPoint1.setY(y1);
        //                if((*temp)->contains(tempPoint1)){
        //                    shouldFlag=0;
        //                    //qDebug("ssssssssssssssss");
        //                    break;
        //                }
        //                count--;
        //                temp--;
        //            }



        //            if(shouldFlag){
        //            saveGet.readSpotPoint(2,&num,saveP);//第一个参数没用
        //            spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //            pointNum=0;//清空未画完斑点计数器

        //            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //            spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale+5*windowScale;
        //            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //            stretch[drawOk]=windowScale/4;
        //            rotation[drawOk]=0;

        //            //把刚绘制完斑点的点保存起来
        //            QPointF *tempPoint;
        //            oPoint.clear();
        //            for(int t=1;t<num+1;t++){
        //                tempPoint=new QPointF;
        //                tempPoint->setX(saveP[t][0]);
        //                tempPoint->setY(saveP[t][1]);
        //                oPoint.push_back(tempPoint);
        //                oPointAll.push_back(tempPoint);
        //                    }
        //            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //            }
        //        }
        //    }
        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        //最下边部分
        //for(int w=1;w<drawX;w+=100){
        for(int w=5;w<drawX-5;w+=8/*100*/){
            for(int h=1;h<drawZ;h+=8/*100*/){

                saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
                spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }

                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }
            }
        }
        //            //检测所要填充的点是不是在已有斑点内部
        //            list<QPainterPath*>::iterator temp = allPath.end();
        //            temp--;
        //            int count=allPath.size();
        //            //qDebug("xian zai ge shu shi:%d",count);
        //            QPointF tempPoint1;
        //            int shouldFlag=1;
        //            float tempX,tempY;
        //            tempX=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //            tempY=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
        //            int x1,y1;
        //            while(count>0){
        //                x1=(tempX-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(tempY-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        //                y1=(tempX-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(tempY-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

        //                tempPoint1.setX(x1);
        //                tempPoint1.setY(y1);
        //                if((*temp)->contains(tempPoint1)){
        //                    shouldFlag=0;
        //                    //qDebug("ssssssssssssssss");
        //                    break;
        //                }
        //                count--;
        //                temp--;
        //            }



        //            if(shouldFlag){
        //            saveGet.readSpotPoint(2,&num,saveP);//第一个参数没用
        //            spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //            pointNum=0;//清空未画完斑点计数器

        //            spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale+5*windowScale;
        //            spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale+5*windowScale;
        //            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //            stretch[drawOk]=windowScale/4;
        //            rotation[drawOk]=0;

        //            //把刚绘制完斑点的点保存起来
        //            QPointF *tempPoint;
        //            oPoint.clear();
        //            for(int t=1;t<num+1;t++){
        //                tempPoint=new QPointF;
        //                tempPoint->setX(saveP[t][0]);
        //                tempPoint->setY(saveP[t][1]);
        //                oPoint.push_back(tempPoint);
        //                oPointAll.push_back(tempPoint);
        //                    }
        //            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //            }
        //        }
        //    }


        //update();
    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("请在画布为五视图模式下使用该功能        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
        return;
    }
    //saveStation();
}


void DrawWidget::getCanvasBigPointS(){
    //    if(AutoCADFlag){
    //    float saveP[300][2];
    //    int num,ranNum;
    //    int thisNum=1;

    //    srand(time(0));
    //    int ranNumAll[101];//=rand()%100+1;
    //    for(int i=1;i<101;i++){
    //        ranNumAll[i]=rand()%100+1;
    //    }

    //    //上边部分
    //    for(int h=300;h<drawY+drawZ*2;h+=600){
    //        for(int w=80;w<drawX-50;w+=110){
    //            ranNum=ranNumAll[thisNum];
    //                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
    //                spotNum[++drawOk]=num;//把斑点含点个数保存起来
    //                pointNum=0;//清空未画完斑点计数器

    //                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
    //                spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranNum*windowScale+h*windowScale;
    //                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    //                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    //                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    //                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    //                stretch[drawOk]=windowScale/4;
    //                rotation[drawOk]=0;

    //                //把刚绘制完斑点的点保存起来
    //                QPointF *tempPoint;
    //                oPoint.clear();
    //                for(int t=1;t<num+1;t++){
    //                    tempPoint=new QPointF;
    //                    tempPoint->setX(saveP[t][0]);
    //                    tempPoint->setY(saveP[t][1]);
    //                    oPoint.push_back(tempPoint);
    //                    oPointAll.push_back(tempPoint);
    //                        }
    //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    //                //////////////////////////////////////////////////////////////////////

    ////                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
    ////                spotNum[++drawOk]=num;//把斑点含点个数保存起来
    ////                pointNum=0;//清空未画完斑点计数器

    ////                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
    ////                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+560*windowScale-drawZ/2*windowScale+ranNum*windowScale;
    ////                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    ////                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    ////                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    ////                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    ////                stretch[drawOk]=windowScale/4;
    ////                rotation[drawOk]=0;

    ////                //把刚绘制完斑点的点保存起来
    ////                QPointF *tempPoint1;
    ////                oPoint.clear();
    ////                for(int t=1;t<num+1;t++){
    ////                    tempPoint1=new QPointF;
    ////                    tempPoint1->setX(saveP[t][0]);
    ////                    tempPoint1->setY(saveP[t][1]);
    ////                    oPoint.push_back(tempPoint1);
    ////                    oPointAll.push_back(tempPoint1);
    ////                        }
    ////                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    //                thisNum++;
    //                thisNum=thisNum%100+1;

    //        }
    //    }
    ////        int addNum=1;
    ////        for(int w=80;w<drawX-50;w+=110){
    ////            for(int h=600;h<drawY+drawZ*2-300;h+=600){
    ////            saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
    ////            spotNum[++drawOk]=num;//把斑点含点个数保存起来
    ////            pointNum=0;//清空未画完斑点计数器

    ////            spotOriginX[drawOk]=spotOriginX[addNum];//midWidth-drawX/2*windowScale+w*windowScale;
    ////            spotOriginY[drawOk]=spotOriginY[addNum]+h*windowScale;//midHeight-drawY/2*windowScale+560*windowScale-drawZ/2*windowScale+ranNum*windowScale;
    ////            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    ////            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    ////            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    ////            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    ////            stretch[drawOk]=windowScale/4;
    ////            rotation[drawOk]=0;

    ////            //把刚绘制完斑点的点保存起来
    ////            QPointF *tempPoint1;
    ////            oPoint.clear();
    ////            for(int t=1;t<num+1;t++){
    ////                tempPoint1=new QPointF;
    ////                tempPoint1->setX(saveP[t][0]);
    ////                tempPoint1->setY(saveP[t][1]);
    ////                oPoint.push_back(tempPoint1);
    ////                oPointAll.push_back(tempPoint1);
    ////                    }
    ////            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    ////            addNum++;
    ////        }
    ////        }
    //        update();

    //    }
}
void DrawWidget::getCanvasBigPointT(){
    //    if(AutoCADFlag){
    //    float saveP[300][2];
    //    int num,ranNum;
    //    int thisNum=1;

    //    srand(time(0));
    //    int ranNumAll[101];//=rand()%100+1;
    //    for(int i=1;i<101;i++){
    //        ranNumAll[i]=rand()%100+1;
    //    }

    //    //上下部分
    //    for(int h=300;h<drawY+drawZ*2;h+=600){
    //        for(int w=100;w<drawX-60;w+=120){
    //            ranNum=ranNumAll[thisNum];
    //                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
    //                spotNum[++drawOk]=num;//把斑点含点个数保存起来
    //                pointNum=0;//清空未画完斑点计数器

    //                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
    //                spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranNum*windowScale+h*windowScale;
    //                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    //                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    //                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    //                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    //                stretch[drawOk]=windowScale/4;
    //                rotation[drawOk]=0;

    //                //把刚绘制完斑点的点保存起来
    //                QPointF *tempPoint;
    //                oPoint.clear();
    //                for(int t=1;t<num+1;t++){
    //                    tempPoint=new QPointF;
    //                    tempPoint->setX(saveP[t][0]);
    //                    tempPoint->setY(saveP[t][1]);
    //                    oPoint.push_back(tempPoint);
    //                    oPointAll.push_back(tempPoint);
    //                        }
    //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
    ////                spotNum[++drawOk]=num;//把斑点含点个数保存起来
    ////                pointNum=0;//清空未画完斑点计数器

    ////                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
    ////                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+h*windowScale-drawZ/2*windowScale+ranNum*windowScale;
    ////                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
    ////                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
    ////                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
    ////                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
    ////                stretch[drawOk]=windowScale/4;
    ////                rotation[drawOk]=0;

    ////                //把刚绘制完斑点的点保存起来
    ////                QPointF *tempPoint1;
    ////                oPoint.clear();
    ////                for(int t=1;t<num+1;t++){
    ////                    tempPoint1=new QPointF;
    ////                    tempPoint1->setX(saveP[t][0]);
    ////                    tempPoint1->setY(saveP[t][1]);
    ////                    oPoint.push_back(tempPoint1);
    ////                    oPointAll.push_back(tempPoint1);
    ////                        }
    ////                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


    ////                thisNum++;
    ////                thisNum=thisNum%100+1;
    //        }
    //       }


    //        update();

    //    }
}


void DrawWidget::getDigitalCanvas(QPainter &p){

    //QPainterPath temp;
    //    for(int i=1;i<drawZ;i+=18/*100*/){
    //        for(int j=2;j<drawY;j+=18/*100*/){
    //    for(float i=midWidth-0.5*drawX-drawZ;i<midWidth-0.5*drawX;i+=18){
    //        for(float j=midHeight-0.5*drawY;j<midHeight+0.5*drawY;j+=18){

    if(drawOk!=0){
        //中间竖着的三部分
        list<QPainterPath*>::iterator temp;
        int count;
        float x,y;
        p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
        int rectNum=(2*drawZ+drawY)*drawX/(rectSize*rectSize);
        float colorAXY[rectNum][2],colorBXY[rectNum][2],colorCXY[rectNum][2],colorDXY[rectNum][2];
        for(int i=0;i<rectNum;i++){
            colorAXY[i][0]=0;
            colorAXY[i][1]=0;

            colorBXY[i][0]=0;
            colorBXY[i][1]=0;

            colorCXY[i][0]=0;
            colorCXY[i][1]=0;

            colorDXY[i][0]=0;
            colorDXY[i][1]=0;
        }
        int colorANum=0,colorBNum=0,colorCNum=0,colorDNum=0;
        QColor colorA(255,255,255),colorB(255,255,255),colorC(255,255,255),colorD(255,255,255);

        for(float i=midWidth-0.5*drawX;i<midWidth+0.5*drawX;i+=rectSize){
            for(float j=midHeight-0.5*drawY-drawZ;j<midHeight+0.5*drawY+drawZ;j+=rectSize){
                //qDebug("%f  %f  %f   %f     %f",midWidth,midHeight,canvasX,canvasY,drawZ);
                //p.drawRect(i,j,18,18);
                temp = allPath.begin();
                count=1;
                //qDebug("start:%f  %f",i,j);
                for(;temp!=allPath.end();++temp){
                    ////真实的点到某个斑点的坐标系
                    x=(i-spotOriginX[count])*cos(rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(rotation[count]/180*PI)/stretch[count];
                    //temp.addRect();
                    getSpotColor(count);
                    if((*temp)->intersects(QRect(x,y,rectSize/stretch[count],rectSize/stretch[count]))){
                        if(colorANum==0&&spotColor!=backGroundColor){
                            colorA=spotColor;
                            colorAXY[colorANum][0]=i;
                            colorAXY[colorANum][1]=j;
                            //qDebug("xs,ys:%f  %f",i,j);
                            //qDebug("%d",colorANum);
                            colorANum++;
                            break;
                        }else if(colorA==spotColor){
                            colorAXY[colorANum][0]=i;
                            colorAXY[colorANum][1]=j;
                            colorANum++;
                            break;
                        }else if(colorBNum==0&&spotColor!=backGroundColor){
                            colorB=spotColor;
                            colorBXY[colorBNum][0]=i;
                            colorBXY[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorB==spotColor){
                            colorBXY[colorBNum][0]=i;
                            colorBXY[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorCNum==0&&spotColor!=backGroundColor){
                            colorC=spotColor;
                            colorCXY[colorCNum][0]=i;
                            colorCXY[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }else if(colorC==spotColor){
                            colorC=spotColor;
                            colorCXY[colorCNum][0]=i;
                            colorCXY[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }
                    }
                    count++;
                }
                if(temp==allPath.end()){
                    colorD=backGroundColor;
                    colorDXY[colorDNum][0]=i;
                    colorDXY[colorDNum][1]=j;
                    colorDNum++;
                }
            }
        }


        p.setBrush(colorA);
        p.setPen(Qt::NoPen);
        for(int i=0;i<colorANum;i++){
            p.drawRects(&QRectF(colorAXY[i][0],colorAXY[i][1],rectSize,rectSize),1);
        }


        p.setBrush(colorB);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorBNum;i++){
            p.drawRects(&QRectF(colorBXY[i][0],colorBXY[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }

        p.setBrush(colorC);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorCNum;i++){
            p.drawRects(&QRectF(colorCXY[i][0],colorCXY[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }

        //colorD.setRgb(255,0,0);
        p.setBrush(colorD);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorDNum;i++){
            p.drawRects(&QRectF(colorDXY[i][0],colorDXY[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }
        p.setBrush(Qt::NoBrush);



        //最左边部分
        p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
        rectNum=drawZ*drawY/(rectSize*rectSize);
        float colorAXYL[rectNum][2],colorBXYL[rectNum][2],colorCXYL[rectNum][2],colorDXYL[rectNum][2];
        for(int i=0;i<rectNum;i++){
            colorAXYL[i][0]=0;
            colorAXYL[i][1]=0;

            colorBXYL[i][0]=0;
            colorBXYL[i][1]=0;

            colorCXYL[i][0]=0;
            colorCXYL[i][1]=0;

            colorDXYL[i][0]=0;
            colorDXYL[i][1]=0;
        }
        //int colorANumL=0,colorBNumL=0,colorCNumL=0,colorDNum=0;
        //QColor colorA,colorB,colorC,colorD;

        colorANum=0,colorBNum=0,colorCNum=0,colorDNum=0;
        for(float i=midWidth-0.5*drawX-drawZ;i<midWidth-0.5*drawX;i+=rectSize){
            for(float j=midHeight-0.5*drawY;j<midHeight+0.5*drawY;j+=rectSize){
                //qDebug("%f  %f  %f   %f     %f",midWidth,midHeight,canvasX,canvasY,drawZ);
                //p.drawRect(i,j,18,18);
                temp = allPath.begin();
                count=1;
                //qDebug("start:%f  %f",i,j);
                for(;temp!=allPath.end();++temp){
                    ////真实的点到某个斑点的坐标系
                    x=(i-spotOriginX[count])*cos(rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(rotation[count]/180*PI)/stretch[count];
                    //tempL.addRect();
                    getSpotColor(count);
                    if((*temp)->intersects(QRect(x,y,rectSize/stretch[count],rectSize/stretch[count]))){
                        if(colorANum==0&&spotColor!=backGroundColor){
                            colorA=spotColor;
                            colorAXYL[colorANum][0]=i;
                            colorAXYL[colorANum][1]=j;
                            //qDebug("xs,ys:%f  %f",i,j);
                            //qDebug("%d",colorANum);
                            colorANum++;
                            break;
                        }else if(colorA==spotColor){
                            colorAXYL[colorANum][0]=i;
                            colorAXYL[colorANum][1]=j;
                            colorANum++;
                            break;
                        }else if(colorBNum==0&&spotColor!=backGroundColor){
                            colorB=spotColor;
                            colorBXYL[colorBNum][0]=i;
                            colorBXYL[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorB==spotColor){
                            colorBXYL[colorBNum][0]=i;
                            colorBXYL[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorCNum==0&&spotColor!=backGroundColor){
                            colorC=spotColor;
                            colorCXYL[colorCNum][0]=i;
                            colorCXYL[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }else if(colorC==spotColor){
                            colorC=spotColor;
                            colorCXYL[colorCNum][0]=i;
                            colorCXYL[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }/*else{
            if(spotColor==colorA){
                colorAXY[colorANum][0]=i;
                colorAXY[colorANum][1]=j;
                //qDebug("x,y:%f  %f",i,j);
                //qDebug("%d",colorANum);
                colorANum++;
                break;
            }else if(spotColor==colorB){
                colorBXY[colorBNum][0]=i;
                colorBXY[colorBNum][1]=j;
                colorBNum++;
                break;
            }else if(spotColor==colorC){
                colorCXY[colorCNum][0]=i;
                colorCXY[colorCNum][1]=j;
                colorCNum++;
                break;
            }
        }*/
                    }/*else{
        colorD=spotColor;
        colorDXY[colorDNum][0]=i;
        colorDXY[colorDNum][1]=j;
        colorDNum++;
    }*/
                    count++;
                }
                if(temp==allPath.end()){
                    colorD=backGroundColor;
                    colorDXYL[colorDNum][0]=i;
                    colorDXYL[colorDNum][1]=j;
                    colorDNum++;
                }
            }
        }


        p.setBrush(colorA);
        p.setPen(Qt::NoPen);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorANum;i++){
            p.drawRects(&QRectF(colorAXYL[i][0],colorAXYL[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }


        p.setBrush(colorB);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorBNum;i++){
            p.drawRects(&QRectF(colorBXYL[i][0],colorBXYL[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }

        p.setBrush(colorC);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorCNum;i++){
            p.drawRects(&QRectF(colorCXYL[i][0],colorCXYL[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }
        p.setBrush(colorD);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorDNum;i++){
            p.drawRects(&QRectF(colorDXYL[i][0],colorDXYL[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }
        p.setBrush(Qt::NoBrush);



        //最右边部分
        p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
        rectNum=drawZ*drawY/(rectSize*rectSize);
        float colorAXYR[rectNum][2],colorBXYR[rectNum][2],colorCXYR[rectNum][2],colorDXYR[rectNum][2];
        for(int i=0;i<rectNum;i++){
            colorAXYR[i][0]=0;
            colorAXYR[i][1]=0;

            colorBXYR[i][0]=0;
            colorBXYR[i][1]=0;

            colorCXYR[i][0]=0;
            colorCXYR[i][1]=0;

            colorDXYR[i][0]=0;
            colorDXYR[i][1]=0;
        }
        //int colorANumL=0,colorBNumL=0,colorCNumL=0,colorDNum=0;
        //QColor colorA,colorB,colorC,colorD;

        colorANum=0,colorBNum=0,colorCNum=0,colorDNum=0;
        for(float i=midWidth+0.5*drawX;i<midWidth+0.5*drawX+drawZ;i+=rectSize){
            for(float j=midHeight-0.5*drawY;j<midHeight+0.5*drawY;j+=rectSize){
                //qDebug("%f  %f  %f   %f     %f",midWidth,midHeight,canvasX,canvasY,drawZ);
                //p.drawRect(i,j,18,18);
                temp = allPath.begin();
                count=1;
                //qDebug("start:%f  %f",i,j);
                for(;temp!=allPath.end();++temp){
                    ////真实的点到某个斑点的坐标系
                    x=(i-spotOriginX[count])*cos(rotation[count]/180*PI)/stretch[count]-(j-spotOriginY[count])*sin(rotation[count]/180*PI)/stretch[count];
                    y=(i-spotOriginX[count])*sin(rotation[count]/180*PI)/stretch[count]+(j-spotOriginY[count])*cos(rotation[count]/180*PI)/stretch[count];
                    //tempL.addRect();
                    getSpotColor(count);
                    if((*temp)->intersects(QRect(x,y,rectSize/stretch[count],rectSize/stretch[count]))){
                        if(colorANum==0&&spotColor!=backGroundColor){
                            colorA=spotColor;
                            colorAXYR[colorANum][0]=i;
                            colorAXYL[colorANum][1]=j;
                            //qDebug("xs,ys:%f  %f",i,j);
                            //qDebug("%d",colorANum);
                            colorANum++;
                            break;
                        }else if(colorA==spotColor){
                            colorAXYR[colorANum][0]=i;
                            colorAXYR[colorANum][1]=j;
                            colorANum++;
                            break;
                        }else if(colorBNum==0&&spotColor!=backGroundColor){
                            colorB=spotColor;
                            colorBXYR[colorBNum][0]=i;
                            colorBXYR[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorB==spotColor){
                            colorBXYR[colorBNum][0]=i;
                            colorBXYR[colorBNum][1]=j;
                            colorBNum++;
                            break;
                        }else if(colorCNum==0&&spotColor!=backGroundColor){
                            colorC=spotColor;
                            colorCXYR[colorCNum][0]=i;
                            colorCXYR[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }else if(colorC==spotColor){
                            colorC=spotColor;
                            colorCXYR[colorCNum][0]=i;
                            colorCXYR[colorCNum][1]=j;
                            colorCNum++;
                            break;
                        }/*else{
            if(spotColor==colorA){
                colorAXY[colorANum][0]=i;
                colorAXY[colorANum][1]=j;
                //qDebug("x,y:%f  %f",i,j);
                //qDebug("%d",colorANum);
                colorANum++;
                break;
            }else if(spotColor==colorB){
                colorBXY[colorBNum][0]=i;
                colorBXY[colorBNum][1]=j;
                colorBNum++;
                break;
            }else if(spotColor==colorC){
                colorCXY[colorCNum][0]=i;
                colorCXY[colorCNum][1]=j;
                colorCNum++;
                break;
            }
        }*/
                    }/*else{
        colorD=spotColor;
        colorDXY[colorDNum][0]=i;
        colorDXY[colorDNum][1]=j;
        colorDNum++;
    }*/
                    count++;
                }
                if(temp==allPath.end()){
                    colorD=backGroundColor;
                    colorDXYR[colorDNum][0]=i;
                    colorDXYR[colorDNum][1]=j;
                    colorDNum++;
                }
            }
        }


        p.setBrush(colorA);
        p.setPen(Qt::NoPen);
        qDebug("color num: %d,%d,%d,%d",colorANum,colorBNum,colorCNum,colorDNum);
        for(int i=0;i<colorANum;i++){
            p.drawRects(&QRectF(colorAXYR[i][0],colorAXYR[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }


        p.setBrush(colorB);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorBNum;i++){
            p.drawRects(&QRectF(colorBXYR[i][0],colorBXYR[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }

        p.setBrush(colorC);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorCNum;i++){
            p.drawRects(&QRectF(colorCXYR[i][0],colorCXYR[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }
        p.setBrush(colorD);
        //qDebug("%d",colorANum);
        for(int i=0;i<colorDNum;i++){
            p.drawRects(&QRectF(colorDXYR[i][0],colorDXYR[i][1],rectSize,rectSize),1);
            //qDebug("11111:%f   %f",colorAXY[i][0],colorAXY[i][1]);
        }
        p.setBrush(Qt::NoBrush);


    }

}

void DrawWidget::getEdgePoint(){
    float saveP[300][2];
    int num;
    int spotReadNum;
    int debugNum=0;
    //QPointF *tempPoint;
    //第一个边
    for(int h=1;h<drawZ-50;h+=10){
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
        debugNum++;

        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        drawOk1++;
        pointNum=0;//清空未画完斑点计数器

        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+10;
        spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale;
        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;

        int detectI=1;
        if(drawOk!=1){
            for(detectI=1;detectI<11;detectI++){
                if(collisonDetection(num,saveP)){
                    //qDebug("detect%d",detectI);
                    break;
                }
                else{
                    drawOk--;
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数为调用的文件序列中的哪个斑点
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                }
            }
        }
        //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
        if(detectI<11){
            //qDebug("绘制第%d个点",drawOk);
            //把刚绘制完斑点的点保存起来
            QPointF *tempPoint;
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


            //////////////////与另一条边对应
            spotNum[++drawOk]=num;//把斑点含点个数保存起来
            drawOk1++;
            pointNum=0;//清空未画完斑点计数器

            spotOriginX[drawOk]=midWidth-drawX/2*windowScale-drawZ*windowScale+h*windowScale;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale-10;
            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
            stretch[drawOk]=windowScale/4;
            rotation[drawOk]=-90;

            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        }
        else{
            drawOk--;
        }


        //把刚绘制完斑点的点保存起来
        //            QPointF *tempPoint;
        //            oPoint.clear();
        //            for(int t=1;t<num+1;t++){
        //                tempPoint=new QPointF;
        //                tempPoint->setX(saveP[t][0]);
        //                tempPoint->setY(saveP[t][1]);
        //                oPoint.push_back(tempPoint);
        //                oPointAll.push_back(tempPoint);
        //                    }
        //            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath



    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    //第二个边
    for(int h=1;h<drawZ-50;h+=80){
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
        debugNum++;
        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        drawOk2++;
        pointNum=0;//清空未画完斑点计数器

        spotOriginX[drawOk]=midWidth+drawX/2*windowScale-10;
        spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+h*windowScale;
        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;



        int detectI=1;
        if(drawOk!=1){
            for(detectI=1;detectI<11;detectI++){
                if(collisonDetection(num,saveP)){
                    //qDebug("detect%d",detectI);
                    break;
                }
                else{
                    drawOk--;
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                }
            }
        }
        //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
        if(detectI<11){
            //qDebug("绘制第%d个点",drawOk);
            //把刚绘制完斑点的点保存起来
            QPointF *tempPoint;
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


            //////////////////与另一条边对应
            spotNum[++drawOk]=num;//把斑点含点个数保存起来
            drawOk2++;
            pointNum=0;//清空未画完斑点计数器

            spotOriginX[drawOk]=midWidth+drawX/2*windowScale+drawZ*windowScale-h*windowScale;
            spotOriginY[drawOk]=midHeight-drawY/2*windowScale-10;
            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
            stretch[drawOk]=windowScale/4;
            rotation[drawOk]=90;

            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        }
        else{
            drawOk--;
        }




        //              //把刚绘制完斑点的点保存起来
        //              QPointF *tempPoint;
        //              oPoint.clear();
        //              for(int t=1;t<num+1;t++){
        //                  tempPoint=new QPointF;
        //                  tempPoint->setX(saveP[t][0]);
        //                  tempPoint->setY(saveP[t][1]);
        //                  oPoint.push_back(tempPoint);
        //                  oPointAll.push_back(tempPoint);
        //                      }
        //              caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //   //////////////////////////////////////////////////////////////////////////////////
        //              spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //              drawOk2++;
        //              pointNum=0;//清空未画完斑点计数器

        //              spotOriginX[drawOk]=midWidth+drawX/2*windowScale+drawZ*windowScale-h*windowScale;
        //              spotOriginY[drawOk]=midHeight-drawY/2*windowScale-10;
        //              spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //              spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //              spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //              spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //              stretch[drawOk]=windowScale/4;
        //              rotation[drawOk]=90;

        //              oPoint.clear();
        //              for(int t=1;t<num+1;t++){
        //                  tempPoint=new QPointF;
        //                  tempPoint->setX(saveP[t][0]);
        //                  tempPoint->setY(saveP[t][1]);
        //                  oPoint.push_back(tempPoint);
        //                  oPointAll.push_back(tempPoint);
        //                      }
        //              caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////

    //第三个边
    for(int h=50;h<drawZ;h+=80){
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
        debugNum++;
        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        drawOk3++;
        pointNum=0;//清空未画完斑点计数器

        spotOriginX[drawOk]=midWidth-drawX/2*windowScale+10;
        spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale;
        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;


        int detectI=1;
        if(drawOk!=1){
            for(detectI=1;detectI<11;detectI++){
                if(collisonDetection(num,saveP)){
                    //qDebug("detect%d",detectI);
                    break;
                }
                else{
                    drawOk--;
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                }
            }
        }
        //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
        if(detectI<11){
            //qDebug("绘制第%d个点",drawOk);
            //把刚绘制完斑点的点保存起来
            QPointF *tempPoint;
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


            //////////////////与另一条边对应
            spotNum[++drawOk]=num;//把斑点含点个数保存起来
            drawOk3++;
            pointNum=0;//清空未画完斑点计数器

            spotOriginX[drawOk]=midWidth-drawX/2*windowScale-h*windowScale;
            spotOriginY[drawOk]=midHeight+drawY/2*windowScale+10;
            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
            stretch[drawOk]=windowScale/4;
            rotation[drawOk]=90;

            //把刚绘制完斑点的点保存起来
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        }
        else{
            drawOk--;
        }




        //                //把刚绘制完斑点的点保存起来
        //                QPointF *tempPoint;
        //                oPoint.clear();
        //                for(int t=1;t<num+1;t++){
        //                    tempPoint=new QPointF;
        //                    tempPoint->setX(saveP[t][0]);
        //                    tempPoint->setY(saveP[t][1]);
        //                    oPoint.push_back(tempPoint);
        //                    oPointAll.push_back(tempPoint);
        //                        }
        //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        ///////////////////////////////////////////////////////////
        //                spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //                drawOk3++;
        //                pointNum=0;//清空未画完斑点计数器

        //                spotOriginX[drawOk]=midWidth-drawX/2*windowScale-h*windowScale;
        //                spotOriginY[drawOk]=midHeight+drawY/2*windowScale+10;
        //                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //                stretch[drawOk]=windowScale/4;
        //                rotation[drawOk]=90;

        //                //把刚绘制完斑点的点保存起来
        //                oPoint.clear();
        //                for(int t=1;t<num+1;t++){
        //                    tempPoint=new QPointF;
        //                    tempPoint->setX(saveP[t][0]);
        //                    tempPoint->setY(saveP[t][1]);
        //                    oPoint.push_back(tempPoint);
        //                    oPointAll.push_back(tempPoint);
        //                        }
        //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    //第四个边
    for(int h=50;h<drawZ;h+=80){
        saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
        debugNum++;
        spotNum[++drawOk]=num;//把斑点含点个数保存起来
        drawOk4++;
        pointNum=0;//清空未画完斑点计数器

        spotOriginX[drawOk]=midWidth+drawX/2*windowScale-10;
        spotOriginY[drawOk]=midHeight+drawY/2*windowScale+h*windowScale;
        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        stretch[drawOk]=windowScale/4;
        rotation[drawOk]=0;


        int detectI=1;
        if(drawOk!=1){
            for(detectI=1;detectI<11;detectI++){
                if(collisonDetection(num,saveP)){
                    //qDebug("detect%d",detectI);
                    break;
                }
                else{
                    drawOk--;
                    saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                    debugNum++;
                    spotNum[++drawOk]=num;//把斑点含点个数保存起来
                    pointNum=0;//清空未画完斑点计数器
                }
            }
        }
        //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
        if(detectI<11){
            //qDebug("绘制第%d个点",drawOk);
            //把刚绘制完斑点的点保存起来
            QPointF *tempPoint;
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


            //////////////////与另一条边对应
            spotNum[++drawOk]=num;//把斑点含点个数保存起来
            drawOk4++;
            pointNum=0;//清空未画完斑点计数器

            spotOriginX[drawOk]=midWidth+drawX/2*windowScale+h*windowScale;
            spotOriginY[drawOk]=midHeight+drawY/2*windowScale+10;
            spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
            spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
            spotOriginPOX[drawOk]=spotOriginOX[drawOk];
            spotOriginPOY[drawOk]=spotOriginOY[drawOk];
            stretch[drawOk]=windowScale/4;
            rotation[drawOk]=-90;

            //把刚绘制完斑点的点保存起来
            oPoint.clear();
            for(int t=1;t<num+1;t++){
                tempPoint=new QPointF;
                tempPoint->setX(saveP[t][0]);
                tempPoint->setY(saveP[t][1]);
                oPoint.push_back(tempPoint);
                oPointAll.push_back(tempPoint);
            }
            caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        }
        else{
            drawOk--;
        }



        //                  //把刚绘制完斑点的点保存起来
        //                  QPointF *tempPoint;
        //                  oPoint.clear();
        //                  for(int t=1;t<num+1;t++){
        //                      tempPoint=new QPointF;
        //                      tempPoint->setX(saveP[t][0]);
        //                      tempPoint->setY(saveP[t][1]);
        //                      oPoint.push_back(tempPoint);
        //                      oPointAll.push_back(tempPoint);
        //                          }
        //                  caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
        //////////////////////////////////////////////////////////////////////////////////////////
        //                  spotNum[++drawOk]=num;//把斑点含点个数保存起来
        //                  drawOk4++;
        //                  pointNum=0;//清空未画完斑点计数器

        //                  spotOriginX[drawOk]=midWidth+drawX/2*windowScale+h*windowScale;
        //                  spotOriginY[drawOk]=midHeight+drawY/2*windowScale+10;
        //                  spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        //                  spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
        //                  spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        //                  spotOriginPOY[drawOk]=spotOriginOY[drawOk];
        //                  stretch[drawOk]=windowScale/4;
        //                  rotation[drawOk]=-90;

        //                  //把刚绘制完斑点的点保存起来
        //                  oPoint.clear();
        //                  for(int t=1;t<num+1;t++){
        //                      tempPoint=new QPointF;
        //                      tempPoint->setX(saveP[t][0]);
        //                      tempPoint->setY(saveP[t][1]);
        //                      oPoint.push_back(tempPoint);
        //                      oPointAll.push_back(tempPoint);
        //                          }
        //                  caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
    }
    //          //qDebug("######################:   %d   %d   %d   %d",drawOk1,drawOk2,drawOk3,drawOk4);
}

void DrawWidget::getCanvasBigPoint(){
    if(AutoCADFlag){
        float saveP[300][2];
        int num;
        int thisNum=1;
        int spotReadNum;
        int debugNum=0;

        srand(time(0));
        int ranNumAll[101];//=rand()%100+1;
        for(int i=1;i<101;i++){
            ranNumAll[i]=rand()%100+1;
        }

        //上边部分
        for(int h=300;h<drawY+drawZ*2;h+=100){
            for(int w=80;w<drawX-50;w+=100){

                //saveGet.readSpotPoint(spotReadNum,&num,saveP,debugNum);//第一个参数没用
                saveGet.readBigSpotPoint(&num,saveP,debugNum);
                debugNum++;
                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                //            if(debugNum==1){
                //                qDebug("首个点：%d",spotReadNum);
                //            }
                pointNum=0;//清空未画完斑点计数器

                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
                spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale/*+ranNum*windowScale*/+h*windowScale;
                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                stretch[drawOk]=windowScale/4;
                rotation[drawOk]=0;

                //qDebug("drawOk shi:%d   %d",drawOk,num);
                int detectI=1;
                if(drawOk!=1){
                    for(detectI=1;detectI<11;detectI++){
                        if(collisonDetection(num,saveP)){
                            //qDebug("detect%d",detectI);
                            break;
                        }
                        else{
                            drawOk--;
                            saveGet.readBigSpotPoint(&num,saveP,debugNum);
                            debugNum++;
                            spotNum[++drawOk]=num;//把斑点含点个数保存起来
                            pointNum=0;//清空未画完斑点计数器
                        }
                    }
                }
                //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d@@@@@@%d$$$$$%d",detectI,w,h);
                if(detectI<11){
                    //qDebug("绘制第%d个点",drawOk);
                    //把刚绘制完斑点的点保存起来
                    QPointF *tempPoint;
                    oPoint.clear();
                    for(int t=1;t<num+1;t++){
                        tempPoint=new QPointF;
                        tempPoint->setX(saveP[t][0]);
                        tempPoint->setY(saveP[t][1]);
                        oPoint.push_back(tempPoint);
                        oPointAll.push_back(tempPoint);
                    }
                    caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                }
                else{
                    drawOk--;
                }


                //for(int h=1;h<drawY;h+=600){
                //            ranNum=ranNumAll[thisNum];
                //                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
                //                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                //                pointNum=0;//清空未画完斑点计数器

                //                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
                //                spotOriginY[drawOk]=midHeight-drawY/2*windowScale-drawZ*windowScale+ranNum*windowScale+h*windowScale;
                //                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                //                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                //                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                //                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                //                stretch[drawOk]=windowScale/4;
                //                rotation[drawOk]=0;

                //                //把刚绘制完斑点的点保存起来
                //                QPointF *tempPoint;
                //                oPoint.clear();
                //                for(int t=1;t<num+1;t++){
                //                    tempPoint=new QPointF;
                //                    tempPoint->setX(saveP[t][0]);
                //                    tempPoint->setY(saveP[t][1]);
                //                    oPoint.push_back(tempPoint);
                //                    oPointAll.push_back(tempPoint);
                //                        }
                //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                //////////////////////////////////////////////////////////////////////

                //                saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
                //                spotNum[++drawOk]=num;//把斑点含点个数保存起来
                //                pointNum=0;//清空未画完斑点计数器

                //                spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
                //                spotOriginY[drawOk]=midHeight-drawY/2*windowScale+550*windowScale-drawZ/2*windowScale+ranNum*windowScale;
                //                spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
                //                spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
                //                spotOriginPOX[drawOk]=spotOriginOX[drawOk];
                //                spotOriginPOY[drawOk]=spotOriginOY[drawOk];
                //                stretch[drawOk]=windowScale/4;
                //                rotation[drawOk]=0;

                //                //把刚绘制完斑点的点保存起来
                //                QPointF *tempPoint1;
                //                oPoint.clear();
                //                for(int t=1;t<num+1;t++){
                //                    tempPoint1=new QPointF;
                //                    tempPoint1->setX(saveP[t][0]);
                //                    tempPoint1->setY(saveP[t][1]);
                //                    oPoint.push_back(tempPoint1);
                //                    oPointAll.push_back(tempPoint1);
                //                        }
                //                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath


                thisNum++;
                thisNum=thisNum%100+1;

            }
            //        int addNum=1;
            //for(int w=80;w<drawX-50;w+=100){
            //        saveGet.readBigSpotPoint(&num,saveP);//第一个参数没用
            //        spotNum[++drawOk]=num;//把斑点含点个数保存起来
            //        pointNum=0;//清空未画完斑点计数器

            //        spotOriginX[drawOk]=spotOriginX[addNum];
            //        spotOriginY[drawOk]=spotOriginY[addNum]+550*windowScale;
            //        //spotOriginX[drawOk]=midWidth-drawX/2*windowScale+w*windowScale;
            //        //spotOriginY[drawOk]=midHeight-drawY/2*windowScale+550*windowScale-drawZ/2*windowScale+ranNum*windowScale;
            //        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
            //        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;
            //        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
            //        spotOriginPOY[drawOk]=spotOriginOY[drawOk];
            //        stretch[drawOk]=windowScale/4;
            //        rotation[drawOk]=0;

            //        //把刚绘制完斑点的点保存起来
            //        QPointF *tempPoint1;
            //        oPoint.clear();
            //        for(int t=1;t<num+1;t++){
            //            tempPoint1=new QPointF;
            //            tempPoint1->setX(saveP[t][0]);
            //            tempPoint1->setY(saveP[t][1]);
            //            oPoint.push_back(tempPoint1);
            //            oPointAll.push_back(tempPoint1);
            //                }
            //        caculateOneCurve();
            //        addNum++;
            //        }//计算最后一个斑点的数据，包括thePoint和cPath

            //    //下边部分
            //        for(int w=80;w<drawX-50;w+=100){
            //            //for(int h=1;h<drawY;h+=600){
            //                thisNum=1;
            //                ranNum=ranNumAll[thisNum];

            //                thisNum++;
            //                thisNum=thisNum%100+1;
            //        }
        }
        //update();

    }
}

float DrawWidget::getStretch(){
    return windowScale;
}
float DrawWidget::getWindowScale(){
    return windowScale;
}

//void DrawWidget::judgeIntersection(int num[5][100],int count/*五视图的哪部分*/,int *hasNum,int ox,int oy,int wid,int hei){
void DrawWidget::judgeIntersection(int num[5][1000],int count/*五视图的哪部分*/,int *hasNum,int ox,int oy,int wid,int hei){
    //qDebug("sssssssss");
    list<QPainterPath*>::iterator temp = allPath.begin();
    int t=1;
    *hasNum=0;//五视图的这部分所包含的斑点总数
    QPointF tempPoint;
    float x,y,j;
    int con;
    //("%d",allPath.size());
    for(;temp!=allPath.end();++temp){
        con=1;
        //qDebug("~~~%d %d %d %d",ox,oy,wid,hei);
        for(float i=ox;i<ox+wid;i+=wid/30){
            for(j=oy;j<oy+hei;j+=hei/30){
                //qDebug("~~~~~~~~~%f %f",i,j);

                //-------xiaotian    cad修改
                x=(i-spotOriginX[t])*cos(-rotation[t]/180*PI)/stretch[t]-(j-spotOriginY[t])*sin(-rotation[t]/180*PI)/stretch[t];
                y=(i-spotOriginX[t])*sin(-rotation[t]/180*PI)/stretch[t]+(j-spotOriginY[t])*cos(-rotation[t]/180*PI)/stretch[t];
                //                    x=(i-spotOriginX[t])-(j-spotOriginY[t]);
                //                    y=(i-spotOriginX[t])+(j-spotOriginY[t]);
                //qDebug("oooo:%f %f",spotOriginX[t],spotOriginY[t]);
                //qDebug("yuan:%f %f",i,j);
                //qDebug("bian:%f %f",x,y);
                tempPoint.setX(x);
                tempPoint.setY(y);
                if((*temp)->contains(tempPoint)){
                    num[count][(*hasNum)]=t;//保存斑点序号
                    //qDebug("&&&&%d %d",count,*hasNum);
                    (*hasNum)++;//此处为五视图所包含斑点个数,数组下表从0开始
                    con=0;
                    //qDebug("!!!%d",t);
                    break;
                }
            }
            if(!con)
                break;
        }
        t++;
    }
    //qDebug("%d",(*hasNum));
}
void DrawWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Delete)
        deleteSpot();
    else if(event->key()==Qt::Key_Control){
        //qDebug("press ctrl");
        ctrlFlag=1;
        //qDebug("xian shi 1111111111");
        //qDebug("xian shi :%d",flag);
        //        if(markFlag==4){
        //            //qDebug("xian shi 1111111111");
        //            if(!ctrlSize){
        //                addCtrlSpot();
        //            }
        //        }
    }

}

void DrawWidget::keyReleaseEvent(QKeyEvent *event){
    //qDebug("aaaaaaaaaaa");
    if(event->key()==Qt::Key_Control){
        //qDebug("aaaaaaaaaaa");
        ctrlFlag=0;
    }

}

void DrawWidget::mapping(){
    if(fabs(windowScale-1)<0.001){
        cWindow=new childWindow();
        cWindow->setWindowTitle(QObject::tr("模型视图"));
        cWindow->show();
        connect(cWindow,SIGNAL(ChildWindowEvent()),this,SLOT(ChildWindowEventSlot()));


        //int num[5][100],hasNum/*记录斑点个数*/;
        int num[5][1000],hasNum/*记录斑点个数*/;
        list<QPainterPath*>::iterator tempPath;
        float oX,oY;
        QPen pen(backGroundColor,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);


        //第一副图
        judgeIntersection(num,0,&hasNum,midWidth-drawX/2,midHeight-drawY/2-drawZ,drawX,drawZ);
        QPixmap pix1(drawX,drawZ);
        QPainter p1(&pix1);
        p1.setBrush(backGroundColor);

        p1.setPen(Qt::NoPen);
        //p1.setPen(Qt::pen);
        p1.drawRect(0,0,drawX,drawZ);

        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[0][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[0][i]]-(midHeight-drawY/2-drawZ);

            p1.translate(oX,oY);
            p1.scale(stretch[num[0][i]],stretch[num[0][i]]);
            p1.rotate(rotation[num[0][i]]);
            //qDebug("jiaodu: %f",rotation[num[0][i]]);
            //qDebug("!!!!!!!!!%f",stretch[num[0][i]]/windowScale);

            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[0][i];j++){
                tempPath++;
            }
            getSpotColor(num[0][i]);
            p1.setBrush(spotColor);
            p1.drawPath(**tempPath);
            p1.setBrush(Qt::NoBrush);

            p1.scale(1/stretch[num[0][i]],1/stretch[num[0][i]]);
            p1.rotate(-rotation[num[0][i]]);
            p1.translate(-oX,-oY);

        }
        p1.end();
        //pix1.save("image/1.png");


        //第二幅图
        judgeIntersection(num,1,&hasNum,midWidth-drawX/2-drawZ,midHeight-drawY/2,drawZ,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix2(drawZ,drawY);
        QPainter p2(&pix2);
        p2.setBrush(backGroundColor);

        //p2.setPen(pen);
        p2.setPen(Qt::NoPen);
        p2.drawRect(0,0,drawZ,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[1][0],num[1][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[1][i]]-(midWidth-drawX/2-drawZ);
            oY=spotOriginY[num[1][i]]-(midHeight-drawY/2);

            p2.translate(oX,oY);
            p2.scale(stretch[num[1][i]],stretch[num[1][i]]/windowScale);
            p2.rotate(rotation[num[1][i]]);



            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[1][i];j++){
                tempPath++;
            }
            getSpotColor(num[1][i]);
            p2.setBrush(spotColor);
            p2.drawPath(**tempPath);
            p2.setBrush(Qt::NoBrush);

            p2.scale(1/stretch[num[1][i]],1/stretch[num[1][i]]);
            p2.rotate(-rotation[num[1][i]]);
            p2.translate(-oX,-oY);

        }
        p2.end();
        //pix2.save("image/2.png");


        //第三幅图
        judgeIntersection(num,2,&hasNum,midWidth-drawX/2,midHeight-drawY/2,drawX,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix3(drawX,drawY);
        QPainter p3(&pix3);
        p3.setBrush(backGroundColor);

        //p3.setPen(pen);
        p3.setPen(Qt::NoPen);
        p3.drawRect(0,0,drawX,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[2][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[2][i]]-(midHeight-drawY/2);

            p3.translate(oX,oY);
            p3.scale(stretch[num[2][i]],stretch[num[2][i]]);
            p3.rotate(rotation[num[2][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[2][i];j++){
                tempPath++;
            }
            getSpotColor(num[2][i]);
            p3.setBrush(spotColor);
            p3.drawPath(**tempPath);
            p3.setBrush(Qt::NoBrush);

            p3.scale(1/stretch[num[2][i]],1/stretch[num[2][i]]);
            p3.rotate(-rotation[num[2][i]]);
            p3.translate(-oX,-oY);

        }
        p3.end();
        //pix3.save("image/3.png");





        //第四幅图
        judgeIntersection(num,3,&hasNum,midWidth+drawX/2,midHeight-drawY/2,drawZ,drawY);
        //qDebug("%d",hasNum);
        QPixmap pix4(drawZ,drawY);
        QPainter p4(&pix4);
        p4.setBrush(backGroundColor);

        //p4.setPen(pen);
        p4.setPen(Qt::NoPen);
        p4.drawRect(0,0,drawZ,drawY);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[3][i]]-(midWidth+drawX/2);
            oY=spotOriginY[num[3][i]]-(midHeight-drawY/2);

            p4.translate(oX,oY);
            p4.scale(stretch[num[3][i]],stretch[num[3][i]]);
            p4.rotate(rotation[num[3][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[3][i];j++){
                tempPath++;
            }
            getSpotColor(num[3][i]);
            p4.setBrush(spotColor);
            p4.drawPath(**tempPath);
            p4.setBrush(Qt::NoBrush);

            p4.scale(1/stretch[num[3][i]],1/stretch[num[3][i]]);
            p4.rotate(-rotation[num[3][i]]);
            p4.translate(-oX,-oY);

        }
        p4.end();
        //pix4.save("image/4.png");




        //第五幅图
        judgeIntersection(num,4,&hasNum,midWidth-drawX/2,midHeight+drawY/2,drawX,drawZ);
        //qDebug("%d",hasNum);
        QPixmap pix5(drawX,drawZ);
        QPainter p5(&pix5);
        p5.setBrush(backGroundColor);

        p5.setPen(pen);
        p5.drawRect(0,0,drawX,drawZ);

        //qDebug("   %d",hasNum);
        //qDebug("   %d  %d",num[2][0],num[2][1]);
        for(int i=0;i<hasNum;i++){

            oX=spotOriginX[num[4][i]]-(midWidth-drawX/2);
            oY=spotOriginY[num[4][i]]-(midHeight+drawY/2);

            p5.translate(oX,oY);
            p5.scale(stretch[num[4][i]],stretch[num[4][i]]);
            p5.rotate(rotation[num[4][i]]);


            //找到path
            tempPath=allPath.begin();
            for(int j=1;j<num[4][i];j++){
                tempPath++;
            }
            getSpotColor(num[4][i]);
            p5.setBrush(spotColor);
            p5.drawPath(**tempPath);
            p5.setBrush(Qt::NoBrush);

            p5.scale(1/stretch[num[4][i]],1/stretch[num[4][i]]);
            p5.rotate(-rotation[num[4][i]]);
            p5.translate(-oX,-oY);

        }
        p5.end();
        //pix5.save("image/5.png");
    }
    else{
        QMessageBox msgBox(this);
        //msgBox.setIconPixmap(QPixmap("icon/huabu.png"));

        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("当前缩放比例必须为1        "));
        msgBox.setMinimumSize(200,100);
        //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));
        msgBox.exec();
    }



}
void DrawWidget::mouseMoveEvent(QMouseEvent *event){

    cout<<"移动鼠标"<<endl;
    if(mousePressFlag){
        xEnd=event->x();
        yEnd=event->y();
        cout<<xEnd<<" "<<yEnd<<endl;
        areaSelected();
    }
    else{
        if(flag==1||flag==2){
            oPointMove(event);
        }

        if(flag==6){//移动斑点
            spotMove(event);
            eventStyle=3;
        }
    }


    update();

}

void DrawWidget::mousePressEvent(QMouseEvent *event){
    cout<<"按下鼠标"<<endl;
    if(event->button()==Qt::LeftButton){

        markFlag=0;
        flag=0;
        spotSelectedNum=0;

        if(oPoint.empty()&&oPointAll.empty()){//如果链表内没有点,责直接加入一个点
            //widthChange=0;
            //heightChange=0;
        }

        currentPoint=new(QPointF);
        currentPoint1=new(QPoint);
        currentPoint->setX(event->x());
        currentPoint->setY(event->y());
        currentPoint1->setX(event->x());
        currentPoint1->setY(event->y());
        if(drawFlag){
            //首先判断有没有选中别的斑点或者原点或者别的斑点的控制点
            if(oPointSelected()||spotSelected()){
                if(!ctrlFlag){
                    ctrlSize=0;
                    spotSelectedCtrl.clear();
                }
                update();
                return;
            }
            else
                //若不是选中状态，则继续画点
                mousePressNotDrawOk();
            if(!ctrlFlag){
                ctrlSize=0;
                spotSelectedCtrl.clear();
            }
        }
        else{
            //若非画笔选中状态
            if(oPointSelected()||spotSelected()){
                if(!ctrlFlag){
                    ctrlSize=0;
                    spotSelectedCtrl.clear();
                }
            }
            else{
                mousePressFlag=1;
                xBegin=event->x();
                yBegin=event->y();
                xEnd=xBegin,yEnd=yBegin;
                if(!ctrlFlag){
                    ctrlSize=0;
                    spotSelectedCtrl.clear();
                }
            }
        }
        update();
    }
    else{
        rightX=event->x();
        rightY=event->y();
    }
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *){
    cout<<"放开鼠标"<<endl;
    if(spotSelectedNum&&flag==6){
        //进行图形中心点调整
        spotOriginX[spotSelectedNum] = spotOriginX[spotSelectedNum] - preoffset1.x() + predivX;
        spotOriginY[spotSelectedNum] = spotOriginY[spotSelectedNum] - preoffset1.y() + predivY;

        //调整画的顺序

        //进行颜色矩阵调整
        //斑点移动前所在的矩阵的行和列
        int preRow = removeCurrentRow[spotSelectedNum-1];
        int preCol = removeCurrentCol[spotSelectedNum-1];
        //斑点移动后所在的矩阵的行和列
        int lastRow = preRow + predivY/rectSize;
        int lastCol = preCol + predivX/rectSize;

        //斑点的矩阵信息
        string mid = graphName[spotSelectedNum-1];

        //更新颜色矩阵
        //取出颜色对应的数字值
        int colorValue = 0;

        getSpotColor(spotSelectedNum);
        //找出斑点颜色对应的allcolor的index值，将index值+1即为颜色编码值
        for(int i=0;i<1000;i++){
            if(allColor.myColor[i].red() == spotColor.red() &&allColor.myColor[i].green() == spotColor.green()
                    &&allColor.myColor[i].blue() == spotColor.blue()){
                colorValue = allColor.index[i];
                break;
            }
        }


        if(colorValue == 29){
            colorValue = 0;
        }else{
            colorValue +=  1;
        }
        //找出背景色对应的颜色编码值


        int rowNum = removeRow[spotSelectedNum-1];
        int colNum = removeCol[spotSelectedNum-1];

        list<QString> jzpoints;
        float spotWidth;
        float spotHeigh;
        jzpoints = saveGet.readOrig(&spotWidth,&spotHeigh,mid);
        int edge[rowNum][colNum];
        for(int i=0;i<rowNum;i++){
            for(int j=0;j<colNum;j++){
                edge[i][j] = 0;
            }
        }


        list<QString>::iterator jzindex = jzpoints.begin();

        int poi=0;
        for(;jzindex!=jzpoints.end();++jzindex){
            int poj=0;
            QString str = *jzindex;
            QStringList strs = str.split(",");
            QList<QString>::Iterator it = strs.begin();
            for(;it!=strs.end();++it){
                QString valuestr = *it;

                int value = 0;
                if(valuestr == "1")
                    value = 1;
                edge[poi][poj] = value;
                ++poj;
            }
            ++poi;
        }




        //更新移动前的颜色矩阵
        int rowbegin  = preRow;
        int colbegin = preCol;
        int rowend = rowbegin + rowNum;
        int colend = colbegin + colNum;
        int m=0;
        for(int i=rowbegin;i<rowend;i++){
            int n = 0;
            for(int j=colbegin;j<colend;j++){
                if(colorJ[i][j] == colorValue){
                    colorJ[i][j] = 0;//--------颜色编码值
                }
                n++;
            }
            m++;
        }

        //记录颜色矩阵
        rowbegin = lastRow;
        colbegin = lastCol;
        rowend = rowbegin + rowNum;
        colend = colbegin + colNum;
        //更新移动后的颜色矩阵
        m=0;
        for(int i=rowbegin;i<rowend;i++){
            int n = 0;
            for(int j=colbegin;j<colend;j++){
                if(edge[m][n] == 1 && colorJ[i][j] == 0){
                    colorJ[i][j] = colorValue;//--------颜色编码值
                }
                n++;
            }
            m++;
        }



        //多次移动，更新斑点的矩阵行和列
        removeCurrentRow[spotSelectedNum-1] = lastRow;
        removeCurrentCol[spotSelectedNum-1] = lastCol;

        //输出新的颜色矩阵
        for(int i=0;i<50;i++){
            for(int j=0;j<60;j++){
                cout<<colorJ[i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<"   jieshu  le  "<<endl;
        saveStation();
    }
    if(flag==1||flag==2){
        saveStation();
    }
    flag=0;
    mousePressFlag=0;
    update();
}

void DrawWidget::mousePressNotDrawOk(){
    QPointF *tempPoint;
    list<QPointF*>::iterator F;
    if(oPoint.empty()&&oPointAll.empty()){//如果链表内没有点,责直接加入一个点
        //widthChange=0;
        //heightChange=0;
        tempPoint=new QPointF;
        tempPoint->setX(currentPoint->x());
        tempPoint->setY(currentPoint->y());
        //qDebug("~~~~%f  %f",currentPoint->x(),currentPoint->y());
        oPoint.push_back(tempPoint);
        pointNum++;
        return;
    }
    else{
        //如果第一个点和最后一个点相同,并且总点个数大于2,则绘制斑点
        if(!oPoint.empty()){
            F=oPoint.begin();
            cPath=new(QPainterPath);
            cPath->addEllipse((**F).x()-keyPointSize/2,(**F).y()-keyPointSize/2,keyPointSize,keyPointSize);
            if(cPath->contains(*currentPoint)&&oPoint.size()>2)
            {
                spotNum[++drawOk]=pointNum;//把斑点含点个数保存起来
                //qDebug("&&&&&&%d   %d",drawOk,spotNum[drawOk-1]);
                pointNum=0;//清空未画完斑点计数器
                addSpotOrigin(drawOk);
                stretch[drawOk]=1;
                rotation[drawOk]=0;
                addSpotPoint();//把刚绘制完斑点的点保存起来
                caculateOneCurve();//计算最后一个斑点的数据，包括thePoint和cPath
                eventStyle=1;
                //qDebug("sdfsdf");
                emit ChildWindowEvent();
                delete cPath;
                saveStation();
                return;
            }
            delete cPath;
        }

        if(flag==0&&drawFlag==1){
            tempPoint=new QPointF;
            tempPoint->setX(currentPoint->x());
            tempPoint->setY(currentPoint->y());
            //qDebug("~~~~%f  %f",currentPoint->x(),currentPoint->y());
            oPoint.push_back(tempPoint);//斑点没有绘制完成，加点
            pointNum++;
        }
    }
}

void DrawWidget::mousePressDrawOk(){

}

int DrawWidget::oPointMove(QMouseEvent *event){
    QPointF offset;

    float x,y,x1,y1;
    x=(event->x()-spotOriginX[spotSelectedNum])*cos(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum]-(event->y()-spotOriginY[spotSelectedNum])*sin(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum];
    y=(event->x()-spotOriginX[spotSelectedNum])*sin(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum]+(event->y()-spotOriginY[spotSelectedNum])*cos(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum];
    x1=selectedPoint->x()-spotOriginX[spotSelectedNum];
    y1=selectedPoint->y()-spotOriginY[spotSelectedNum];

    offset.setX(x-x1);
    offset.setY(y-y1);


    QPointF offset1;
    offset1.setX(event->x()-selectedPoint->x());
    offset1.setY(event->y()-selectedPoint->y());


    list<QPointF*>::iterator oP;
    oPointMoveFlag=0;
    int oPointMoveFlagH=0;

    oP=oPoint.begin();
    for(;oP!=oPoint.end();oP++){
        if(fabs((**oP).x()-selectedPoint->x())<0.001&&fabs((**oP).y()-selectedPoint->y())<0.001){
            (**oP).setX((**oP).x()+offset1.x());
            (**oP).setY((**oP).y()+offset1.y());
            selectedPoint->setX(event->x());
            selectedPoint->setY(event->y());
            //qDebug("move move");
            return 1;
        }
    }


    int ok=0;
    oP = oPointAll.begin();
    list<QPointF*>::iterator oP1 = handlePointAll.begin();
    list<QPointF*>::iterator oP2;
    //int countccc=1;
    for(int i=1;i<drawOk+1;i++){
        for(int j=1;j<spotNum[i]+1;j++){
            if(fabs((**oP).x()+spotOriginX[spotSelectedNum]-selectedPoint->x())<0.001&&fabs((**oP).y()+spotOriginY[spotSelectedNum]-selectedPoint->y())<0.001&&oPointJudge==i){
                oPointMoveFlag=i;
                (**oP).setX((**oP).x()+offset.x());
                (**oP).setY((**oP).y()+offset.y());
                selectedPoint->setX((**oP).x()+spotOriginX[spotSelectedNum]);
                selectedPoint->setY((**oP).y()+spotOriginY[spotSelectedNum]);
                oPointMoveFlagH=j;
                ok=1;
                //qDebug("%d",countccc);
                //countccc++;
                break;
            }
            ++oP;
        }
        if(ok)
            break;
    }


    oP = oPointAll.begin();
    oPointTemp.clear();
    for(int i=1;i<oPointMoveFlag;i++){
        for(int j=1;j<spotNum[i]+1;j++){
            oP++;
        }
    }
    for(int j=1;j<spotNum[oPointMoveFlag]+1;j++){
        oPointTemp.push_back(*oP);
        ++oP;
    }


    //把控制点放到计算list中
    oP1 = handlePointAll.begin();
    //thePoint.clear();
    for(int i=1;i<oPointMoveFlag;i++){
        for(int j=1;j<2*spotNum[i]+1;j++){
            oP1++;
        }
    }
    //重新计算某个斑点控制点
    midPoint.clear();
    midM.clear();
    tranCoo.clear();
    thePoint.clear();
    use.getMid(oPointTemp,midPoint,midM);
    use.getTraCoo(oPointTemp,midM,tranCoo);
    use.getThePoint(midPoint,tranCoo,thePoint);
    oP2=thePoint.begin();
    //qDebug("aaaaaaaaaa:%d",oPointMoveFlag);
    for(int j=1;j<2*spotNum[oPointMoveFlag]+1;j++){
        (**oP1).setX((**oP2).x());
        (**oP1).setY((**oP2).y());
        //qDebug("QQQQQQ: %f %f",(**oP2).x(),(**oP2).y());
        //qDebug("*********%d",handlePointAll.size());
        ++oP1;
        ++oP2;
    }

    //加入path
    path=new(QPainterPath);
    list<QPointF*>::iterator midP =thePoint.begin();
    oP = oPointTemp.begin();
    list<QPointF*>::iterator midPNext;
    list<QPointF*>::iterator oPNext;
    path->moveTo((**oP).x(),(**oP).y());
    ++oP;


    midPNext=++midP;
    midP--;
    oPNext=++oP;
    oP--;

    for(;oP!=oPointTemp.end();++oPNext){
        path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());
        midP++;
        midP++;
        midPNext=++midP;
        midP--;
        oP++;
    }
    oP=oPointTemp.begin();
    path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP).x(),(**oP).y());

    list<QPainterPath*>::iterator tempPath;
    tempPath=allPath.begin();
    QPainterPath *tempPathDelete;
    for(int j=1;j<oPointMoveFlag;j++)
        tempPath++;
    tempPathDelete=*tempPath;
    allPath.erase(tempPath);
    tempPath=allPath.begin();
    for(int j=1;j<oPointMoveFlag;j++)
        tempPath++;
    allPath.insert(tempPath,path);
    delete tempPathDelete;

    /////////////////////////////////清理内存
    list<QPointF*>::iterator tempDelete;
    QPointF *tempDeletePoint;
    tempDelete=midPoint.begin();
    for(;tempDelete!=midPoint.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }

    midPoint.clear();
    tempDelete=midM.begin();
    for(;tempDelete!=midM.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    midM.clear();

    tempDelete=tranCoo.begin();
    for(;tempDelete!=tranCoo.end();tempDelete++){
        tempDeletePoint=*tempDelete;
        delete tempDeletePoint;
    }
    tranCoo.clear();
    return 0;
}

int DrawWidget::oPointSelected(){
    //qDebug("sdfsdfsdf");
    list<QPointF*>::iterator temp=oPointAll.begin();
    list<QPointF*>::iterator temp1;
    //QPointF tempPoint;

    if(oPoint.size()>0){
        temp1=oPoint.begin();
        cPath=new(QPainterPath);
        cPath->addEllipse((**temp1).x()-keyPointSize/2,(**temp1).y()-keyPointSize/2,keyPointSize,keyPointSize);
        if(cPath->contains(*currentPoint))//如果if为真,则点重合
        {
            delete cPath;
            return 0;
        }
        delete cPath;

        for(;temp1!=oPoint.end();temp1++){
            cPath=new(QPainterPath);
            cPath->addEllipse((**temp1).x()-keyPointSize/2,(**temp1).y()-keyPointSize/2,keyPointSize,keyPointSize);
            if(cPath->contains(*currentPoint))//如果if为真,则点重合
            {
                flag=2;
                markFlag=1;
                selectedPoint=new(QPointF);
                selectedPoint->setX((**temp1).x());
                selectedPoint->setY((**temp1).y());
                handleO.setX((**temp1).x());
                handleO.setY((**temp1).y());
                delete cPath;
                //addOPointEdit();
                return 1;
            }
            delete cPath;
        }
    }



    if(drawOk){
        //oPAll=oPointAll.begin();
        int t=1;
        int n=1;
        for(;t<drawOk+1;t++){
            //p.translate(spotOriginX[t],spotOriginY[t]);
            n=1;
            for(;n<spotNum[t]+1;n++){
                //tempPoint.setX(currentPoint->x()/2);
                //tempPoint.setY(currentPoint->x()/2);
                cPath=new(QPainterPath);
                float x,y;
                //qDebug("   %f",stretch[t]);
                //..x=(**temp).x()*cos(rotation[t]/180*PI)*stretch[t]-(**temp).y()*sin(rotation[t]/180*PI)*stretch[t]+spotOriginX[t]-keyPointSize/2*stretch[t];
                //..y=(**temp).x()*sin(rotation[t]/180*PI)*stretch[t]+(**temp).y()*cos(rotation[t]/180*PI)*stretch[t]+spotOriginY[t]-keyPointSize/2*stretch[t];
                x=(currentPoint->x()-spotOriginX[t])*cos(-rotation[t]/180*PI)/stretch[t]-(currentPoint->y()-spotOriginY[t])*sin(-rotation[t]/180*PI)/stretch[t];
                y=(currentPoint->x()-spotOriginX[t])*sin(-rotation[t]/180*PI)/stretch[t]+(currentPoint->y()-spotOriginY[t])*cos(-rotation[t]/180*PI)/stretch[t];
                QPointF tempPoint1;
                tempPoint1.setX(x);
                tempPoint1.setY(y);
                //qDebug("%f  %f",sin(PI/2),cos(PI/2));
                //qDebug("%f  %f",(*currentPoint).x(),(*currentPoint).y());
                //qDebug("%f  %f",x,y);
                //cPath->addEllipse(((**temp).x()-keyPointSize/2)/2+spotOriginX[t],((**temp).y()-keyPointSize/2)/2+spotOriginY[t],keyPointSize/2,keyPointSize/2);
                cPath->addEllipse((**temp).x()-keyPointSize/2,(**temp).y()-keyPointSize/2,keyPointSize,keyPointSize);

                //qDebug("bian~~~~~~~:  %f %f",x,y);
                //qDebug("ooo~~~~~~~~:  %f %f",(**temp).x(),(**temp).y());
                //qDebug("  ");
                if(cPath->contains(tempPoint1))//如果if为真,则点重合
                {
                    flag=2;
                    markFlag=1;
                    selectedPoint=new(QPointF);
                    selectedPoint->setX((**temp).x()+spotOriginX[t]);
                    selectedPoint->setY((**temp).y()+spotOriginY[t]);
                    oPointJudge=t;
                    //qDebug("++++%f   %f",(**temp).x(),(**temp).y());
                    //qDebug("++++%f   %f",spotOriginX[t],spotOriginY[t]);
                    //selectedPoint->setX((**temp).x()/2+spotOriginX[t]);
                    //selectedPoint->setY((**temp).y()/2+spotOriginY[t]);
                    this->update();
                    spotSelectedNum=t;
                    handleO.setX((**temp).x()+spotOriginX[t]);
                    handleO.setY((**temp).y()+spotOriginY[t]);
                    delete cPath;
                    //qDebug("sssssssssssssssssss");
                    qDebug("xuan zhong :%d",spotSelectedNum);

                    //addOPointEdit();
                    return 1;
                }
                delete cPath;
                //1("%f  %f",(**temp).x(),(**temp).y());
                temp++;
            }
            //qDebug("%f  %f",sin(PI/2),cos(PI/2));
            //qDebug("%f  %f",(*currentPoint).x(),(*currentPoint).y());
            //qDebug("%f  %f",x,y);

            //p.translate(-spotOriginX[t],-spotOriginY[t]);
        }


        //    for(;oPAll!=oPointAll.end();++oPAll){
        //       if(markFlag==1&&(**oPAll).x()==selectedPoint->x()&&(**oPAll).y()==selectedPoint->y()){
        //                      p.setBrush(QBrush(QColor(255,0,255),Qt::Dense4Pattern));
        //                      p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
        //                      p.setBrush(Qt::NoBrush);
        //                  }
        //       else{
        //                      p.drawEllipse((**oPAll).x()-keyPointSize/2,(**oPAll).y()-keyPointSize/2,keyPointSize,keyPointSize);
        //                  }
        //        }
    }




    //    for(;temp!=oPointAll.end();temp++){
    //       cPath=new(QPainterPath);
    //       cPath->addEllipse((**temp).x()-keyPointSize/2,(**temp).y()-keyPointSize/2,keyPointSize,keyPointSize);
    //       if(cPath->contains(*currentPoint))//如果if为真,则点重合
    //           {
    //               flag=2;
    //               markFlag=1;
    //               selectedPoint=new(QPointF);
    //               selectedPoint->setX((**temp).x());
    //               selectedPoint->setY((**temp).y());
    //               handleO.setX((**temp).x());
    //               handleO.setY((**temp).y());
    //               delete cPath;
    //               //addOPointEdit();
    //               return 1;
    //           }
    //       delete cPath;
    //      }

    return 0;
}

//----------------xiaotian    画外围内包的点
void DrawWidget::drawNbSpot(QPainter &p){


}



void DrawWidget::paintEvent(QPaintEvent *){

    QPainter p(this);
    spotColor.setRgb(255,255,255);
    p.setRenderHint(QPainter::Antialiasing,true);//抗锯齿渲染

    drawCanvas(p);


    if(showDigital){
        //---------------------------xiaotian     变为自己编写的方法
        //getCanvasPointSTest(100,100);

        //getDigitalCanvas(p);
        drawDigitalSpot(p);

    }else{

        //drawDigital(p);
        //else{
        if(ifCanDraw){
            p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
            if(mousePressFlag){
                p.drawRect(xBegin,yBegin,xEnd-xBegin,yEnd-yBegin);

            }

            if(showOPoint)
                drawOPoint(p);
            if(oPoint.size()>1){//绘制过程直线
                drawProcessLine(p);
            }

            if(drawOk){
                drawSpot(p);
                if(showOPoint){
                    drawOPoint(p);
                    drawOrign(p);//绘制斑点中间那个点
                }
                if(radiusFlag){
                    drawMark(p);
                }
            }


            ////drawBlank(p);

            drawEdgeLine(p);
            //网格线+标尺
            drawScaleLine(p);
            drawCLine(p);



            ////qDebug("xian zai z shi:%f,%f",drawX,drawY);
        }
    }
    //}

}

void DrawWidget::resizeEvent(QResizeEvent *event){
}

int DrawWidget::return_flag(){
    return flag;
}
void DrawWidget::QScrollAreaResize(){
    //qDebug("sdfsdffffffff");
}
void DrawWidget::readCanvasF(QString fileName){
    clear();
    float tempWidth=0,tempHeight=0;
    spot *tempSave1=new spot;
    saveGet.readCanvas(tempSave1,fileName);
    drawOk=tempSave1->getDrawOk();
    tempSave1->getWidHei(tempWidth,tempHeight);
    tempSave1->getSpotNum(spotNum);
    tempSave1->getSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    tempSave1->getCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    tempSave1->getStretch(stretch);
    tempSave1->getRotation(rotation);
    tempSave1->getOpointAll(oPointAll);
    tempSave1->getHandlePointAll(handlePointAll);
    tempSave1->getAllColorIndex(allColor.index,backGroundColorIndex);
    tempSave1->getCanvas(drawX,drawY,drawZ);
    tempSave1->getWindowScale(windowScale);

    midWidth=tempWidth/2;
    midHeight=tempHeight/2;
    //通过index初始化颜色
    for(int i=1;i<drawOk+1;i++){
        allColor.myColor[i]=iconColor[allColor.index[i]+1];
        allColor.myColor[i]=iconColor[allColor.index[i]+1];
        //qDebug("QQQQQQQQ:%d",allColor.index[i]+1);
    }
    backGroundColor=iconColor[backGroundColorIndex+1];
    if(drawZ>0){
        drawCanvasFlag=2;
        AutoCADFlag=1;
    }
    else{
        drawCanvasFlag=1;
    }

    this->setGeometry(0,0,tempWidth,tempHeight);
    caculateCanvasPath();
    this->update();
    emit getAllColor_s();
    saveStation();
}

void DrawWidget::rightCpy(){
    if(spotSelectedNum){
        cpyNum=spotSelectedNum;
    }
}
void DrawWidget::setNewColor(QColor *tempColor,int colorNum){
    for(int i=1;i<colorNum+1;i++){
        iconColor[30+i]=tempColor[30+i];
    }
    addColorNum=colorNum;
}


void DrawWidget::showSpotEdge(int temp){
    ifShowSpotEdge=temp;
    this->update();
}

void DrawWidget::rightCut(){
}

void DrawWidget::rightPaste(){
    if(cpyNum){
        list<QPointF*>::iterator oP1= oPointAll.begin();
        list<QPointF*>::iterator handleP= handlePointAll.begin();

        list<QPointF*>oPointTempAddSpecial;
        list<QPointF*>thePointTempAdd;

        //找到移动斑点的原点所在区间
        for(int i=1;i<cpyNum;i++){//spotSelectedNum
            for(int j=1;j<spotNum[i]+1;j++){
                ++oP1;
            }
        }

        QPointF *tempPoint;
        //将移动斑点的原点压栈到计算链表
        for(int j=1;j<spotNum[cpyNum]+1;j++){
            tempPoint=new(QPointF);
            tempPoint->setX((**oP1).x());
            tempPoint->setY((**oP1).y());

            oPointTempAddSpecial.push_back(tempPoint);
            oPointAll.push_back(tempPoint);
            ++oP1;
        }


        //找到移动斑点的控制点所在区间
        for(int i=1;i<cpyNum;i++){
            for(int j=1;j<2*spotNum[i]+1;j++){
                ++handleP;
            }
        }

        //将移动斑点的控制点压栈到计算链表
        for(int j=1;j<2*spotNum[cpyNum]+1;j++){
            tempPoint=new(QPointF);
            tempPoint->setX((**handleP).x());
            tempPoint->setY((**handleP).y());


            thePointTempAdd.push_back(tempPoint);
            handlePointAll.push_back(tempPoint);
            ++handleP;
        }



        //计算移动斑点的路径
        path=new(QPainterPath);
        oP1 = oPointTempAddSpecial.begin();
        list<QPointF*>::iterator midP =thePointTempAdd.begin();

        list<QPointF*>::iterator midPNext;
        list<QPointF*>::iterator oPNext;

        path->moveTo((**oP1).x(),(**oP1).y());
        ++oP1;

        midPNext=++midP;
        midP--;
        oPNext=++oP1;
        oP1--;

        if(saveGet.digitalFlag == 0){
            for(;oP1!=oPointTempAddSpecial.end();++oPNext){
                path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
                midP++;
                midP++;
                midPNext=++midP;
                midP--;
                oP1++;
            }
            oP1=oPointTempAddSpecial.begin();
            path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
            allPath.push_back(path);
        }else{
            //数码迷彩的斑点画法   -----------xiaotian    数码迷彩的斑点移动和复制

            for(;oP1!=oPointTempAddSpecial.end();++oPNext){
                //path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
                path->lineTo((**oP1).x(),(**oP1).y());
                midP++;
                midP++;
                midPNext=++midP;
                midP--;
                oP1++;
            }
            oP1=oPointTempAddSpecial.begin();
            //path->cubicTo((**midP).x(),(**midP).y(),(**midPNext).x(),(**midPNext).y(),(**oP1).x(),(**oP1).y());
            path->lineTo((**oP1).x(),(**oP1).y());
            allPath.push_back(path);
        }


        spotNum[++drawOk]=spotNum[cpyNum];//把斑点含点个数保存起来
        //qDebug("&&&&&&%d   %d",drawOk,spotNum[drawOk-1]);
        stretch[drawOk]=stretch[cpyNum];
        rotation[drawOk]=rotation[cpyNum];
        eventStyle=1;
        //qDebug("sdfsdf");
        emit ChildWindowEvent();


        spotOriginX[drawOk]=rightX;
        spotOriginY[drawOk]=rightY;

        spotOriginOX[drawOk]=spotOriginX[drawOk]-midWidth;
        spotOriginOY[drawOk]=spotOriginY[drawOk]-midHeight;

        spotOriginPOX[drawOk]=spotOriginOX[drawOk];
        spotOriginPOY[drawOk]=spotOriginOY[drawOk];

        update();
        saveStation();
    }
}

void DrawWidget::rightDelete(){
}

//-----------xiaotian
void DrawWidget::setAutoSingleColor(spotColorAll tempAllColor,int tempIndex,int count){
    allColor.index[count] = tempAllColor.index[count];
    allColor.myColor[count] = iconColor[tempAllColor.index[count] + 1];

    update();
    saveStation();
}



void DrawWidget::setAutoColor(spotColorAll tempAllColor,int tempIndex){
    //qDebug("sssssssssssssssssssssssssssssssssssssssssss%d",drawOk);
    for(int i=1;i<drawOk+1;i++){
        allColor.index[i]=tempAllColor.index[i];
        //qDebug("ccccccccccccccccccccccccccccccc%d",tempAllColor.index[i]);
        //
        allColor.myColor[i]=iconColor[tempAllColor.index[i]+1];
    }
    backGroundColorIndex=tempIndex;
    backGroundColor=iconColor[backGroundColorIndex+1];
    update();
    saveStation();
}


void DrawWidget::saveCanvasF(QString fileName){
    tempSave=new spot;
    tempSave->setDrawOk(drawOk);
    tempSave->setSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    tempSave->setCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    tempSave->setWidHei(width(),height());
    tempSave->setSpotNum(spotNum);
    tempSave->setStretch(stretch);
    tempSave->setRotation(rotation);
    tempSave->setOpointAll(oPointAll);
    tempSave->setHandlePointAll(handlePointAll);
    tempSave->setAllColorIndex(allColor.index,backGroundColorIndex);
    //tempSave->setAllPath(allPath);
    //tempSave->setAllColor(allColor);
    tempSave->setCanvas(drawX,drawY,drawZ);
    tempSave->setWindowScale(windowScale);
    saveGet.saveCanvas(tempSave,fileName);
}

int DrawWidget::saveSpotPoint(){
    if(AutoCADFlag){
        if(fabs(windowScale-1)<0.001){
            getAutoCAD();
            return 1;

        }
        else{
            QMessageBox msgBox(this);
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("当前缩放比例必须为1        "));
            msgBox.setMinimumSize(200,100);
            msgBox.exec();
            return 0;
        }

    }
    else{
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("只有在五面画布下能生成图纸！        "));
        msgBox.setMinimumSize(200,100);
        msgBox.exec();
        return 0;
    }
}
void DrawWidget::setCanvasXY(int x,int y,int tempFlag){
    AutoCADFlag=0;
    drawX=x;
    drawY=y;
    drawZ=0;

    canvasX=drawX;
    canvasY=drawY;

    if(canvasX>showArea->viewport()->width()&&canvasY<showArea->viewport()->height()){
        this->setGeometry(0,0,canvasX,showArea->viewport()->height());
    }
    if(canvasX<showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
        this->setGeometry(0,0,showArea->viewport()->width(),canvasY);
    }
    if(canvasX>showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
        this->setGeometry(0,0,canvasX,canvasY);
        //qDebug("aaaaaaaaa");
    }

    drawCanvasFlag=tempFlag;
}
void DrawWidget::setCanvasXYZ(int x,int y,int z,int tempFlag){
    //    canvasX=x;
    //    canvasY=y;
    //    canvasZ=z;
    AutoCADFlag=1;
    drawX=x;
    drawY=y;
    drawZ=z;

    canvasX=2*drawZ+drawX;
    canvasY=2*drawZ+drawY;
    //qDebug("fu zhi shi:%f",canvasY);

    if(canvasX>showArea->viewport()->width()&&canvasY<showArea->viewport()->height()){
        this->setGeometry(0,0,canvasX,showArea->viewport()->height());
    }
    if(canvasX<showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
        this->setGeometry(0,0,showArea->viewport()->width(),canvasY);
    }
    if(canvasX>showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
        this->setGeometry(0,0,canvasX,canvasY);
        //qDebug("@@@@@@@@@@%f  %f",canvasX,canvasY);
    }


    drawCanvasFlag=tempFlag;
}
void DrawWidget::setCenter(float x, float y){
    float tempCanvasX,tempCanvasY;
    tempCanvasX=canvasX*windowScale;
    tempCanvasY=canvasY*windowScale;
    //float tempWidth,tempHeight;
    //tempHeight=this->height();
    if(2*x<tempCanvasX&&2*y>tempCanvasY){
        this->setGeometry(0,0,tempCanvasX,2*y);
    }
    else if(2*x>tempCanvasX&&2*y<tempCanvasY){
        this->setGeometry(0,0,2*x,tempCanvasY);
        //qDebug("%d %d",showArea->viewport()->width(),width());
    }
    else if(2*x<tempCanvasX&&2*y<tempCanvasY){
        this->setGeometry(0,0,tempCanvasX,tempCanvasY);
    }
    else{
        this->setGeometry(0,0,2*x,2*y);
    }

    //qDebug("pre:%f %f",preMidWidth,preMidHeight);

    midWidth=width()/2;
    midHeight=height()/2;
    //qDebug("now:%f %f",midWidth,midHeight);

    float tempX;
    float tempY;
    tempX=midWidth-preMidWidth;
    tempY=midHeight-preMidHeight;
    //qDebug("cha: %f",tempX);


    //midWidth=x;
    //midHeight=y;
    for(int i=1;i<drawOk+1;i++){
        spotOriginX[i]=spotOriginX[i]+tempX;
        spotOriginY[i]=spotOriginY[i]+tempY;
        //spotOriginXI[i]=spotOriginX[i]+tempX;
        //spotOriginYI[i]=spotOriginY[i]+tempY;
    }
    preMidWidth=midWidth;
    preMidHeight=midHeight;
    this->update();
}

void DrawWidget::setColor(QColor tempColor,int tempIndex,spotChangeSpot *exchangeS){
    saveStation();
    if(ctrlSize>0){
        list<int>::iterator oP=spotSelectedCtrl.begin();
        for(int i=1;i<ctrlSize+1;i++,oP++){
            allColor.myColor[*oP]=tempColor;
            allColor.index[*oP]=tempIndex;
        }
    }
    else{
        allColor.myColor[spotSelectedNum]=tempColor;
        allColor.index[spotSelectedNum]=tempIndex;
    }

    handlePointColor=exchangeS->handlePointColor;
    handlePointSize=exchangeS->handlePointSize;
    hPointLineWidth=exchangeS->hPointLineWidth;
    keyPointColor=exchangeS->keyPointColor;
    keyPointSize=exchangeS->keyPointSize;

    markNum=exchangeS->markNum;
    minResolution=exchangeS->minResolution;
    spotLineColor=exchangeS->spotLineColor;
    spotLineWidth=exchangeS->spotLineWidth;
    this->update();
}
void DrawWidget::setBackGroundColor(QColor tempColor,int index){
    saveStation();
    backGroundColor=tempColor;
    backGroundColorIndex=index;
    this->update();
}

void DrawWidget::setBackGroundSize(int x, int y, int z){
    if(!z){

        AutoCADFlag=0;
        drawX=x;
        drawY=y;
        drawZ=0;

        canvasX=drawX;
        canvasY=drawY;

        if(canvasX>showArea->viewport()->width()&&canvasY<showArea->viewport()->height()){
            this->setGeometry(0,0,canvasX,showArea->viewport()->height());
        }
        if(canvasX<showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
            this->setGeometry(0,0,showArea->viewport()->width(),canvasY);
        }
        if(canvasX>showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
            this->setGeometry(0,0,canvasX,canvasY);
            //qDebug("aaaaaaaaa");
        }

        drawCanvasFlag=1;
        saveStation();
    }
    else{

        AutoCADFlag=1;
        drawX=x;
        drawY=y;
        drawZ=z;

        canvasX=2*drawZ+drawX;
        canvasY=2*drawZ+drawY;
        //qDebug("fu zhi shi:%f",canvasY);


        if(canvasX>showArea->viewport()->width()&&canvasY<showArea->viewport()->height()){
            this->setGeometry(0,0,canvasX,showArea->viewport()->height());
        }
        if(canvasX<showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
            this->setGeometry(0,0,showArea->viewport()->width(),canvasY);
        }
        if(canvasX>showArea->viewport()->width()&&canvasY>showArea->viewport()->height()){
            this->setGeometry(0,0,canvasX,canvasY);
            //qDebug("@@@@@@@@@@%f  %f",canvasX,canvasY);
        }
        drawCanvasFlag=2;
        saveStation();
    }
    this->update();
}

void DrawWidget::setCanDraw(){
    ifCanDraw=1;
}

void DrawWidget::setCanNDraw(){
    ifCanDraw=0;
}

void DrawWidget::setOPointFlag(int flag){
    showOPoint=flag;
    //showDigital = !flag;
    //qDebug("~~~~~~~~~~%d",showOPoint);
    this->update();
}

void DrawWidget::setDrawFlag(int flag){
    drawFlag=flag;
    oPoint.clear();
    pointNum=0;
    this->update();
    //qDebug("%d",drawFlag);
}

void DrawWidget::setRadiusFlag(int flag){
    radiusFlag=flag;
}

void DrawWidget::setZeroPoint(int flag){
    //widthChange+=0.41421356*canvasX*flag/2/1.4142135623;
    //heightChange+=0.41421356*canvasY*flag/2/1.4142135623;
    //qDebug("widthChange:  %f  heightChange:  %f",widthChange,heightChange);
}

void DrawWidget::spotMove(QMouseEvent *event){
    list<QPointF*>::iterator oP = oPointAll.begin();
    list<QPointF*>::iterator midP =handlePointAll.begin();
    //QPointF offset;
    QPointF offset1;

    //    float lupointX =midWidth-(drawX/2+drawZ)*windowScale;
    //    float lupointY =midHeight-(drawY/2+drawZ)*windowScale;
    //    offset.setX(event->x()-selectedPoint->x());
    //    offset.setY(event->y()-selectedPoint->y());

    int divX = event->x()-selectedPoint->x();
    int divY = event->y()-selectedPoint->y();
    int rectsize = rectSize;
    if(divX<0 && divX > -rectsize){
        divX = -rectsize;
    }
    if(divY<0 && divY > -rectsize){
        divY = -rectsize;
    }
    if(divX < rectsize && divX>0){
        divX = rectsize;
    }
    if(divY<rectsize && divY>0){
        divY = rectsize;
    }

    divX = divX/rectsize;
    divX = divX*rectsize;
    divY = divY/rectsize;
    divY = divY*rectsize;

    offset1.setX(event->x()-selectedPoint->x());
    offset1.setY(event->y()-selectedPoint->y());

    preoffset1.setX(offset1.x());
    preoffset1.setY(offset1.y());
    predivX = divX;
    predivY = divY;
    //-------xiaotian     斑点移动更改坐标，加入除以边长.
    //    offset1.setX(offset1.x()/rectSize);
    //    offset1.setY(offset1.y()/rectSize);
    if(spotOperation==1){
        //        spotOriginX[spotSelectedNum]+=offset.x();
        //        spotOriginY[spotSelectedNum]+=offset.y();

        spotOriginX[spotSelectedNum]+=offset1.x();
        spotOriginY[spotSelectedNum]+=offset1.y();

        //        spotOriginX[spotSelectedNum] = spotOriginX[spotSelectedNum] - offset1.x() + divX;
        //        spotOriginY[spotSelectedNum] = spotOriginY[spotSelectedNum] - offset1.y() + divY;


        spotOriginOX[spotSelectedNum]=spotOriginX[spotSelectedNum]-midWidth;
        spotOriginOY[spotSelectedNum]=spotOriginY[spotSelectedNum]-midHeight;

        spotOriginPOX[spotSelectedNum]=spotOriginOX[spotSelectedNum];
        spotOriginPOY[spotSelectedNum]=spotOriginOY[spotSelectedNum];
    }
    if(spotOperation==2){
        rotation[spotSelectedNum]+=offset1.x()/5/*/windowScale*/;
        //qDebug("       %f",offset.x()/5/*/windowScale*/);
    }
    if(spotOperation==3&&(stretch[spotSelectedNum]+offset1.x()/20)>0.1){
        stretch[spotSelectedNum]+=offset1.x()/20;
    }

    selectedPoint->setX(event->x());
    selectedPoint->setY(event->y());
}

int DrawWidget::spotSelected(){
    list<QPainterPath*>::iterator temp = allPath.end();
    temp--;

    int count=allPath.size();
    QPointF tempPoint;
    int x1,y1;
    while(count>0){
        x1=(currentPoint1->x()-spotOriginX[count])*cos(-rotation[count]/180*PI)/stretch[count]-(currentPoint1->y()-spotOriginY[count])*sin(-rotation[count]/180*PI)/stretch[count];
        y1=(currentPoint1->x()-spotOriginX[count])*sin(-rotation[count]/180*PI)/stretch[count]+(currentPoint1->y()-spotOriginY[count])*cos(-rotation[count]/180*PI)/stretch[count];

        tempPoint.setX(x1);
        tempPoint.setY(y1);
        if((*temp)->contains(tempPoint)){
            selectedPoint->setX(currentPoint1->x());
            selectedPoint->setY(currentPoint1->y());
            flag=6;
            markFlag=4;
            spotSelectedNum=count;
            if(ctrlFlag){
                addCtrlSpot();
                //qDebug("RRRRRRRRRRRRRRRRRR%d",ctrlSize);
            }
            eventStyle=2;
            emit spotSelected_S();
            return 1;
        }
        count--;
        temp--;
    }
    //qDebug("RRRRRRRRRRRRRRRRRR%d",spotSelectedNum);
    return 0;
}

void DrawWidget::setHandlePoint(QMouseEvent *event){
    QPointF offset;
    float x,y,x1,y1;
    //    float x=event->x();
    //    x=x/windowScale;
    //    float y=event->y();
    //    y=y/windowScale;
    //    offset.setX(x-selectedPoint->x());
    //    offset.setY(y-selectedPoint->y());
    //    offset.setX((-midWidth+event->x()-widthChange)/windowScale-selectedPoint->x());
    //    offset.setY((-midHeight+event->y()-heightChange)/windowScale-selectedPoint->y());
    //offset.setX((event->x()-selectedPoint->x())*2);
    //offset.setY((event->y()-selectedPoint->y())*2);
    //    offset.setX(event->x()-widthChange-selectedPoint->x());
    //    offset.setY(event->y()-heightChange-selectedPoint->y());
    x=(event->x()-spotOriginX[spotSelectedNum])*cos(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum]-(event->y()-spotOriginY[spotSelectedNum])*sin(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum];
    y=(event->x()-spotOriginX[spotSelectedNum])*sin(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum]+(event->y()-spotOriginY[spotSelectedNum])*cos(-rotation[spotSelectedNum]/180*PI)/stretch[spotSelectedNum];
    x1=selectedPoint->x()-spotOriginX[spotSelectedNum];
    y1=selectedPoint->y()-spotOriginY[spotSelectedNum];
    offset.setX(x-x1);
    offset.setY(y-y1);
    list<QPointF*>::iterator oP;
    if(flag==4){
        oP = handlePointAll.begin();
        for(;oP!=handlePointAll.end();oP++){//遍历handlePointAll，找出选中一个控制点
            if(fabs((**oP).x()+spotOriginX[spotSelectedNum]-handleA.x())<0.001&&fabs((**oP).y()+spotOriginY[spotSelectedNum]-handleA.y())<0.001){
                (**oP).setX((**oP).x()+offset.x());
                (**oP).setY((**oP).y()+offset.y());//qDebug("11111111");
                //                (**oP).setX(event->x());
                //                (**oP).setY(event->y());
                handleA.setX((**oP).x()+spotOriginX[spotSelectedNum]);
                handleA.setY((**oP).y()+spotOriginY[spotSelectedNum]);
                QPointF temp;
                temp.setX((**oP).x());
                temp.setY((**oP).y());
                selectedPoint->setX((**oP).x()+spotOriginX[spotSelectedNum]);
                selectedPoint->setY((**oP).y()+spotOriginY[spotSelectedNum]);
                //handleA.setX(x-widthChange);
                //handleA.setY(y-heightChange);
                oP = handlePointAll.begin();
                for(;oP!=handlePointAll.end();oP++){//修改与选中的控制点对应的另一个控制点
                    if(fabs((**oP).x()+spotOriginX[spotSelectedNum]-handleB.x())<0.001&&fabs((**oP).y()+spotOriginY[spotSelectedNum]-handleB.y())<0.001){
                        (**oP).setX(2*handleO.x()-temp.x());//qDebug("sssssss");
                        (**oP).setY(2*handleO.y()-temp.y());
                        handleB.setX((**oP).x()+spotOriginX[spotSelectedNum]);
                        handleB.setY((**oP).y()+spotOriginY[spotSelectedNum]);
                        break;
                    }
                }
                break;
            }
        }
    }

    if(flag==5){//同上，flag为5表示选中的是第二个控制点
        oP = handlePointAll.begin();
        for(;oP!=handlePointAll.end();oP++){
            if(fabs((**oP).x()+spotOriginX[spotSelectedNum]-handleB.x())<0.001&&fabs((**oP).y()+spotOriginY[spotSelectedNum]-handleB.y())<0.001){
                //                (**oP).setX(event->x());
                //                (**oP).setY(event->y());
                (**oP).setX((**oP).x()+offset.x());//qDebug("22222222");
                (**oP).setY((**oP).y()+offset.y());
                //handleB.setX(x-widthChange);
                //handleB.setY(y-heightChange);
                handleB.setX((**oP).x()+spotOriginX[spotSelectedNum]);
                handleB.setY((**oP).y()+spotOriginY[spotSelectedNum]);
                QPointF temp;
                temp.setX((**oP).x());
                temp.setY((**oP).y());
                selectedPoint->setX((**oP).x()+spotOriginX[spotSelectedNum]);
                selectedPoint->setY((**oP).y()+spotOriginY[spotSelectedNum]);
                oP = handlePointAll.begin();
                for(;oP!=handlePointAll.end();oP++){
                    if(fabs((**oP).x()+spotOriginX[spotSelectedNum]-handleA.x())<0.001&&fabs((**oP).y()+spotOriginY[spotSelectedNum]-handleA.y())<0.001){
                        (**oP).setX(2*handleO.x()-temp.x());//qDebug("sssssss");
                        (**oP).setY(2*handleO.y()-temp.y());
                        handleA.setX((**oP).x()+spotOriginX[spotSelectedNum]);
                        handleA.setY((**oP).y()+spotOriginY[spotSelectedNum]);
                        break;
                    }
                }
                break;
            }
        }
    }

}

void DrawWidget::setSpotOperationFlag(int flag){
    spotOperation=flag;
}

void DrawWidget::wheelEvent(QWheelEvent *event){
    float tempX;
    float tempY;
    preWindowScale=windowScale;
    int canvasFlag=0;

    //判断滑轮滚动方向
    if(event->delta()>0){
        windowScale*=1.4142135623;
        if(windowScale>90){
            windowScale/=1.4142135623;
            return;
        }
        float tempCanvasX,tempCanvasY;
        tempCanvasX=canvasX*windowScale;
        tempCanvasY=canvasY*windowScale;
        //showArea;drawWidget大小发生变化
        if(tempCanvasX>showArea->viewport()->width()||tempCanvasY>showArea->viewport()->height()){
            canvasFlag=1;
        }
        //drawWidget大小没发生变化
        else if(tempCanvasX<showArea->viewport()->width()&&tempCanvasY<showArea->viewport()->height()){
            canvasFlag=0;
        }


        if(canvasFlag){
            //qDebug("%d",height());大小发生变化后的处理
            if(tempCanvasX>showArea->viewport()->width()&&tempCanvasY<showArea->viewport()->height()){
                this->setGeometry(0,0,tempCanvasX,showArea->viewport()->height());
                //qDebug("   %d %d",showArea->viewport()->width(),showArea->viewport()->height());
                //drawCanvasX();
            }
            else if(tempCanvasX<showArea->viewport()->width()&&tempCanvasY>showArea->viewport()->height()){
                this->setGeometry(0,0,showArea->viewport()->width(),tempCanvasY);
            }
            else if(tempCanvasX>showArea->viewport()->width()&&tempCanvasY>showArea->viewport()->height()){
                //qDebug("ssssssss");
                //qDebug("cy:%f,y:%f",canvasY,2*drawZ+drawY);
                this->setGeometry(0,0,tempCanvasX,tempCanvasY);
                //qDebug("%f    %f",tempCanvasX,tempCanvasY);
                //qDebug("%f    %f",drawZ*2*windowScale+drawX*windowScale,drawZ*windowScale+drawY*windowScale+drawZ*windowScale);
                //qDebug("  ");
            }

            midWidth=width()/2;
            midHeight=height()/2;
            //qDebug("out: %d  %d",width()/2,height()/2);
            //qDebug("%d %d",width()/2,height()/2);
            for(int i=1;i<drawOk+1;i++){
                spotOriginOX[i]*=1.4142135623;
                spotOriginOY[i]*=1.4142135623;
                stretch[i]=stretch[i]*1.4142135623;
                tempX=spotOriginOX[i]-spotOriginPOX[i];
                tempY=spotOriginOY[i]-spotOriginPOY[i];
                //qDebug("%f %f",tempX,tempY);
                spotOriginPOX[i]=spotOriginOX[i];
                spotOriginPOY[i]=spotOriginOY[i];
                spotOriginX[i]=spotOriginX[i]+midWidth-preMidWidth+tempX;
                spotOriginY[i]=spotOriginY[i]+midHeight-preMidHeight+tempY;
            }
            //qDebug("%f %f",preMidWidth-midWidth,preMidHeight-midHeight);
            preMidWidth=midWidth;
            preMidHeight=midHeight;
        }else{
            //如果drawWidget比showArea小，表示窗口需要还原
            this->setGeometry(0,0,showArea->viewport()->width(),showArea->viewport()->height());

            midWidth=width()/2;
            midHeight=height()/2;


            for(int i=1;i<drawOk+1;i++){
                spotOriginOX[i]*=1.4142135623;
                spotOriginOY[i]*=1.4142135623;
                stretch[i]=stretch[i]*1.4142135623;
                tempX=spotOriginOX[i]-spotOriginPOX[i];
                tempY=spotOriginOY[i]-spotOriginPOY[i];
                //qDebug("%f %f",tempX,tempY);
                spotOriginPOX[i]=spotOriginOX[i];
                spotOriginPOY[i]=spotOriginOY[i];
                spotOriginX[i]=spotOriginX[i]+midWidth-preMidWidth+tempX;
                spotOriginY[i]=spotOriginY[i]+midHeight-preMidHeight+tempY;
            }
            preMidWidth=midWidth;
            preMidHeight=midHeight;
        }

        this->update();
        //return;
    }
    else{
        windowScale/=1.4142135623;
        if(windowScale<0.09){
            windowScale*=1.4142135623;
            return;
        }

        float tempCanvasX,tempCanvasY;
        tempCanvasX=canvasX*windowScale;
        tempCanvasY=canvasY*windowScale;
        if(tempCanvasX>showArea->viewport()->width()||tempCanvasY>showArea->viewport()->height()){
            canvasFlag=1;
        }
        else if(tempCanvasX<showArea->viewport()->width()&&tempCanvasY<showArea->viewport()->height()){
            canvasFlag=0;
        }

        if(canvasFlag){
            //qDebug("%d",height());
            if(tempCanvasX>showArea->viewport()->width()&&tempCanvasY<showArea->viewport()->height()){
                this->setGeometry(0,0,tempCanvasX,showArea->viewport()->height());
                //qDebug("   %d %d",showArea->viewport()->width(),showArea->viewport()->height());
                //drawCanvasX();
            }
            else if(tempCanvasX<showArea->viewport()->width()&&tempCanvasY>showArea->viewport()->height()){
                this->setGeometry(0,0,showArea->viewport()->width(),tempCanvasY);
            }
            else if(tempCanvasX>showArea->viewport()->width()&&tempCanvasY>showArea->viewport()->height()){
                this->setGeometry(0,0,tempCanvasX,tempCanvasY);
            }

            midWidth=width()/2;
            midHeight=height()/2;
            for(int i=1;i<drawOk+1;i++){
                spotOriginOX[i]/=1.4142135623;
                spotOriginOY[i]/=1.4142135623;
                stretch[i]=stretch[i]/1.4142135623;
                tempX=spotOriginOX[i]-spotOriginPOX[i];
                tempY=spotOriginOY[i]-spotOriginPOY[i];
                spotOriginPOX[i]=spotOriginOX[i];
                spotOriginPOY[i]=spotOriginOY[i];
                spotOriginX[i]=spotOriginX[i]+midWidth-preMidWidth+tempX;
                spotOriginY[i]=spotOriginY[i]+midHeight-preMidHeight+tempY;
            }
            preMidWidth=midWidth;
            preMidHeight=midHeight;

        }else{
            //qDebug("111111111");
            //            midWidth=width()/2;
            //            midHeight=height()/2;
            this->setGeometry(0,0,showArea->viewport()->width(),showArea->viewport()->height());
            //qDebug("kuang %d %d",showArea->viewport()->width(),showArea->viewport()->height());
            //qDebug("li    %d %d",width(),height());
            midWidth=width()/2;
            midHeight=height()/2;
            for(int i=1;i<drawOk+1;i++){
                spotOriginOX[i]/=1.4142135623;
                spotOriginOY[i]/=1.4142135623;
                stretch[i]=stretch[i]/1.4142135623;
                tempX=spotOriginOX[i]-spotOriginPOX[i];
                tempY=spotOriginOY[i]-spotOriginPOY[i];
                spotOriginPOX[i]=spotOriginOX[i];
                spotOriginPOY[i]=spotOriginOY[i];
                spotOriginX[i]=spotOriginX[i]+midWidth-preMidWidth+tempX;
                spotOriginY[i]=spotOriginY[i]+midHeight-preMidHeight+tempY;
            }
            preMidWidth=midWidth;
            preMidHeight=midHeight;
        }
        this->update();
    }
    eventStyle=5;
    emit ChildWindowEvent();
    emit getShowStretch();
}
