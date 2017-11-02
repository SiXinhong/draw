#ifndef SAVESPOT_H
#define SAVESPOT_H
#include <fstream>
#include<cstdio>
#include<cstring>
#include<string>
#include<QDebug>
#include<QPointF>
#include <sstream>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include<list>
#include<QFile>
#include <QStringList>
#include"drawWidget/spot.h"
using namespace std;
#define maxSize 1000
#define pi 3.1415926535
class saveSpot
{
public:
    int digitalFlag;
    saveSpot();
    void saveCanvas(spot *temp,QString fileName);
    void readCanvas(spot *temp,QString fileName);
    void saveSpotPoint(int num,float saveP[300][2]);
    string readSpotPoint(int &readNum,int *num,float saveP[300][2],int mark);
    //---------xiaotian  测试数码迷彩读取斑点
    string readDigitalSpotPoint(int edge[10][10],int &readNum,int mark);
    void strToIntArray(QString str,int temp[10][10],int t);

    void readBigSpotPoint(int *num,float saveP[300][2],int mark);
    void getAutoCAD(int hasNum,int spotNum[maxSize],int colorIndex[maxSize],int (*num)[1000],QPointF *tempP[5000][100],int area,float width,float height);
    void getAutoCADAll(int hasNum,int spotNum[maxSize],int colorIndex[maxSize],int (*num)[1000],QPointF *tempP[5000][100],int area,int x,int y,int z);
    void autoCADAll();
    list<QString> readOrig(float*,float*,string);
private:
    float saveP[300][2];
    int count;
    string iconColor[31];
    int get;//用来取随机斑点
};

#endif // SAVESPOT_H
