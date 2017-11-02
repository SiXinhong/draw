#ifndef SPOTCOLORALL_H
#define SPOTCOLORALL_H
#define maxSize 1000
#define PI 3.1415926535
#include<QColor>
#include<QString>
using namespace std;
typedef struct{
    QColor myColor[maxSize];
    int index[maxSize];
    QString colorName[maxSize];
}spotColorAll;

typedef struct{
    int spotLineWidth;
    int markNum;//ÇúÂÊÏ¡Êè¶È
    int minResolution;//ÇúÂÊ°ë¾¶
    QColor spotLineColor;
    int keyPointSize;
    QColor keyPointColor;
    int handlePointSize;
    int hPointLineWidth;
    QColor handlePointColor;
    int handlePointR,handlePointG,handlePointB;

}spotChangeSpot;
#endif // SPOTCOLORALL_H
