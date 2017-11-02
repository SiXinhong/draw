/****************************************************************************
** Meta object code from reading C++ file 'wumainwin.h'
**
** Created: Thu Oct 26 10:35:34 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../window/wumainwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wumainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_wumainWin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      19,   10,   10,   10, 0x08,
      30,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_wumainWin[] = {
    "wumainWin\0\0openS()\0savePicS()\0"
    "changBackS()\0"
};

const QMetaObject wumainWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_wumainWin,
      qt_meta_data_wumainWin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &wumainWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *wumainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *wumainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wumainWin))
        return static_cast<void*>(const_cast< wumainWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int wumainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openS(); break;
        case 1: savePicS(); break;
        case 2: changBackS(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
