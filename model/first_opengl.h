#ifndef first_opengl_H
#define first_opengl_H

#include <QGLWidget>
#include<model/glm.h>
#include<QMouseEvent>
#include<string>
#include<QWheelEvent>

using namespace std;


class first_opengl : public QGLWidget
{
    Q_OBJECT
public:
    explicit first_opengl(QWidget *parent = 0);
    bool setBackFlag;
    //char* backGroundFile;
    QString backGroundFile;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    //void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *event);

    void setbackImage(char* file);
    //void loadTextures();
    // void set_model_texture(QString filename);
public:
    //void drawFivePlane();
    void drawFivePlane1();
    void drawBbox();
    //void drawblank();
    void setTexWay(int textureFlag);
   // void getStr(char *temp);

    int boxflag;
    int planeflag;
 void load_OBJ();
     GLMmodel *model;
     GLuint model_texture;
     GLuint model_texture2;

      //char *modelFile;
     char *textureFile;
     int textureFlag;

private:
    //GLfloat translate, xRot, yRot, zRot;
   // GLuint textures[3];
    float m_xScaling;
    float m_yScaling;
    float m_zScaling;
    float m_xTranslation;
    float m_yTranslation;
    float m_zTranslation;
    float m_ClearColorRed;
    float m_ClearColorGreen;
    float m_ClearColorBlue;
    float m_xRotation;
    float m_yRotation;
    float m_zRotation;


    QPoint lastPos;

   // GLuint textures[3];


    GLfloat dimensions[3];
    float Bbox[6];




signals:

public slots:

};

#endif // first_opengl_H
