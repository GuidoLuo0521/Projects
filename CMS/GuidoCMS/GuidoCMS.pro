#-------------------------------------------------
#
# Project created by QtCreator 2021-08-08T01:14:56
#
#-------------------------------------------------

QT += core gui
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
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        common/commonapi.cpp \
        common/filedownloader.cpp \
        common/ntpclient.cpp \
        common/singleton.cpp \
        common/staffinfo.cpp \
        controlext/standerdateedit.cpp \
        controlext/standerinputstructer.cpp \
        controlext/standerplaintextedit.cpp \
        controlext/standerrangeedit.cpp \
        database/cmsdatabase.cpp \
        database/cmsdatebasedef.cpp \
        delegate/datedelegate.cpp \
        delegate/readonlydelegate.cpp \
        delegate/comboboxdelegate.cpp \
        form/addtableinfodepartmentdialog.cpp \
        form/addtableinfodialog.cpp \
        form/addtableinfojobdialog.cpp \
        form/addtableinforoledialog.cpp \
        form/addtableinfostaffdialog.cpp \
        form/searchdialog.cpp \
        form/logindialog.cpp \
        form/systemmanagerdialog.cpp\
        controlext/standerlineedit.cpp \
        controlext/standercombobox.cpp \
        form/tabledepartmentmanagerdialog.cpp \
        form/tablejobmanagerdialog.cpp \
        form/tablemanagerdialog.cpp \
        form/tablerolemanagerdialog.cpp \
        form/tablestaffmanagerdialog.cpp \
        main.cpp

HEADERS += \
        common/commonapi.h \
        common/controlinclude.h \
        common/filedownloader.h \
        common/staffinfo.h \
        common/ntpclient.h \
        common/singleton.h \
        controlext/controlext.h \
        controlext/standerdateedit.h \
        controlext/standerinputstructer.h \
        controlext/standerplaintextedit.h \
        controlext/standerrangeedit.h \
        database/cmsdatabase.h \
        database/cmsdatebasedef.h \
        delegate/readonlydelegate.h \
        delegate/comboboxdelegate.h \
        delegate/controldelegate.h \
        delegate/datedelegate.h \
        form/addtableinfodepartmentdialog.h \
        form/addtableinfodialog.h \
        form/addtableinfojobdialog.h \
        form/addtableinforoledialog.h \
        form/addtableinfostaffdialog.h \
        form/searchdialog.h \
        form/logindialog.h \
        form/systemmanagerdialog.h \
        controlext/standerlineedit.h \
        controlext/standercombobox.h \
        form/tabledepartmentmanagerdialog.h \
        form/tablejobmanagerdialog.h \
        form/tablemanagerdialog.h \
        form/tablerolemanagerdialog.h \
        form/tablestaffmanagerdialog.h

FORMS += \
        form/logindialog.ui \
        form/searchdialog.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
