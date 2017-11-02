#ifndef SPOT_H
#define SPOT_H
#include<list>
#include<QPointF>
#include<QPainterPath>
#include"window/spotColorAll.h"
#include<QColor>
#define maxSize 1000
using namespace std;
class spot
{
public:
    spot();
    void setDrawOk(int);
    int  getDrawOk();
    void getWidHei(float&,float&);
    void setWidHei(float,float);
    void setCenter(float midWidth,float midHeight,float preMidWidth,float preMidHeight);
    void getCenter(float &midWidth,float &midHeight,float &preMidWidth,float &preMidHeight);
    void setSpotNum(int *);
    void getSpotNum(int *);
    void setStretch(float *);
    void getStretch(float *);
    void setRotation(float *);
    void getRotation(float *);
    void setOpointAll(list<QPointF*>tempOPointAll);
    void getOpointAll(list<QPointF*>&tempOPointAll);
    void setHandlePointAll(list<QPointF*>tempHandlePointAll);
    void getHandlePointAll(list<QPointF*>&tempHandlePointAll);

    void setAllPath(list<QPainterPath*>tempAllPath);
    void getAllPath(list<QPainterPath*>&tempAllPath);
    void setAllColor(spotColorAll tempAllColor);
    void getAllColor(spotColorAll &tempAllColor);

    void setBackGroundColor(QColor tempColor);
    void getBackGroundColor(QColor &tempColor);

    void setAllColorIndex(int *,int);
    void getAllColorIndex(int *,int&);

    void setCanvas(float tempX,float tempY,float tempZ);
    void getCanvas(float &tempX,float &tempY,float &tempZ);
    void setWindowScale(float);
    void getWindowScale(float&);
    void setSpotOrigin(float*,float*,float*,float*,float*,float*);
    void getSpotOrigin(float*,float*,float*,float*,float*,float*);

    void getMidWidHei(float&,float&);
private:
    int drawOk;
    float spotOriginX[maxSize];
    float spotOriginY[maxSize];
    float spotOriginOX[maxSize];
    float spotOriginOY[maxSize];
    float spotOriginPOX[maxSize];
    float spotOriginPOY[maxSize];
    int spotNum[maxSize];
    float stretch[maxSize];
    float rotation[maxSize];
    float width;
    float height;
    float midWidth;
    float midHeight;
    float preMidWidth;
    float preMidHeight;
    list<QPointF*>oPointAll;//用户画的原点
    list<QPointF*>handlePointAll;
    list<QPainterPath*>allPath;
    spotColorAll allColor;
    QColor backGroundColor;
    //int backGroundColorIndex;
    float drawX;
    float drawY;
    float drawZ;
    float windowScale;
//序列化专用
    int spotColorIndex[maxSize];
    int backGroundColorIndex;
};



#endif // SPOT_H
