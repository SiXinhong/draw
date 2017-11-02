#ifndef GETPOINT_H
#define GETPOINT_H

#include<list>
#include<QPointF>
using namespace std;
class getPoint
{
public:
        getPoint(void);
        ~getPoint(void);
        void getMid(list<QPointF*>oPoint,list<QPointF*>&midPoint,list<QPointF*>&midM);
        void getTraCoo(list<QPointF*>oPoint,list<QPointF*>midM,list<QPointF*>&tranCoo);
        void getThePoint(list<QPointF*>&midPoint,list<QPointF*>tranCoo,list<QPointF*>&thePoint);
};
#endif // WIDGET_H
