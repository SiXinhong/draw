#include "model/fiveView.h"
#include"model/first_opengl.h"



fiveView::fiveView(QWidget *parent):
   QGLWidget(parent)

{


  texflag=0;
  texfile="image/3.png";
  k=2.0;

}

// ��ʼ������
void fiveView::initializeGL()
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH);//������ɫģʽ�� ����mode������GL_SMOOTH��Ĭ��ֵ����GL_FLAT��
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);


}


// �����ӿڴ�С
void fiveView::resizeGL(int w, int h)
{///////////

    glViewport(0, 0, (GLint)w, (GLint)h);//�ӿڱ�����Ϊռ�ݴ򿪴��ڵ��������ؾ��Σ�����һ��Ϊx��yָ���ӿ����Ͻ�λ�ã�������widget��height
    glMatrixMode(GL_PROJECTION);//��ͶӰ����Ӧ�����ľ������
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    //glMatrixMode(GL_MODELVIEW);//��ģ���Ӿ������ջӦ�����ľ������
    //glLoadIdentity();

}

// ��Ⱦ����
void fiveView::paintGL()
{
   //�������ɫ
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�Լ���Ȼ���
    glClearColor(255.0,22.0,22.0,1.0f);//����ǰ3���������ñ���ɫ��
     //drawFivePlane();
    loadFiveView();

    //glScalef(0.3,0.5,0.5);

   // drawFivePlane();




}

void fiveView::loadFiveView(){


    ///////
    //����ģ����ʾ����
    glmDimensions(model,dimensions);
    GLfloat my_scal=2.0f/max(max(dimensions[0], dimensions[1]), dimensions[2]);

    if(dimensions[1]*my_scal+dimensions[2]*my_scal*2>3.8)
        k=1.3f;
    else
        k=2.0f;
//    GLfloat ambientLight[]={50.0,50.0,10.0,0.0};
//    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE,ambientLight);


    glEnable(GL_COLOR_MATERIAL);

   // glPushMatrix();//ѹ���ջ����
    glMatrixMode(GL_MODELVIEW);
  //  drawFivePlane();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLoadIdentity();  //����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
    glTranslatef(0,0,-5);//ģ�ͱ任���� �ƶ�

   // glScalef(1.0,1.5,1.0);

    model_texture=bindTexture(QPixmap("image/3.png"),GL_TEXTURE_2D);//��ͼƬ�󶨵�model_texture
    glBindTexture(GL_TEXTURE_2D,model_texture);//�����
    glmFacetNormals(model);////����ģ����ķ��򣨼ٶ�����ζ���˳��Ϊ��ʱ�룩
    glmVertexNormals(model, 90);

    /////////////
    setTex(texflag);

     //�м���ͼ
    glDisable(GL_COLOR_MATERIAL);
    glPushMatrix();//ѹ���ջ����
   // glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
    glRotatef(180,0.0,0.0,1.0);
    glmUnitize(model,k); //��λ��ģ��model���������ű�������,��λ�����ǰ�ģ��ͨ��ƽ�ƺ����ű任���Ƶ�3ά����ϵ�е�Ϊ���ĵ�һ����λ������������
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //ǰ��ͼ
    glPushMatrix();
   // glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
    glTranslatef(0.0,-(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(100,0.1,0.0,0.0);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //��λ��ģ��model���������ű�������,��λ�����ǰ�ģ��ͨ��ƽ�ƺ����ű任���Ƶ�3ά����ϵ�е�Ϊ���ĵ�һ����λ������������

    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


    //����ͼ
    glPushMatrix();
   // glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
    glTranslatef(0.0,(dimensions[1]*0.5+dimensions[2]*0.5+0.2),0.0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(-100,1.0,0.0,0.0);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //��λ��ģ��model���������ű�������,��λ�����ǰ�ģ��ͨ��ƽ�ƺ����ű任���Ƶ�3ά����ϵ�е�Ϊ���ĵ�һ����λ������������
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


    //����ͼ
    glPushMatrix();
  //  glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
     glTranslatef(-(dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
    glRotatef(180,0.0,0.0,1.0);
    glRotatef(-110,0.0,1.0,0.0);
    glScalef(0.6,1,1);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //��λ��ģ��model���������ű�������,��λ�����ǰ�ģ��ͨ��ƽ�ƺ����ű任���Ƶ�3ά����ϵ�е�Ϊ���ĵ�һ����λ������������
    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();


   //����ͼ

    glPushMatrix();
  //  glMatrixMode(GL_MODELVIEW);//ָ�������ǵ�ǰ����
     glTranslatef((dimensions[0]*0.5+dimensions[2]*0.5+0.4),0,0);
    glRotatef(70,0.0,1.0,0.0);
    glRotatef(180,1.0,0.0,0.0);
    glScalef(0.6,1,1);
    //model=glmReadOBJ("E://micai//Files//sample.OBJ");
    glmUnitize(model,k); //��λ��ģ��model���������ű�������,��λ�����ǰ�ģ��ͨ��ƽ�ƺ����ű任���Ƶ�3ά����ϵ�е�Ϊ���ĵ�һ����λ������������

    glmDraw(model, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //////////////////
  //  glMatrixMode(GL_PROJECTION);//��ͶӰ����Ӧ�����ľ������.ע�͵��Ͳ�����������
  //  glLoadIdentity();//����ȥ��
    //////////

    gluPerspective(60.0, 1.0f, 1.0f, 128.0);//gluPerspective�������ָ���˹۲���Ӿ��壬����һ�ǽǶȣ����������Ӿ���Ŀ�߱ȣ����������ķֱ�����z�᷽���������֮��ľ���Ľ�����Զ��

    drawFivePlane();   //������ͼ����ķ����
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


