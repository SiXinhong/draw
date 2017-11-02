#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,QColor a,QColor b,QColor c,QColor d) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    aa = a;
    ab = b;
    ac = c;
    ad = d;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(Qt::NoPen);

    p.setBrush(QBrush(aa,Qt::SolidPattern));
    p.drawRect(100,100,100,100);

    p.setBrush(QBrush(ab,Qt::SolidPattern));
    p.drawRect(200,100,100,100);

    p.setBrush(QBrush(ac,Qt::SolidPattern));
    p.drawRect(300,100,100,100);

    p.setBrush(QBrush(ad,Qt::SolidPattern));
    p.drawRect(400,100,100,100);
}
