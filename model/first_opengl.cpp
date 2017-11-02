#include "first_opengl.h"
//#include <QtOpenGL>
//#include <QtGui>
#include "model/fiveview.h"
#include<QString>




first_opengl::first_opengl(QWidget *parent) :
    QGLWidget(parent)
{
    m_xTranslation = 0.0f;
    m_yTranslation = 0.0f;
    m_zTranslation = -3.0f;
    m_xScaling = 1.0f;
    m_yScaling = 1.0f;
    m_zScaling = 1.0f;
    m_ClearColorRed=255.0f;
    m_ClearColorGreen=255.0f;
    m_ClearColorBlue=255.0f;
    m_xRotation=0;
    m_yRotation=0;
    Bbox[0] = -1.0;Bbox[1] = 1.0;Bbox[2] = -1.0;
    Bbox[3] = 1.0;Bbox[4] = -0.25; Bbox[5] = 0.41;

    textureFile="image/1.png";
    textureFlag=1;
    setBackFlag=false;
    //backGroundFile=NULL;
    boxflag=1;
    planeflag=1;


}

// 初始化环境
void first_opengl::initializeGL()
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);//设置着色模式。 参数mode可以是GL_SMOOTH（默认值）或GL_FLAT。
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

}


// 调整视口大小
void first_opengl::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);//视口被设置为占据打开窗口的整个像素矩形，参数一二为x，y指定视口左上角位置，后面是widget和height
    glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
   // glMatrixMode(GL_MODELVIEW);//对模型视景矩阵堆栈应用随后的矩阵操作
   // glLoadIdentity();

}

// 渲染场景
void first_opengl::paintGL()
{
   //清除背景色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色以及深度缓存
    glClearColor(m_ClearColorRed,m_ClearColorGreen,m_ClearColorBlue,1.0f);//利用前3个参数设置背景色了

    if(setBackFlag==true)
       {
           QByteArray arr=backGroundFile.toLocal8Bit();
           qDebug("%s",arr.data());
           setbackImage(arr.data());
           //setbackImage("..//draw//1.bmp");
           qDebug("set beijing");
       }

    load_OBJ();

    if(planeflag==1)
    drawFivePlane1();
    if(boxflag==1)
    drawBbox();


}





void first_opengl::load_OBJ(){

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();//压入堆栈矩阵
    glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵

    // scale / translation / rotation

    glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心
    glScalef(m_xScaling,m_yScaling,m_zScaling);//模型变换函数 缩放
    glTranslatef(m_xTranslation,m_yTranslation,m_zTranslation);//模型变换函数 移动
    glRotatef(m_xRotation,1.0f,0.0f,0.0f);//转动，参数一是角度，后面是向量坐标
    glRotatef(m_yRotation,0.0f,1.0f,0.0f);

    //model=glmReadOBJ(modelFile);

     //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmUnitize(model,2.0f);
    glmFacetNormals(model);////计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model, 90);////计算模型的平滑顶点法向

    glRotatef(-90,1,0,0);

    if (model!=NULL)
    {

        glDisable(GL_COLOR_MATERIAL);//关闭当前材料的颜色唯一性（可有可无）
        glEnable(GL_TEXTURE_2D);//启用纹理映射功能

        //model_texture=bindTexture(QPixmap("image/3.png"),GL_TEXTURE_2D);//把图片绑定到model_texture
        model_texture=bindTexture(QPixmap("image/1.png"),GL_TEXTURE_2D);
        //model_texture2=bindTexture(QPixmap("image/8.png"),GL_TEXTURE_2D);//把图片绑定到model_texture
        glBindTexture(GL_TEXTURE_2D,model_texture);//纹理绑定
        //glBindTexture(GL_TEXTURE_2D,model_texture2);//纹理绑定

        setTexWay(textureFlag);

        glPushMatrix();

        glmUnitize(model,2.0f);


        glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);


    }

    glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作.
    glLoadIdentity();
    gluPerspective(60.0, 1.0f, 1.0f, 128.0);//gluPerspective这个函数指定了观察的视景体，参数一是角度，参数二是视景体的宽高比，参数三、四分别是沿z轴方向的两裁面之间的距离的近处，远处

    glPopMatrix();//出栈
}

