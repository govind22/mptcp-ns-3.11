/****************************************************************************
** Meta object code from reading C++ file 'AnimView.h'
**
** Created: Wed Jan 14 10:48:05 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AnimView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnimView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnimView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AnimView[] = {
    "AnimView\0\0TimeToUpdate()\0"
};

const QMetaObject AnimView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnimView,
      qt_meta_data_AnimView, 0 }
};

const QMetaObject *AnimView::metaObject() const
{
    return &staticMetaObject;
}

void *AnimView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnimView))
	return static_cast<void*>(const_cast< AnimView*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnimView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: TimeToUpdate(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
