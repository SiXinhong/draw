#include "childwindow.h"
#include "ui_childwindow.h"
#include<QToolBar>
#include<QToolButton>
#include"model/first_opengl.h"
#include"model/fiveview.h"
#include <QTextCodec>
#include<model/glm.h>
#include<QMessageBox>


childWindow::childWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::childWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));

    fiveViewFlag=0;
    model=NULL;
    addMyToolBar();

    //视图切换
    connect(showFiveView,SIGNAL(clicked()),this,SLOT(showFiveViewS()));
    connect(xy,SIGNAL(clicked()),this,SLOT(xyMap()));
    connect(yz,SIGNAL(clicked()),this,SLOT(yzMap()));
    connect(xz,SIGNAL(clicked()),this,SLOT(xzMap()));
    connect(line,SIGNAL(clicked()),this,SLOT(linerMap()));
    connect(cube,SIGNAL(clicked()),this,SLOT(cubeMap()));
    connect(sphere,SIGNAL(clicked()),this,SLOT(sphereMap()));
    connect(fiveImage,SIGNAL(clicked()),this,SLOT(fiveImageS()));
    //文件打开
    connect(openObj,SIGNAL(clicked()),this,SLOT(openobjS()));
    connect(changeback,SIGNAL(clicked()),this,SLOT(changebackS()));
    connect(planeFlag,SIGNAL(clicked()),this,SLOT(planeFlagS()));
    connect(boxFlag,SIGNAL(clicked()),this,SLOT(boxFlagS()));

}

childWindow::~childWindow()
{
    glmDelete(c->model);
    delete ui;

}


void childWindow::addMyToolBar(){

    openObj=new QToolButton(this);
    //openObj->setCheckable(true);
    openObj->setToolTip(tr("打开文件"));
    openObj->setIcon(QPixmap("icon/openobj.png"));
    openObj->setMinimumHeight(45);
    openObj->setMinimumWidth(45);
    ui->toolBar->addWidget(openObj);


    showFiveView=new QToolButton(this);
    //showFiveView->setCheckable(true);
    showFiveView->setToolTip(tr("切换视图"));
    showFiveView->setIcon(QPixmap("icon/5.png"));
    showFiveView->setMinimumHeight(45);
    showFiveView->setMinimumWidth(45);
    ui->toolBar->addWidget(showFiveView);

    xy=new QToolButton(this);
    // xy->setCheckable(true);
    xy->setToolTip(tr("xy方向贴图"));
    xy->setIcon(QPixmap("icon/xy.png"));
    xy->setMinimumHeight(45);
    xy->setMinimumWidth(45);
    ui->toolBar->addWidget(xy);
    xy->setEnabled(false);

    yz=new QToolButton(this);
    // yz->setCheckable(true);
    yz->setToolTip(tr("yz方向贴图"));
    yz->setIcon(QPixmap("icon/yz.png"));
    yz->setMinimumHeight(45);
    yz->setMinimumWidth(45);
    ui->toolBar->addWidget(yz);
    yz->setEnabled(false);

    xz=new QToolButton(this);
    // xz->setCheckable(true);
    xz->setToolTip(tr("xz方向贴图"));
    xz->setIcon(QPixmap("icon/xz.png"));
    xz->setMinimumHeight(45);
    xz->setMinimumWidth(45);
    ui->toolBar->addWidget(xz);
    xz->setEnabled(false);

    line=new QToolButton(this);
   // line->setCheckable(true);
    line->setToolTip(tr("线性贴图"));
    line->setIcon(QPixmap("icon/line.png"));
    line->setMinimumHeight(45);
    line->setMinimumWidth(45);
    ui->toolBar->addWidget(line);
    line->setEnabled(false);

    cube=new QToolButton(this);
  //  cube->setCheckable(true);
    cube->setToolTip(tr("立方体贴图"));
    cube->setIcon(QPixmap("icon/cube.png"));
    cube->setMinimumHeight(45);
    cube->setMinimumWidth(45);
    ui->toolBar->addWidget(cube);
    cube->setEnabled(false);

    sphere=new QToolButton(this);
   // sphere->setCheckable(true);
    sphere->setToolTip(tr("球体贴图"));
    sphere->setIcon(QPixmap("icon/sphere.png"));
    sphere->setMinimumHeight(45);
    sphere->setMinimumWidth(45);
    ui->toolBar->addWidget(sphere);
    sphere->setEnabled(false);

    fiveImage=new QToolButton(this);
   // fiveImage->setCheckable(true);
    fiveImage->setToolTip(tr("清空贴图"));
    fiveImage->setIcon(QPixmap("icon/empty.png"));
    fiveImage->setMinimumHeight(45);
    fiveImage->setMinimumWidth(45);
    ui->toolBar->addWidget(fiveImage);
    fiveImage->setEnabled(false);

    changeback=new QToolButton(this);
   // sphere->setCheckable(true);
    changeback->setToolTip(tr("选择背景"));
    changeback->setIcon(QPixmap("icon/changeBack.png"));
    changeback->setMinimumHeight(45);
    changeback->setMinimumWidth(45);
    ui->toolBar->addWidget(changeback);
    changeback->setEnabled(false);

    planeFlag=new QToolButton(this);
   // sphere->setCheckable(true);
    planeFlag->setToolTip(tr("显示/显示平面格"));
    planeFlag->setIcon(QPixmap("icon/plane.png"));
    planeFlag->setMinimumHeight(45);
    planeFlag->setMinimumWidth(45);
    ui->toolBar->addWidget(planeFlag);
    planeFlag->setEnabled(false);

    boxFlag=new QToolButton(this);
   // sphere->setCheckable(true);
    boxFlag->setToolTip(tr("显示/显示包围盒"));
    boxFlag->setIcon(QPixmap("icon/box.png"));
    boxFlag->setMinimumHeight(45);
    boxFlag->setMinimumWidth(45);
    ui->toolBar->addWidget(boxFlag);
    boxFlag->setEnabled(false);


}
//void childWindow::closeEvent(QCloseEvent *event){
//    //qDebug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
////    if(this->model!=NULL){
////        ////////////////////////////////////////////////////@@@@@@@@@@@
////        glmDelete(model);
////    }
////    if(this!=NULL)
////     delete this;
//    emit ChildWindowEvent();
//}

