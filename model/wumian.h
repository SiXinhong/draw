#ifndef WUMIAN_H
#define WUMIAN_H

#include <QGLWidget>
#include<model/glm.h>
#include<QPainter>
//#include<cstring>
//using namespace std;
//#define MAX_CHAR        128
class wumian : public QGLWidget
{
    Q_OBJECT
public:
    explicit wumian(QWidget *parent = 0);

    char* modelF;
     void draw();

      GLMmodel *model;
      bool setBackFlag;
      char * backGroundFile;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    //void drawText(const char* str);

private:
    QString tex1;
    char* tex2;
    char* tex3;
    char* tex4;
    char* tex5;
    GLfloat dimensions[3];
    GLfloat k;


    void drawFivePlane();
    GLfloat max(GLfloat a, GLfloat b);


    GLuint model_texture;



    void setbackImage(char* file);



signals:

public slots:

};

#endif // WUMIAN_H
