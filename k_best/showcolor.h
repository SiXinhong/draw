#ifndef SHOWCOLOR_H
#define SHOWCOLOR_H

#include <QMainWindow>
#include<QPainter>
#include<QDebug>


namespace Ui {
    class showColor;
}

class showColor : public QMainWindow
{
    Q_OBJECT

public:
    explicit showColor(QWidget *parent = 0,QColor a = QColor(0,0,0),QColor b = QColor(0,0,0),QColor c = QColor(0,0,0));
    ~showColor();

private:
    Ui::showColor *ui;
    void paintEvent(QPaintEvent *);
    QColor aa,ab,ac;
};


#endif // MAINWINDOW_H
