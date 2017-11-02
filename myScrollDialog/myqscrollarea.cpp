#include "myqscrollarea.h"

myQScrollArea::myQScrollArea()
{
    preWidth=this->viewport()->width();
    preHeight=this->viewport()->height();
}

void myQScrollArea::resizeEvent(QResizeEvent *event){
    //qDebug("Sssssss");
    centralDraw->resizeEvent(event);
    centralDraw->setCenter(this->viewport()->width()/2,this->viewport()->height()/2);
//    if(geometry().width()>centralDraw->geometry().width()){
//        centralDraw->setGeometry(0,0,this->viewport()->width(),centralDraw->geometry().height());
//    }
//    if(geometry().height()>centralDraw->geometry().height()){
//        centralDraw->setGeometry(0,0,centralDraw->geometry().width(),this->viewport()->height());
//    }
    if(this->viewport()->width()>centralDraw->geometry().width()){
        centralDraw->setGeometry(0,0,this->viewport()->width(),this->viewport()->height());
    }
    if(this->viewport()->height()>centralDraw->geometry().height()){
        centralDraw->setGeometry(0,0,this->viewport()->width(),this->viewport()->height());
    }
    centralDraw->setCenter(this->viewport()->width()/2,this->viewport()->height()/2);

    if(preWidth!=this->width()||preHeight!=this->height()){
        centralDraw->setCenter(this->viewport()->width()/2,this->viewport()->height()/2);
        preWidth=this->width();
        preHeight=this->height();
        //qDebug("%d %d",this->geometry().width(),this->geometry().height());
        //qDebug("11111");
    }
    centralDraw->setCenter(this->viewport()->width()/2,this->viewport()->height()/2);
    //qDebug("%d %d",this->geometry().width(),this->geometry().height());
    //qDebug("%d %d",this->viewport()->width(),this->viewport()->height());
    //qDebug("11111");
    //qDebug("%d %d",this->geometry().width(),this->geometry().height());
}

void myQScrollArea::getDrawWidget(DrawWidget *temp){
    centralDraw=temp;
}