//----------------xiaotian  原来的代码
/*
void first_opengl::load_OBJ(){

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();//压入堆栈矩阵
    glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵

    // scale / translation / rotation

    glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心
    glScalef(m_xScaling,m_yScaling,m_zScaling);//模型变换函数 缩放
    glTranslatef(m_xTranslation,m_yTranslation,m_zTranslation);//模型变换函数 移动
    glRotatef(m_xRotation,1.0f,0.0f,0.0f);//转动，参数一是角度，后面是向量坐标
    glRotatef(m_yRotation,0.0f,1.0f,0.0f);

    //model=glmReadOBJ(modelFile);

     //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmUnitize(model,2.0f);
    glmFacetNormals(model);////计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model, 90);////计算模型的平滑顶点法向

    glRotatef(-90,1,0,0);

    if (model!=NULL)
    {

        glDisable(GL_COLOR_MATERIAL);//关闭当前材料的颜色唯一性（可有可无）
        glEnable(GL_TEXTURE_2D);//启用纹理映射功能

        model_texture=bindTexture(QPixmap("image/13.png"),GL_TEXTURE_2D);//把图片绑定到model_texture
        glBindTexture(GL_TEXTURE_2D,model_texture);//纹理绑定


        setTexWay(textureFlag);

        glPushMatrix();

        glmUnitize(model,2.0f);

        glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);


    }

    glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作.
    glLoadIdentity();
    gluPerspective(60.0, 1.0f, 1.0f, 128.0);//gluPerspective这个函数指定了观察的视景体，参数一是角度，参数二是视景体的宽高比，参数三、四分别是沿z轴方向的两裁面之间的距离的近处，远处

    glPopMatrix();//出栈
}
*/



void first_opengl::mousePressEvent(QMouseEvent *event)

{
    lastPos = event->pos();
}

//void first_opengl::mouseMoveEvent(QMouseEvent *event)
//{
//    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
//    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

//   if (event->buttons() & Qt::LeftButton) {
//       m_xRotation += 180 * dy;
//        m_yRotation += 180 * dx;
//        updateGL();
//    } else if (event->buttons() & Qt::RightButton) {
//        m_xRotation += 180 * dy;
//        m_zRotation += 180 * dx;
//        updateGL();
//    }

//    lastPos = event->pos();
//}


void first_opengl::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

   if (event->buttons() & Qt::LeftButton) {
        m_xRotation += 180 * dy;
        m_yRotation += 180 * dx;
        updateGL();
    }
   else
       if (event->buttons() & Qt::RightButton) {
//        m_xRotation += 180 * dy;
//        m_zRotation += 180 * dx;
//        updateGL();

         //平移
           m_xTranslation+=10*dx;
           m_yTranslation-=10*dy;
           updateGL();

    }

    lastPos = event->pos();
}


void first_opengl::drawBbox()
{
        //makeCurrent();
        // vertex in back face
    glmDimensions(model,dimensions);


    Bbox[0] = -(dimensions[0]*0.5);Bbox[1] = dimensions[0]*0.5;Bbox[2] = -(dimensions[1]*0.5);
    Bbox[3] = dimensions[1]*0.5;Bbox[4] = -(dimensions[2]*0.5); Bbox[5] = (dimensions[2]*0.5);

        float v1[3]={Bbox[0],Bbox[2],Bbox[4]};
        float v2[3]={Bbox[0],Bbox[2],Bbox[5]};
        float v3[3]={Bbox[0],Bbox[3],Bbox[5]};
        float v4[3]={Bbox[0],Bbox[3],Bbox[4]};
        // vertex in front face
        float v5[3]={Bbox[1],Bbox[2],Bbox[4]};
        float v6[3]={Bbox[1],Bbox[2],Bbox[5]};
        float v7[3]={Bbox[1],Bbox[3],Bbox[5]};
        float v8[3]={Bbox[1],Bbox[3],Bbox[4]};

        /////////////
        glDisable(GL_LIGHTING);

        glPushAttrib(GL_ALL_ATTRIB_BITS);//全部属性（GL_ALL_ATTRIBUTE_BITS)通过函数glPushAttrib压入属性堆栈中
        glColor3f(0, 0, 0);

        // edges in front face
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v5);
        glVertex3fv(v6);
        glVertex3fv(v7);
        glVertex3fv(v8);
        glEnd();

        // edges in back face
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v1);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glVertex3fv(v4);
        glEnd();

        // edges between back and front face
        glBegin(GL_LINES);
        glVertex3fv(v1);
        glVertex3fv(v5);
        glVertex3fv(v6);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glVertex3fv(v7);
        glVertex3fv(v4);
        glVertex3fv(v8);
        glEnd();

        glPopAttrib();
}




