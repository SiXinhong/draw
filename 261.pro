#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T21:58:47
#
#-------------------------------------------------
QT       +=opengl\
           core gui opengl


TARGET = draw
TEMPLATE = app


SOURCES +=   caculate/getpoint.cpp \
    caculate/getcurvature.cpp \
    myScrollDialog/myqscrollarea.cpp \
    myScrollDialog/mydialog.cpp \
    qtPropertyBrowser/qtvariantproperty.cpp \
    qtPropertyBrowser/qttreepropertybrowser.cpp \
    qtPropertyBrowser/qtpropertymanager.cpp \
    qtPropertyBrowser/qtpropertybrowserutils.cpp \
    qtPropertyBrowser/qtpropertybrowser.cpp \
    qtPropertyBrowser/qtgroupboxpropertybrowser.cpp \
    qtPropertyBrowser/qteditorfactory.cpp \
    qtPropertyBrowser/qtbuttonpropertybrowser.cpp \
    window/mainWindow.cpp \
    window/main.cpp \
    window/mythread.cpp \
    window/controlthread.cpp \
    caculate/savespot.cpp \
    caculate/colorm.cpp \
    window/childwindow.cpp \
    model/glm.cpp \
    model/fiveview.cpp \
    model/first_opengl.cpp \
    window/wumainwin.cpp \
    model/wumian.cpp \
    drawWidget/spot.cpp \
    drawWidget/drawWidget.cpp \
    drawWidget/digitalwidget.cpp \
    caculate/caculate.cpp \
    caculate/CIEDE2000.cpp \
    caculate/RGB2LAB.cpp

HEADERS  += caculate/getpoint.h \
    caculate/getcurvature.h \
    caculate/colorm.h \
    drawWidget/drawwidget.h \
    myScrollDialog/myqscrollarea.h \
    myScrollDialog/mydialog.h \
    qtPropertyBrowser/qtvariantproperty.h \
    qtPropertyBrowser/qttreepropertybrowser.h \
    qtPropertyBrowser/qtpropertymanager.h \
    qtPropertyBrowser/qtpropertybrowserutils_p.h \
    qtPropertyBrowser/qtpropertybrowser.h \
    qtPropertyBrowser/qtgroupboxpropertybrowser.h \
    qtPropertyBrowser/qteditorfactory.h \
    qtPropertyBrowser/qtbuttonpropertybrowser.h \
    window/spotColorAll.h \
    window/mainwindow.h \
    window/mythread.h \
    window/controlthread.h \
    caculate/savespot.h \
    window/childwindow.h \
    model/glm.h \
    model/fiveview.h \
    model/first_opengl.h \
    window/wumainwin.h \
    model/wumian.h \
    drawWidget/spot.h \
    drawWidget/digitalwidget.h \
    caculate/caculate.h \
    caculate/CIEDE2000.h \
    caculate/RGB2LAB.h


FORMS    += mainwindow.ui \
    mydialog.ui \
    childwindow.ui \
    wumainwin.ui
RC_FILE=icon/myapp.rc

INCLUDEPATH+=D:\Qt\QTsource\OpenCV\include\opencv\

             INCLUDEPATH+=D:\Qt\QTsource\OpenCV\include\opencv2\

             INCLUDEPATH+=D:\Qt\QTsource\OpenCV\include

LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_calib3d231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_contrib231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_core231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_features2d231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_flann231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_gpu231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_highgui231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_imgproc231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_legacy231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_ml231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_objdetect231.dll.a\

        LIBS+=D:\Qt\QTsource\OpenCV\lib\libopencv_ts231.a\

CONFIG += consol
