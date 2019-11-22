/****************************************************************************
** Meta object code from reading C++ file 'mtrWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mtrWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mtrWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mtrWidget_t {
    QByteArrayData data[10];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mtrWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mtrWidget_t qt_meta_stringdata_mtrWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "mtrWidget"
QT_MOC_LITERAL(1, 10, 22), // "on_btn_OpenTp5_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_btn_startMod_clicked"
QT_MOC_LITERAL(4, 58, 22), // "on_btn_OpenTp7_clicked"
QT_MOC_LITERAL(5, 81, 24), // "on_btn_cRadiance_clicked"
QT_MOC_LITERAL(6, 106, 18), // "on_btn_clr_clicked"
QT_MOC_LITERAL(7, 125, 29), // "on_btn_cTransmittance_clicked"
QT_MOC_LITERAL(8, 155, 24), // "on_modtranThread_started"
QT_MOC_LITERAL(9, 180, 25) // "on_modtranThread_finished"

    },
    "mtrWidget\0on_btn_OpenTp5_clicked\0\0"
    "on_btn_startMod_clicked\0on_btn_OpenTp7_clicked\0"
    "on_btn_cRadiance_clicked\0on_btn_clr_clicked\0"
    "on_btn_cTransmittance_clicked\0"
    "on_modtranThread_started\0"
    "on_modtranThread_finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mtrWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mtrWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mtrWidget *_t = static_cast<mtrWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_OpenTp5_clicked(); break;
        case 1: _t->on_btn_startMod_clicked(); break;
        case 2: _t->on_btn_OpenTp7_clicked(); break;
        case 3: _t->on_btn_cRadiance_clicked(); break;
        case 4: _t->on_btn_clr_clicked(); break;
        case 5: _t->on_btn_cTransmittance_clicked(); break;
        case 6: _t->on_modtranThread_started(); break;
        case 7: _t->on_modtranThread_finished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject mtrWidget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mtrWidget.data,
      qt_meta_data_mtrWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mtrWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mtrWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mtrWidget.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int mtrWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