void first_opengl::drawFivePlane1(){

    float x=-1.5;
    float y=-1;
    glmDimensions(model,dimensions);
    float z=-(dimensions[2]*0.5);
    //float z=-(dimensions[2]*0.5);
   // int move = ((int)length + 1)*2;
    float move = 3 ;
    int num= 14;
    //float dis=length/num;

    glDisable(GL_LIGHTING);

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    for(int i=0;i<=num+1;++i)
    {
        glVertex3f(x,y,z);
        glVertex3f(x,y+move-1,z);
        x+=0.2;
    }
    glEnd();
    x=-1.5;
    glBegin(GL_LINES);
    for(int i=0;i<=num-4;++i)
    {
        glVertex3f(x,y,z);
        glVertex3f(x+move,y,z);
        y+=0.2;
    }
    glEnd();
    glColor3f(1.0,1.0,1.0);

   // glScalef(2,2,2);

}

void first_opengl::setTexWay(int textureFlag){

    switch (textureFlag){

    case 0:
        glDisable(GL_TEXTURE_2D);
      //  glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );//参数二很重要,纹理方式绘图
        break;
    case 1:
        glmXYTexture(model,1);
        glEnable(GL_TEXTURE_2D);
      //  glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    case 2:
        glmXYTexture(model,2);
        glEnable(GL_TEXTURE_2D);
      //  glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    case 3:
        glmXYTexture(model,3);
        glEnable(GL_TEXTURE_2D);
       // glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    case 4:
        glmLinearTexture(model);
        glEnable(GL_TEXTURE_2D);
      //  glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    case 5:
        glmCubicmapTexture(model);
        glEnable(GL_TEXTURE_2D);
       // glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    case 6:
        glmSpheremapTexture(model);
        glEnable(GL_TEXTURE_2D);
       // glmDraw(model, GLM_SMOOTH |GLM_TEXTURE );
        break;

    default:
        break;


    }


}


void first_opengl::wheelEvent(QWheelEvent *event){

    if(event->delta()>0)
       {
        m_zTranslation+=-0.5;
        updateGL();
       }
    if(event->delta()<0)
       {

        m_zTranslation+=0.5;
        updateGL();
       }

}


void first_opengl::setbackImage(char* file){

     makeCurrent();
     glDisable(GL_BLEND);
     glPushAttrib(GL_ALL_ATTRIB_BITS);
     glDisable(GL_BLEND);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(-10.0,10.0,-10.0,10.0,-10.0,10.0);

     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();

     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_GEQUAL);
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);

     glNormal3f(0.0,0.0,1.0);



     GLuint texture=bindTexture(QPixmap(file),GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D,texture);

     glBegin(GL_POLYGON);
     glTexCoord2f(0.0,0.0);
     glVertex3f(-10.0,-10.0,-10.0);
     glTexCoord2f(1.0,0.0);
     glVertex3f(10.0,-10.0,-10.0);
     glTexCoord2f(1.0,1.0);
     glVertex3f(10.0,10.0,-10.0);
     glTexCoord2f(0.0,1.0);
     glVertex3f(-10.0,10.0,-10.0);
     glEnd();
     glDisable(GL_TEXTURE_2D);


     glMatrixMode(GL_MODELVIEW);
     glPopMatrix();
     glMatrixMode(GL_PROJECTION);
     glPopMatrix();
     glPopAttrib();


}



