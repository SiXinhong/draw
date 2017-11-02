#include "model/wumian.h"

wumian::wumian(QWidget *parent) :
    QGLWidget(parent)
{
    setBackFlag=false;
    backGroundFile=NULL;

}

void wumian::initializeGL(){
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    tex1=QString("image/3.png");
    tex2="image/4.png";
    tex3="image/1.png";
    tex4="image/5.png";
    tex5="image/2.png";



}

void wumian::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    //glMatrixMode(GL_MODELVIEW);//��ģ���Ӿ������ջӦ�����ľ������
    //glLoadIdentity();
}

void wumian::paintGL()
{
//    QPainter p(this);
//    p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
//    p.drawRect(100,100,200,200);
//    p.setPen(Qt::NoPen);

   //�������ɫ
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�Լ���Ȼ���
    glClearColor(255.0,255.0,255.0,1.0f);//����ǰ3��

//    if(setBackFlag==true)
//    {
//        setbackImage(backGroundFile);
//        qDebug("diao yong le setbackimage");
//    }


    glRasterPos3f(100,80,0);
    //CString str="test";
    QString str="test";
    glCallLists(str.length(),GL_UNSIGNED_BYTE,&str);

    //drawText("hello world");
    draw();
    drawFivePlane();


}

//void wumian::drawText(const char *str){
//    static int isFirstCall = 1;
//      static GLuint lists;

//      if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
//                           // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
//           isFirstCall = 0;

//           // ����MAX_CHAR����������ʾ�б���
//           lists = glGenLists(MAX_CHAR);

//           // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
//           wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
//       }
//       // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
//      for(; *str!='\0'; ++str)
//           glCallList(lists + *str);
//}

void wumian::draw( ){

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();//ѹ���ջ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  //����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
    glTranslatef(0,0,-5);//ģ�ͱ任���� �ƶ�


   // model=glmReadOBJ("e:/micai/Files/sample.obj");

    glmFacetNormals(model);////����ģ����ķ��򣨼ٶ�����ζ���˳��Ϊ��ʱ�룩
    glmVertexNormals(model, 90);

    //����ģ����ʾ����
    glmDimensions(model,dimensions);

    GLfloat my_scal=2.0f/max(max(dimensions[0], dimensions[1]), dimensions[2]);

    if(dimensions[1]*my_scal+dimensions[2]*my_scal*2>3.8)
        k=1.2f;
    else
        k=2.0f;

    glmUnitize(model,k);

    //center
    model_texture=bindTexture(QPixmap(tex1),GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glRotatef(180,0.0,0.0,1.0);
    glmUnitize(model,k);
    glmXYTexture(model,1);
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //fore
    model_texture=bindTexture(QPixmap(tex4),GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
    glTranslatef(0.0,-(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(90,0.1,0.0,0.0);
    glRotatef(180,0.0,0.0,1.0);
    glmUnitize(model,k);
    glmXYTexture(model,2);
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //behind
    QImage i1=QImage(tex3);
    i1=i1.mirrored(false,true);
    model_texture=bindTexture(i1,GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0,(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(-100,1.0,0.0,0.0);
    glRotatef(180,0.0,0.0,1.0);
    glmUnitize(model,k);
    glmXYTexture(model,2);
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //right
    QMatrix ma;
    ma.rotate(90.0);
    QImage i2=QImage(tex2);
    i2=i2.transformed(ma,Qt::FastTransformation);
    model_texture=bindTexture(i2,GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
     glTranslatef((dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
   // glRotatef(180,0.0,0.0,1.0);
    glRotatef(-115,0.0,1.0,0.0);

    glScalef(0.6,1,1);
    glmUnitize(model,k);
    glmXYTexture(model,3);
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //left
    QMatrix ma2;
    ma2.rotate(-90.0);
    QImage i3=QImage(tex5);
    i3=i3.transformed(ma2,Qt::FastTransformation);
    // i3=i3.mirrored(false,true);
    i3=i3.mirrored(true,false);
    model_texture=bindTexture(i3,GL_TEXTURE_2D);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
    glTranslatef(-(dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
    glRotatef(110,0.0,1.0,0.0);
   // glRotatef(180,1.0,0.0,0.0);

 //   glScalef(0.6,1,1);

    glmUnitize(model,k);
    glmXYTexture(model,3);
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

  //  gluPerspective(60.0, 1.0f, 1.0f, 128.0);

    /////////////////////////////
    glMatrixMode(GL_PROJECTION);//��ͶӰ����Ӧ�����ľ������.
    glLoadIdentity();
    gluPerspective(60.0, 1.0f, 1.0f, 128.0);//

    glPopMatrix();



}

void wumian::drawFivePlane(){
//    if(model)
//        glmDimensions(model,dimensions);//����ģ�͵Ŀ��ߣ���ߴ磬���������dimensions��ָ��3Ԫ��������
//    //glColor3f(0.5,0.5,0.5);
//    float length=std::max(dimensions[0],std::max(dimensions[1],dimensions[2]));
 //  glScalef(0.3,0.3,0.5);

    float x=-2.5;
    float y=-2;
    float z=-0.5;
   // int move = ((int)length + 1)*2;
//    float move = 5 ;
//    int num= 25;
    //float dis=length/num;

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

GLfloat wumian::max(GLfloat a, GLfloat b)
{
 if (b > a)
   return b;
 return a;
}

void wumian::setbackImage(char* file){

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

//wumian::~wumian(){
//    //deleteTexture(model_texture);
//    glmDelete(model);
//}
