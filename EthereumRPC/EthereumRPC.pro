#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T15:09:12
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = EthRPC
TEMPLATE = lib

DEFINES += ETHRPC_LIBRARY

SOURCES += \
    ethobject.cpp \
    ethrpc.cpp \
    ethlocalclient.cpp \
    jsoncoder.cpp

HEADERS +=\
    ethobject.h \
    iethclient.h \
    ethrpc_global.h \
    ethrpc.h \
    ethrpc_utils.h \
    ethlocalclient.h \
    jsoncoder.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
