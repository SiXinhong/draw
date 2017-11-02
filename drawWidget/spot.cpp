#include "spot.h"

spot::spot()
{
}
void spot::setDrawOk(int tempDrawOk){
    drawOk=tempDrawOk;
}

int spot::getDrawOk(){
    return drawOk;
    qDebug("~~~~~~%d",drawOk);
}
void spot::setWidHei(float tempW,float tempH){
    width=tempW;
    height=tempH;

}
void spot::getWidHei(float &tempW,float &tempH){
    tempW=width;
    tempH=height;
}

void spot::setCenter(float tempW,float tempH,float preTempW,float preTempH){
    for(int i=1;i<drawOk+1;i++){
        midWidth=tempW;
        midHeight=tempH;
        preMidWidth=preTempW;
        preMidHeight=preTempH;
    }
}

void spot::getCenter(float &tempW,float &tempH,float &preTempW,float &preTempH){
    for(int i=1;i<drawOk+1;i++){
        tempW=midWidth;
        tempH=midHeight;
        preTempW=preMidWidth;
        preTempH=preMidHeight;
    }
}

void spot::setSpotNum(int *tempSet){
    for(int i=1;i<drawOk+1;i++){
        spotNum[i]=*(tempSet+i);
    }
}

void spot::getSpotNum(int *tempGet){
    for(int i=1;i<drawOk+1;i++){
        tempGet[i]=spotNum[i];
    }
}

void spot::setSpotOrigin(float*tempX,float*tempY,float*tempOX,float*tempOY,float*tempPOX,float*tempPOY){
    for(int i=1;i<drawOk+1;i++){
        spotOriginX[i]=*(tempX+i);
        spotOriginY[i]=*(tempY+i);
        spotOriginOX[i]=*(tempOX+i);
        spotOriginOY[i]=*(tempOY+i);
        spotOriginPOX[i]=*(tempPOX+i);
        spotOriginPOY[i]=*(tempPOY+i);
    }
    //float spotOriginX[maxSize];
    //float spotOriginY[maxSize];
}
void spot::getSpotOrigin(float*tempX,float*tempY,float*tempOX,float*tempOY,float*tempPOX,float*tempPOY){
    for(int i=1;i<drawOk+1;i++){
        *(tempX+i)=spotOriginX[i];
        *(tempY+i)=spotOriginY[i];
        *(tempOX+i)=spotOriginOX[i];
        *(tempOY+i)=spotOriginOY[i];
        *(tempPOX+i)=spotOriginPOX[i];
        *(tempPOY+i)=spotOriginPOY[i];
    }
}

void spot::setStretch(float *tempSet){
    for(int i=1;i<drawOk+1;i++){
        stretch[i]=tempSet[i];
    }
}

void spot::getStretch(float *tempGet){
    for(int i=1;i<drawOk+1;i++){
        tempGet[i]=stretch[i];
    }
}

void spot::setRotation(float *tempSet){
    for(int i=1;i<drawOk+1;i++){
        rotation[i]=tempSet[i];
    }
}

void spot::getRotation(float *tempGet){
    for(int i=1;i<drawOk+1;i++){
        tempGet[i]=rotation[i];
    }
}

void spot::setOpointAll(list<QPointF*>tempOPointAll){
    oPointAll.clear();
    QPointF *tempPoint;
    list<QPointF*>::iterator oP = tempOPointAll.begin();
    for(;oP!=tempOPointAll.end();oP++){
        tempPoint=new QPointF;
        tempPoint->setX((**oP).x());
        tempPoint->setY((**oP).y());
        oPointAll.push_back(tempPoint);
    }
}

void spot::getOpointAll(list<QPointF*>&tempOPointAll){
    QPointF *tempPoint;
    list<QPointF*>::iterator oP = oPointAll.begin();
    for(;oP!=oPointAll.end();oP++){
        tempPoint=new QPointF;
        tempPoint->setX((**oP).x());
        tempPoint->setY((**oP).y());
        tempOPointAll.push_back(tempPoint);
    }
}

void spot::setHandlePointAll(list<QPointF*>tempHandlePointAll){
    handlePointAll.clear();
    QPointF *tempPoint;
    list<QPointF*>::iterator oP = tempHandlePointAll.begin();
    for(;oP!=tempHandlePointAll.end();oP++){
        tempPoint=new QPointF;
        tempPoint->setX((**oP).x());
        tempPoint->setY((**oP).y());
        handlePointAll.push_back(tempPoint);
    }
}

void spot::getHandlePointAll(list<QPointF*>&tempHandlePointAll){
    QPointF *tempPoint;
    list<QPointF*>::iterator oP = handlePointAll.begin();
    for(;oP!=handlePointAll.end();oP++){
        tempPoint=new QPointF;
        tempPoint->setX((**oP).x());
        tempPoint->setY((**oP).y());
        tempHandlePointAll.push_back(tempPoint);
    }
}

void spot::setAllPath(list<QPainterPath*>tempAllPath){
    allPath.clear();
    QPainterPath *tempPath;
    list<QPainterPath*>::iterator oP= tempAllPath.begin();
    for(;oP!=tempAllPath.end();oP++){
        tempPath=new QPainterPath;
        *tempPath=(**oP);
        allPath.push_back(tempPath);
    }
}

void spot::getAllPath(list<QPainterPath*>&tempAllPath){
    QPainterPath *tempPath;
    list<QPainterPath*>::iterator oP= allPath.begin();
    for(;oP!=allPath.end();oP++){
        tempPath=new QPainterPath;
        *tempPath=(**oP);
        tempAllPath.push_back(tempPath);
    }
}

void spot::setAllColor(spotColorAll tempAllColor){
    for(int i=1;i<drawOk+1;i++){
        allColor.index[i]=tempAllColor.index[i];
        allColor.myColor[i]=tempAllColor.myColor[i];
    }
}

void spot::getAllColor(spotColorAll &tempAllColor){
    for(int i=1;i<drawOk+1;i++){
        tempAllColor.index[i]=allColor.index[i];
        tempAllColor.myColor[i]=allColor.myColor[i];
    }
}

void spot::setCanvas(float tempX,float tempY,float tempZ){
    drawX=tempX;
    drawY=tempY;
    drawZ=tempZ;
}

void spot::getCanvas(float &x,float&y,float&z){
    x=drawX;
    y=drawY;
    z=drawZ;
}

void spot::setWindowScale(float tempSet){
    windowScale=tempSet;
}

void spot::getWindowScale(float &tempGet){
    tempGet=windowScale;
}

void spot::getMidWidHei(float &tempW, float &tempH){
    tempW=midWidth;
    tempH=midHeight;
}

void spot::setAllColorIndex(int *tempSpotIndex,int tempBackGroundIndex){
    for(int i=1;i<drawOk+1;i++){
        spotColorIndex[i]=*(tempSpotIndex+i);
        backGroundColorIndex=tempBackGroundIndex;
    }
}

void spot::getAllColorIndex(int *tempSpotIndex,int &tempBackGroundIndex){
    for(int i=1;i<drawOk+1;i++){
        *(tempSpotIndex+i)=spotColorIndex[i];
        tempBackGroundIndex=backGroundColorIndex;
    }
}

void spot::setBackGroundColor(QColor tempColor){
    backGroundColor=tempColor;
    //backGroundColorIndex=index;
}

void spot::getBackGroundColor(QColor &tempColor){
    tempColor=backGroundColor;
    //index=backGroundColorIndex;
}
