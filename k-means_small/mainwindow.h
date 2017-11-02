#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QDebug>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,QColor a = QColor(0,0,0),QColor b = QColor(0,0,0),QColor c = QColor(0,0,0),QColor d = QColor(0,0,0));
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    QColor aa,ab,ac,ad;
};

#endif // MAINWINDOW_H
