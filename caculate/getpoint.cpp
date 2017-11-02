#include"getpoint.h"


getPoint::getPoint(void)
{
}


getPoint::~getPoint(void)
{
}


void getPoint::getMid(list<QPointF*>oPoint,list<QPointF*>&midPoint,list<QPointF*>&midM){
        list<QPointF*>::iterator pointF;//遍历oPoint
        list<QPointF*>::iterator pointN;
        QPointF *addMidPoint;
        QPointF *addM;


        //求原始点中点
        //求第一个点对应中点
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        pointF--;
        addM=new(QPointF);
        (*addM).setX(((**pointF).x()+(**pointN).x())/2);
        (*addM).setY(((**pointF).y()+(**pointN).y())/2);
        midM.push_back(addM);


        //求中间的点对应的中点
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF--;
        pointN++;
        for(;pointN!=oPoint.end();pointN++,pointF++){
                addM=new(QPointF);
                (*addM).setX(((**pointF).x()+(**pointN).x())/2);
                (*addM).setY(((**pointF).y()+(**pointN).y())/2);
                midM.push_back(addM);
                 }


        //最后中点
        addM=new(QPointF);
        pointN=oPoint.begin();
        (*addM).setX(((**pointF).x()+(**pointN).x())/2);
        (*addM).setY(((**pointF).y()+(**pointN).y())/2);
        midM.push_back(addM);


        //第一点对应的三等分点(一半);
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        addMidPoint=new(QPointF);
        pointF--;



        (*addMidPoint).setX(((**pointF).x()+(**pointN).x()*2)/3);
        (*addMidPoint).setY(((**pointF).y()+(**pointN).y()*2)/3);
        midPoint.push_back(addMidPoint);


        //中间的三等分点
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF--;
        pointN++;
        for(;pointN!=oPoint.end();pointN++,pointF++){
                addMidPoint=new(QPointF);
                (*addMidPoint).setX(((**pointF).x()*2+(**pointN).x())/3);
                (*addMidPoint).setY(((**pointF).y()*2+(**pointN).y())/3);
                midPoint.push_back(addMidPoint);

                addMidPoint=new(QPointF);
                (*addMidPoint).setX(((**pointF).x()+(**pointN).x()*2)/3);
                (*addMidPoint).setY(((**pointF).y()+(**pointN).y()*2)/3);
                midPoint.push_back(addMidPoint);
                 }



        //倒数第二个点的三等分点
        pointN=oPoint.begin();
        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()*2+(**pointN).x())/3);
        (*addMidPoint).setY(((**pointF).y()*2+(**pointN).y())/3);
        midPoint.push_back(addMidPoint);

        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()+(**pointN).x()*2)/3);
        (*addMidPoint).setY(((**pointF).y()+(**pointN).y()*2)/3);

        midPoint.push_back(addMidPoint);



        //最后一个点（一半）的三等分点
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        pointF--;
        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()*2+(**pointN).x())/3);
        (*addMidPoint).setY(((**pointF).y()*2+(**pointN).y())/3);
        midPoint.push_back(addMidPoint);
}
void getPoint::getTraCoo(list<QPointF*>oPoint,list<QPointF*>midM,list<QPointF*>&tranCoo){//计算便宜距离
        list<QPointF*>::iterator pointO;
        list<QPointF*>::iterator pointM;
        QPointF *addTranCoo;

        pointO=oPoint.begin();
        pointM=midM.begin();
        for(;pointO!=oPoint.end();pointO++){
                addTranCoo=new(QPointF);
                (*addTranCoo).setX((**pointO).x()-(**pointM).x());
                (*addTranCoo).setY((**pointO).y()-(**pointM).y());
                pointM++;
                tranCoo.push_back(addTranCoo);
                 }
}


void getPoint::getThePoint(list<QPointF*>&midPoint,list<QPointF*>tranCoo,list<QPointF*>&thePoint){
        list<QPointF*>::iterator midPF;
        list<QPointF*>::iterator midPN;
        list<QPointF*>::iterator tranP;
        QPointF *addThePoint;


        //第一个点的一半
        midPF=midPoint.begin();
        tranP=tranCoo.begin();
        addThePoint=new(QPointF);
        (*addThePoint).setX((**midPF).x()+(**tranP).x());
        (*addThePoint).setY((**midPF).y()+(**tranP).y());
        thePoint.push_back(addThePoint);



        //后边的点
        midPF++;
        midPN=++midPF;
        midPF--;
        tranP++;
                while(midPN!=midPoint.end()){
                        addThePoint=new(QPointF);
                        (*addThePoint).setX((**midPF).x()+(**tranP).x());
                        (*addThePoint).setY((**midPF).y()+(**tranP).y());
                        thePoint.push_back(addThePoint);

                        addThePoint=new(QPointF);
                        (*addThePoint).setX((**midPN).x()+(**tranP).x());
                        (*addThePoint).setY((**midPN).y()+(**tranP).y());
                        thePoint.push_back(addThePoint);

                        tranP++;
                        midPN++;
                        midPF=midPN;
                        midPN++;
                 }


                addThePoint=new(QPointF);
                tranP=tranCoo.begin();
                (*addThePoint).setX((**midPF).x()+(**tranP).x());
                (*addThePoint).setY((**midPF).y()+(**tranP).y());
                thePoint.push_back(addThePoint);

}
