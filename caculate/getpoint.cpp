#include"getpoint.h"


getPoint::getPoint(void)
{
}


getPoint::~getPoint(void)
{
}


void getPoint::getMid(list<QPointF*>oPoint,list<QPointF*>&midPoint,list<QPointF*>&midM){
        list<QPointF*>::iterator pointF;//����oPoint
        list<QPointF*>::iterator pointN;
        QPointF *addMidPoint;
        QPointF *addM;


        //��ԭʼ���е�
        //���һ�����Ӧ�е�
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        pointF--;
        addM=new(QPointF);
        (*addM).setX(((**pointF).x()+(**pointN).x())/2);
        (*addM).setY(((**pointF).y()+(**pointN).y())/2);
        midM.push_back(addM);


        //���м�ĵ��Ӧ���е�
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


        //����е�
        addM=new(QPointF);
        pointN=oPoint.begin();
        (*addM).setX(((**pointF).x()+(**pointN).x())/2);
        (*addM).setY(((**pointF).y()+(**pointN).y())/2);
        midM.push_back(addM);


        //��һ���Ӧ�����ȷֵ�(һ��);
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        addMidPoint=new(QPointF);
        pointF--;



        (*addMidPoint).setX(((**pointF).x()+(**pointN).x()*2)/3);
        (*addMidPoint).setY(((**pointF).y()+(**pointN).y()*2)/3);
        midPoint.push_back(addMidPoint);


        //�м�����ȷֵ�
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



        //�����ڶ���������ȷֵ�
        pointN=oPoint.begin();
        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()*2+(**pointN).x())/3);
        (*addMidPoint).setY(((**pointF).y()*2+(**pointN).y())/3);
        midPoint.push_back(addMidPoint);

        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()+(**pointN).x()*2)/3);
        (*addMidPoint).setY(((**pointF).y()+(**pointN).y()*2)/3);

        midPoint.push_back(addMidPoint);



        //���һ���㣨һ�룩�����ȷֵ�
        pointF=oPoint.begin();
        pointN=++pointF;
        pointF=oPoint.end();
        pointF--;
        addMidPoint=new(QPointF);
        (*addMidPoint).setX(((**pointF).x()*2+(**pointN).x())/3);
        (*addMidPoint).setY(((**pointF).y()*2+(**pointN).y())/3);
        midPoint.push_back(addMidPoint);
}
void getPoint::getTraCoo(list<QPointF*>oPoint,list<QPointF*>midM,list<QPointF*>&tranCoo){//������˾���
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


        //��һ�����һ��
        midPF=midPoint.begin();
        tranP=tranCoo.begin();
        addThePoint=new(QPointF);
        (*addThePoint).setX((**midPF).x()+(**tranP).x());
        (*addThePoint).setY((**midPF).y()+(**tranP).y());
        thePoint.push_back(addThePoint);



        //��ߵĵ�
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
