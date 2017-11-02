/****************************************************************************
** Meta object code from reading C++ file 'childwindow.h'
**
** Created: Thu Oct 26 10:35:32 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../window/childwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'childwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_childWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   12,   12,   12, 0x08,
      48,   12,   12,   12, 0x08,
      56,   12,   12,   12, 0x08,
      64,   12,   12,   12, 0x08,
      72,   12,   12,   12, 0x08,
      83,   12,   12,   12, 0x08,
      93,   12,   12,   12, 0x08,
     105,   12,   12,   12, 0x08,
     118,   12,   12,   12, 0x08,
     129,   12,   12,   12, 0x08,
     143,   12,   12,   12, 0x08,
     156,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_childWindow[] = {
    "childWindow\0\0ChildWindowEvent()\0"
    "showFiveViewS()\0xyMap()\0yzMap()\0xzMap()\0"
    "linerMap()\0cubeMap()\0sphereMap()\0"
    "fiveImageS()\0openobjS()\0changebackS()\0"
    "planeFlagS()\0boxFlagS()\0"
};

const QMetaObject childWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_childWindow,
      qt_meta_data_childWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &childWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *childWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *childWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_childWindow))
        return static_cast<void*>(const_cast< childWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int childWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ChildWindowEvent(); break;
        case 1: showFiveViewS(); break;
        case 2: xyMap(); break;
        case 3: yzMap(); break;
        case 4: xzMap(); break;
        case 5: linerMap(); break;
        case 6: cubeMap(); break;
        case 7: sphereMap(); break;
        case 8: fiveImageS(); break;
        case 9: openobjS(); break;
        case 10: changebackS(); break;
        case 11: planeFlagS(); break;
        case 12: boxFlagS(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void childWindow::ChildWindowEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
