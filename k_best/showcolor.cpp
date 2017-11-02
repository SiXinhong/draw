#include "showcolor.h"
#include "ui_mainwindow.h"

showColor::showColor(QWidget *parent,QColor a,QColor b,QColor c) :
    QMainWindow(parent),
    ui(new Ui::showColor)
{
    aa = a;
    ab = b;
    ac = c;
    ui->setupUi(this);
}

showColor::~showColor()
{
    delete ui;
}

void showColor::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::NoPen);

    p.setBrush(QBrush(aa,Qt::SolidPattern));
    p.drawRect(100,100,100,100);

    p.setBrush(QBrush(ab,Qt::SolidPattern));
    p.drawRect(200,100,100,100);

    p.setBrush(QBrush(ac,Qt::SolidPattern));
    p.drawRect(300,100,100,100);

}
