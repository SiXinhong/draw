/****************************************************************************
** Meta object code from reading C++ file 'drawwidget.h'
**
** Created: Thu Oct 26 10:35:23 2017
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../drawWidget/drawwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DrawWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      31,   11,   11,   11, 0x05,
      48,   11,   11,   11, 0x05,
      64,   11,   11,   11, 0x05,
      80,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DrawWidget[] = {
    "DrawWidget\0\0ChildWindowEvent()\0"
    "getShowStretch()\0getAllColor_s()\0"
    "releaseCtrl_S()\0spotSelected_S()\0"
    "QScrollAreaResize()\0ChildWindowEventSlot()\0"
};

const QMetaObject DrawWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DrawWidget,
      qt_meta_data_DrawWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DrawWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DrawWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DrawWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DrawWidget))
        return static_cast<void*>(const_cast< DrawWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DrawWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ChildWindowEvent(); break;
        case 1: getShowStretch(); break;
        case 2: getAllColor_s(); break;
        case 3: releaseCtrl_S(); break;
        case 4: spotSelected_S(); break;
        case 5: QScrollAreaResize(); break;
        case 6: ChildWindowEventSlot(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DrawWidget::ChildWindowEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DrawWidget::getShowStretch()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DrawWidget::getAllColor_s()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DrawWidget::releaseCtrl_S()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void DrawWidget::spotSelected_S()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
