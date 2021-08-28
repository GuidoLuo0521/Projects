#-------------------------------------------------
#
# Project created by QtCreator 2021-08-08T01:14:56
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuidoCMS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        common/commonapi.cpp \
        common/ntpclient.cpp \
        common/singleton.cpp \
        common/staffinfo.cpp \
        database/cmsdatabase.cpp \
        database/cmsdatebasedef.cpp \
        delegate/datedelegate.cpp \
        delegate/readonlydelegate.cpp \
        delegate/comboboxdelegate.cpp \
        Form/logindialog.cpp \
        Form/mainwindow.cpp \
        Form/systemmanagerdialog.cpp\
        main.cpp

HEADERS += \
        common/commonapi.h \
        common/staffinfo.h \
        common/ntpclient.h \
        common/singleton.h \
        database/cmsdatabase.h \
        database/cmsdatebasedef.h \
        delegate/readonlydelegate.h \
        delegate/comboboxdelegate.h \
        delegate/controldelegate.h \
        delegate/datedelegate.h \
        Form/logindialog.h \
        Form/mainwindow.h \
        Form/systemmanagerdialog.h

FORMS += \
        Form/logindialog.ui \
        Form/mainwindow.ui \
        Form/systemmanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
