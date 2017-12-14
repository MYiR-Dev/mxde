/****************************************************************************
** Meta object code from reading C++ file 'mxmaindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mxmaindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mxmaindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MxMainDialog_t {
    QByteArrayData data[10];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MxMainDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MxMainDialog_t qt_meta_stringdata_MxMainDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MxMainDialog"
QT_MOC_LITERAL(1, 13, 19), // "OnApplicationClosed"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "OnCurrentPageChanged"
QT_MOC_LITERAL(4, 55, 5), // "index"
QT_MOC_LITERAL(5, 61, 19), // "OnSystemInfoClicked"
QT_MOC_LITERAL(6, 81, 17), // "OnLanguageChanged"
QT_MOC_LITERAL(7, 99, 8), // "language"
QT_MOC_LITERAL(8, 108, 18), // "OnOpenAnimFinished"
QT_MOC_LITERAL(9, 127, 19) // "onCloseAnimFinished"

    },
    "MxMainDialog\0OnApplicationClosed\0\0"
    "OnCurrentPageChanged\0index\0"
    "OnSystemInfoClicked\0OnLanguageChanged\0"
    "language\0OnOpenAnimFinished\0"
    "onCloseAnimFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MxMainDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MxMainDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MxMainDialog *_t = static_cast<MxMainDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnApplicationClosed(); break;
        case 1: _t->OnCurrentPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnSystemInfoClicked(); break;
        case 3: _t->OnLanguageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnOpenAnimFinished(); break;
        case 5: _t->onCloseAnimFinished(); break;
        default: ;
        }
    }
}

const QMetaObject MxMainDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MxMainDialog.data,
      qt_meta_data_MxMainDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MxMainDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MxMainDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MxMainDialog.stringdata0))
        return static_cast<void*>(const_cast< MxMainDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int MxMainDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
