#ifndef FIVEVIEW_H
#define FIVEVIEW_H

#include <QWidget>
#include<model/first_opengl.h>
#include<model/glm.h>
#include <QtOpenGL>
#include <QtGui>

class fiveView : public QGLWidget
{
    Q_OBJECT
public:
    explicit fiveView(QWidget *parent = 0);
    int texflag;
    char* modfile;
    char * texfile;
     GLMmodel *model;
     void loadFiveView();

     void drawFivePlane();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void setTex(  int k);
    GLfloat k;
    GLfloat dimensions[3];



    //void fivemodel();

private:

     GLuint model_texture;
     first_opengl *w;



signals:

public slots:

};

#endif // FIVEVIEW_H
