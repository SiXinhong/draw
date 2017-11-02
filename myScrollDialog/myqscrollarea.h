#ifndef MYQSCROLLAREA_H
#define MYQSCROLLAREA_H
#include <QScrollArea>
#include<drawWidget/drawwidget.h>

class DrawWidget;
class myQScrollArea : public QScrollArea
{
public:
    myQScrollArea();
    void resizeEvent(QResizeEvent *);
    void getDrawWidget(DrawWidget *);
private:
    DrawWidget *centralDraw;
    int preWidth;
    int preHeight;
};

#endif // MYQSCROLLAREA_H
