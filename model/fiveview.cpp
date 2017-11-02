#include "model/fiveView.h"
#include"model/first_opengl.h"



fiveView::fiveView(QWidget *parent):
   QGLWidget(parent)

{


  texflag=0;
  texfile="image/3.png";
  k=2.0;

}

// 初始化环境
void fiveView::initializeGL()
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);//设置着色模式。 参数mode可以是GL_SMOOTH（默认值）或GL_FLAT。
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);


}


// 调整视口大小
void fiveView::resizeGL(int w, int h)
{///////////

    glViewport(0, 0, (GLint)w, (GLint)h);//视口被设置为占据打开窗口的整个像素矩形，参数一二为x，y指定视口左上角位置，后面是widget和height
    glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    //glMatrixMode(GL_MODELVIEW);//对模型视景矩阵堆栈应用随后的矩阵操作
    //glLoadIdentity();

}

// 渲染场景
void fiveView::paintGL()
{
   //清除背景色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色以及深度缓存
    glClearColor(255.0,22.0,22.0,1.0f);//利用前3个参数设置背景色了
     //drawFivePlane();
    loadFiveView();

    //glScalef(0.3,0.5,0.5);

   // drawFivePlane();




}

void fiveView::loadFiveView(){


    ///////
    //处理模型显示比例
    glmDimensions(model,dimensions);
    GLfloat my_scal=2.0f/max(max(dimensions[0], dimensions[1]), dimensions[2]);

    if(dimensions[1]*my_scal+dimensions[2]*my_scal*2>3.8)
        k=1.3f;
    else
        k=2.0f;
//    GLfloat ambientLight[]={50.0,50.0,10.0,0.0};
//    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE,ambientLight);


    glEnable(GL_COLOR_MATERIAL);

   // glPushMatrix();//压入堆栈矩阵
    glMatrixMode(GL_MODELVIEW);
  //  drawFivePlane();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLoadIdentity();  //将当前的用户坐标系的原点移到了屏幕中心
    glTranslatef(0,0,-5);//模型变换函数 移动

   // glScalef(1.0,1.5,1.0);

    model_texture=bindTexture(QPixmap("image/3.png"),GL_TEXTURE_2D);//把图片绑定到model_texture
    glBindTexture(GL_TEXTURE_2D,model_texture);//纹理绑定
    glmFacetNormals(model);////计算模型面的法向（假定多边形顶点顺序为逆时针）
    glmVertexNormals(model, 90);

    /////////////
    setTex(texflag);

     //中间视图
    glDisable(GL_COLOR_MATERIAL);
    glPushMatrix();//压入堆栈矩阵
   // glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵
    glRotatef(180,0.0,0.0,1.0);
    glmUnitize(model,k); //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //前视图
    glPushMatrix();
   // glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵
    glTranslatef(0.0,-(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(100,0.1,0.0,0.0);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内

    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


    //后视图
    glPushMatrix();
   // glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵
    glTranslatef(0.0,(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(-100,1.0,0.0,0.0);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


    //左视图
    glPushMatrix();
  //  glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵
     glTranslatef(-(dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(-110,0.0,1.0,0.0);
    glScalef(0.6,1,1);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


   //右视图

    glPushMatrix();
  //  glMatrixMode(GL_MODELVIEW);//指定参数是当前矩阵
     glTranslatef((dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
    glRotatef(70,0.0,1.0,0.0);
    glRotatef(180,1.0,0.0,0.0);
    glScalef(0.6,1,1);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //单位化模型model并返回缩放比例因子,单位化就是把模型通过平移和缩放变换限制到3维坐标系中点为中心的一个单位正方体区域内

    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //////////////////
  //  glMatrixMode(GL_PROJECTION);//对投影矩阵应用随后的矩阵操作.注释掉就不随胖随瘦了
  //  glLoadIdentity();//可以去掉
    //////////

    gluPerspective(60.0, 1.0f, 1.0f, 128.0);//gluPerspective这个函数指定了观察的视景体，参数一是角度，参数二是视景体的宽高比，参数三、四分别是沿z轴方向的两裁面之间的距离的近处，远处

    drawFivePlane();   //画五视图后面的方格板
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}


void fiveView::setTex( int k){

    switch(k){
    case 0:
        glDisable(GL_TEXTURE_2D);
        break;
    case 1:
        glmXYTexture(model,1);
        glEnable(GL_TEXTURE_2D);
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


void fiveView::drawFivePlane(){

    glScalef(0.3,0.3,0.5);

    float x=-2.5;
    float y=-2;
    float z=-0.5;


    if(k==2.0){
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINES);
        for(int i=0;i<=25;++i)
        {
            glVertex3f(x,y,z);
            glVertex3f(x,y+4,z);
            x+=0.2;
        }
        glEnd();
        x=-2.5;
        glBegin(GL_LINES);
        for(int i=0;i<=20;++i)
        {
            glVertex3f(x,y,z);
            glVertex3f(x+5,y,z);
            y+=0.2;

        }
        glEnd();
        glColor3f(1.0,1.0,1.0);
    }
    else
    {
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINES);
        for(int i=0;i<=39;++i)
        {
            glVertex3f(x,y,z);
            glVertex3f(x,y+4.02,z);
            x+=0.13;
        }
        glEnd();
        x=-2.5;
        glBegin(GL_LINES);
        for(int i=0;i<=31;++i)
        {
            glVertex3f(x,y,z);
            glVertex3f(x+5.05,y,z);
            y+=0.13;

        }
        glEnd();
        glColor3f(1.0,1.0,1.0);
    }


}


