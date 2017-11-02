#include "window/wumainwin.h"
#include "ui_wumainwin.h"
#include<QTextCodec>
#include<QFileDialog>
#include<QDir>
#include<QtOpenGL>

wumainWin::wumainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wumainWin)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));

    flag=0;

    openObj=new QToolButton(this);
    //openObj->setCheckable(true);
    openObj->setToolTip(tr("打开文件"));
    openObj->setIcon(QPixmap("icon/openobj.png"));
    openObj->setMinimumHeight(45);
    openObj->setMinimumWidth(45);
    ui->toolBar->addWidget(openObj);

    savePic=new QToolButton(this);
    //savePic->setCheckable(true);
    savePic->setToolTip(tr("保存图片"));
    savePic->setIcon(QPixmap("icon/savepic.png"));
    savePic->setMinimumHeight(45);
    savePic->setMinimumWidth(45);
    ui->toolBar->addWidget(savePic);

//    changBack=new QToolButton(this);
//    changBack->setToolTip(tr("选择背景"));
//    changBack->setIcon(QPixmap("icon/changeBack.png"));
//    changBack->setMinimumHeight(45);
//    changBack->setMinimumWidth(45);
//    ui->toolBar->addWidget(changBack);
//    changBack->setEnabled(false);
//    changBack->hide();

    connect(openObj,SIGNAL(clicked()),this,SLOT(openS()));
    connect(savePic,SIGNAL(clicked()),this,SLOT(savePicS()));
    //connect(changBack,SIGNAL(clicked()),this,SLOT(changBackS()));



}

void wumainWin::openS(){

    QString filename=QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "Document files (*.obj );;All files(*.*)");

        if (filename.isNull()){
            QMessageBox::information(this, tr("提示"),tr("没有选中文件"));
            return;
        }

    QByteArray ba=filename.toLocal8Bit();

    test=new wumian(this);
    test->modelF=ba.data();
    GLMmodel *model=glmReadOBJ(ba.data());
    test->model=model;
    test->updateGL();
    setCentralWidget(test);


}

void wumainWin::savePicS(){   

    QPixmap pixmap=QPixmap::grabWindow(QApplication::desktop()->winId(),QWidget::x(),QWidget::y(),this->width()+15,this->height()+35);

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Open Config"),
            "",
            tr("Config Files (*.png)"));


    if (!fileName.isNull())
        {

            QByteArray qb=fileName.toLocal8Bit();
            //QPixmap pixmap = QPixmap::grabWidget(this->centralWidget());

            pixmap.save(qb.data(), "png");
            QMessageBox::information(this, tr("提示"),tr("图片保存成功"));
        }
    else
        QMessageBox::information(this, tr("提示"),tr("图片保存失败"));



}


void wumainWin::changBackS(){

    QString filename=QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "Document files (*.jpg *.png);;All files(*.*)");

        if (filename.isNull()){
            QMessageBox::information(this, tr("提示"),tr("没有选中文件"));
            return;
        }

        QByteArray b=filename.toLocal8Bit();
        test->setBackFlag=true;
        test->backGroundFile=b.data();
        test->updateGL();


}

wumainWin::~wumainWin()
{

    delete ui;
}
