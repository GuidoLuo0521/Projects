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
        controlext/standerdateedit.cpp \
        controlext/standerinputstructer.cpp \
        controlext/standerplaintextedit.cpp \
        database/cmsdatabase.cpp \
        database/cmsdatebasedef.cpp \
        delegate/datedelegate.cpp \
        delegate/readonlydelegate.cpp \
        delegate/comboboxdelegate.cpp \
        form/departmentinfodialog.cpp \
        form/staffinfodialog.cpp \
        form/logindialog.cpp \
        form/mainwindow.cpp \
        form/systemmanagerdialog.cpp\
        form/tableinfodialog.cpp \
        controlext/standerlineedit.cpp \
        controlext/standercombobox.cpp \
        main.cpp

HEADERS += \
        common/commonapi.h \
        common/controlinclude.h \
        common/staffinfo.h \
        common/ntpclient.h \
        common/singleton.h \
        controlext/controlext.h \
        controlext/standerdateedit.h \
        controlext/standerinputstructer.h \
        controlext/standerplaintextedit.h \
        database/cmsdatabase.h \
        database/cmsdatebasedef.h \
        delegate/readonlydelegate.h \
        delegate/comboboxdelegate.h \
        delegate/controldelegate.h \
        delegate/datedelegate.h \
        form/staffinfodialog.h \
        form/departmentinfodialog.h \
        form/logindialog.h \
        form/mainwindow.h \
        form/systemmanagerdialog.h \
        form/tableinfodialog.h  \
        controlext/standerlineedit.h \
        controlext/standercombobox.h

FORMS += \
        form/departmentinfodialog.ui \
        form/logindialog.ui \
        form/mainwindow.ui \
        form/staffinfodialog.ui \
        form/systemmanagerdialog.ui \
        form/tableinfodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
