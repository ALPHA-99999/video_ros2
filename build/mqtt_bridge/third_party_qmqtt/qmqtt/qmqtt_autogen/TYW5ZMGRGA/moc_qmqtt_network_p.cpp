/****************************************************************************
** Meta object code from reading C++ file 'qmqtt_network_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../src/third_party_qmqtt/qmqtt/src/mqtt/qmqtt_network_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmqtt_network_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMQTT__Network_t {
    const uint offsetsAndSize[30];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QMQTT__Network_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QMQTT__Network_t qt_meta_stringdata_QMQTT__Network = {
    {
QT_MOC_LITERAL(0, 14), // "QMQTT::Network"
QT_MOC_LITERAL(15, 13), // "connectToHost"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 12), // "QHostAddress"
QT_MOC_LITERAL(43, 4), // "host"
QT_MOC_LITERAL(48, 4), // "port"
QT_MOC_LITERAL(53, 8), // "hostName"
QT_MOC_LITERAL(62, 18), // "disconnectFromHost"
QT_MOC_LITERAL(81, 15), // "ignoreSslErrors"
QT_MOC_LITERAL(97, 13), // "onSocketError"
QT_MOC_LITERAL(111, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(140, 11), // "socketError"
QT_MOC_LITERAL(152, 17), // "onSocketReadReady"
QT_MOC_LITERAL(170, 11), // "onConnected"
QT_MOC_LITERAL(182, 14) // "onDisconnected"

    },
    "QMQTT::Network\0connectToHost\0\0"
    "QHostAddress\0host\0port\0hostName\0"
    "disconnectFromHost\0ignoreSslErrors\0"
    "onSocketError\0QAbstractSocket::SocketError\0"
    "socketError\0onSocketReadReady\0onConnected\0"
    "onDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMQTT__Network[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   68,    2, 0x0a,    1 /* Public */,
       1,    2,   73,    2, 0x0a,    4 /* Public */,
       7,    0,   78,    2, 0x0a,    7 /* Public */,
       8,    0,   79,    2, 0x0a,    8 /* Public */,
       9,    1,   80,    2, 0x09,    9 /* Protected */,
      12,    0,   83,    2, 0x09,   11 /* Protected */,
      13,    0,   84,    2, 0x09,   12 /* Protected */,
      14,    0,   85,    2, 0x09,   13 /* Protected */,
       1,    0,   86,    2, 0x09,   14 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UShort,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    6,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QMQTT::Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Network *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectToHost((*reinterpret_cast< std::add_pointer_t<QHostAddress>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2]))); break;
        case 1: _t->connectToHost((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<quint16>>(_a[2]))); break;
        case 2: _t->disconnectFromHost(); break;
        case 3: _t->ignoreSslErrors(); break;
        case 4: _t->onSocketError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 5: _t->onSocketReadReady(); break;
        case 6: _t->onConnected(); break;
        case 7: _t->onDisconnected(); break;
        case 8: _t->connectToHost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject QMQTT::Network::staticMetaObject = { {
    QMetaObject::SuperData::link<NetworkInterface::staticMetaObject>(),
    qt_meta_stringdata_QMQTT__Network.offsetsAndSize,
    qt_meta_data_QMQTT__Network,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QMQTT__Network_t
, QtPrivate::TypeAndForceComplete<Network, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QHostAddress &, std::false_type>, QtPrivate::TypeAndForceComplete<const quint16, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const quint16, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QMQTT::Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMQTT::Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMQTT__Network.stringdata0))
        return static_cast<void*>(this);
    return NetworkInterface::qt_metacast(_clname);
}

int QMQTT::Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NetworkInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
