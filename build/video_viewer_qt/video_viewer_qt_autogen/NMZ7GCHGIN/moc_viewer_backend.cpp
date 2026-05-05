/****************************************************************************
** Meta object code from reading C++ file 'viewer_backend.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/video_viewer_qt/include/video_viewer_qt/viewer_backend.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer_backend.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewerBackend_t {
    const uint offsetsAndSize[32];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ViewerBackend_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ViewerBackend_t qt_meta_stringdata_ViewerBackend = {
    {
QT_MOC_LITERAL(0, 13), // "ViewerBackend"
QT_MOC_LITERAL(14, 12), // "stateChanged"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 12), // "frameUpdated"
QT_MOC_LITERAL(41, 18), // "requestMqttConnect"
QT_MOC_LITERAL(60, 8), // "clientId"
QT_MOC_LITERAL(69, 21), // "requestMqttDisconnect"
QT_MOC_LITERAL(91, 10), // "statusText"
QT_MOC_LITERAL(102, 6), // "source"
QT_MOC_LITERAL(109, 10), // "frameWidth"
QT_MOC_LITERAL(120, 11), // "frameHeight"
QT_MOC_LITERAL(132, 3), // "fps"
QT_MOC_LITERAL(136, 15), // "loginStatusText"
QT_MOC_LITERAL(152, 12), // "loginPending"
QT_MOC_LITERAL(165, 8), // "hasFrame"
QT_MOC_LITERAL(174, 13) // "frameRevision"

    },
    "ViewerBackend\0stateChanged\0\0frameUpdated\0"
    "requestMqttConnect\0clientId\0"
    "requestMqttDisconnect\0statusText\0"
    "source\0frameWidth\0frameHeight\0fps\0"
    "loginStatusText\0loginPending\0hasFrame\0"
    "frameRevision"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewerBackend[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       9,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,   10 /* Public */,
       3,    0,   39,    2, 0x06,   11 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   40,    2, 0x02,   12 /* Public */,
       6,    0,   43,    2, 0x02,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00015001, uint(0), 0,
       8, QMetaType::QString, 0x00015001, uint(0), 0,
       9, QMetaType::Int, 0x00015001, uint(0), 0,
      10, QMetaType::Int, 0x00015001, uint(0), 0,
      11, QMetaType::Double, 0x00015001, uint(0), 0,
      12, QMetaType::QString, 0x00015001, uint(0), 0,
      13, QMetaType::Bool, 0x00015001, uint(0), 0,
      14, QMetaType::Bool, 0x00015001, uint(1), 0,
      15, QMetaType::ULongLong, 0x00015001, uint(1), 0,

       0        // eod
};

void ViewerBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewerBackend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->frameUpdated(); break;
        case 2: _t->requestMqttConnect((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->requestMqttDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewerBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewerBackend::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ViewerBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewerBackend::frameUpdated)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ViewerBackend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->statusText(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->source(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->frameWidth(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->frameHeight(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->fps(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->loginStatusText(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->loginPending(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->hasFrame(); break;
        case 8: *reinterpret_cast< quint64*>(_v) = _t->frameRevision(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ViewerBackend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ViewerBackend.offsetsAndSize,
    qt_meta_data_ViewerBackend,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ViewerBackend_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<double, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<quint64, std::true_type>, QtPrivate::TypeAndForceComplete<ViewerBackend, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *ViewerBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewerBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewerBackend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ViewerBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ViewerBackend::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ViewerBackend::frameUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