void childWindow::showFiveViewS(){
    if(model!=NULL){

    if(fiveViewFlag==0)
    {
        changeback->setEnabled(false);
        boxFlag->setEnabled(false);
        planeFlag->setEnabled(false);
            c->hide();
            ff->show();
            fiveViewFlag=1;

     }
     else {
        changeback->setEnabled(true);
        boxFlag->setEnabled(true);
        planeFlag->setEnabled(true);
            ff->hide();
            c->show();
            fiveViewFlag=0;
        }
    }
    else
        QMessageBox::information(this, "tip", "No model");

}

void childWindow::fiveImageS(){
    if(fiveViewFlag==0)
       {

           c->textureFlag=0;
           c->load_OBJ();
           c->update();
       }
    else{

        ff->texflag=0;
        ff->loadFiveView();
        ff->update();
    }
}

void childWindow::xyMap()
{
    if(fiveViewFlag==0)
       {
           c->textureFlag=1;
           c->load_OBJ();
           c->update();
       }
    else{
        ff->texflag=1;
        ff->loadFiveView();
        ff->update();
    }


}

void childWindow::yzMap()
{
   if(fiveViewFlag==0){
       c->textureFlag=2;
       c->load_OBJ();
       c->update();
   }

   else{
       ff->texflag=2;
       ff->loadFiveView();
       ff->update();
   }

}

void childWindow::xzMap()
{
   if(fiveViewFlag==0){
       c->textureFlag=3;
       c->load_OBJ();
       c->update();
   }

   else{
       ff->texflag=3;
       ff->loadFiveView();
       ff->update();
   }

}

void childWindow::linerMap()
{
   if(fiveViewFlag==0){
       c->textureFlag=4;
       c->load_OBJ();
       c->update();
   }

   else{
       ff->texflag=4;
       ff->loadFiveView();
       ff->update();
   }

}

void childWindow::cubeMap()
{
  if(fiveViewFlag==0){
      c->textureFlag=5;
      c->load_OBJ();
      c->update();
  }
    else{
      ff->texflag=5;
      ff->loadFiveView();
      ff->update();
  }

}

void childWindow::sphereMap()
{
   if(fiveViewFlag==0){
       c->textureFlag=6;
       c->load_OBJ();
       c->update();
   }
   else{
       ff->texflag=6;
       ff->loadFiveView();
       ff->update();
   }


}


void childWindow::openobjS(){
    QString filename=QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "Document files (*.obj *.doc);;All files(*.*)");

    if (filename.isNull()){
        QMessageBox::information(this, tr("文件"),tr("没有选中文件"));
         return;
    }

    QByteArray ba=filename.toLocal8Bit();
    if(this->model!=NULL){
        ////////////////////////////////////////////////////@@@@@@@@@@@
        glmDelete(model);
    }

    this->model=glmReadOBJ(ba.data());

        c=new first_opengl(this);
        c->model=model;
        ff=new fiveView(this);
        ff->model=model;

        QSplitter *sp=new QSplitter;
        sp->addWidget(c);
        sp->addWidget(ff);
        this->setCentralWidget(sp);
        ff->hide();

        //禁用hand
           for(int i = 0; i<sp->count();i++)
            {
            QSplitterHandle *handl = sp->handle(i);
            handl->setEnabled(false);
            }

           xy->setEnabled(true);
           yz->setEnabled(true);
           xz->setEnabled(true);
           line->setEnabled(true);
           sphere->setEnabled(true);
           cube->setEnabled(true);
           fiveImage->setEnabled(true);
           changeback->setEnabled(true);
           boxFlag->setEnabled(true);
           planeFlag->setEnabled(true);

           QPalette pale;
           pale.setColor(QPalette::ButtonText,QColor(0,0,255));
           xy->setPalette(pale);
           yz->setPalette(pale);
           xz->setPalette(pale);
           line->setPalette(pale);
           cube->setPalette(pale);
           sphere->setPalette(pale);
           pale.setColor(QPalette::ButtonText,QColor(255,0,0));
           fiveImage->setPalette(pale);
}



void childWindow::changebackS(){
    QString filename=QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "Document files (*.jpg *.png);;All files(*.*)");

        if (filename.isNull()){
            QMessageBox::information(this, tr("提示"),tr("没有选中文件"));
            return;
        }

       // QByteArray b=filename.toLocal8Bit();
        c->setBackFlag=true;
       // c->backGroundFile=b.data();
        c->backGroundFile=filename;
        c->updateGL();

}

void childWindow::boxFlagS(){

    c->boxflag=-c->boxflag;
    c->updateGL();

}

void childWindow::planeFlagS(){
    c->planeflag=-c->planeflag;
    c->updateGL();

}
