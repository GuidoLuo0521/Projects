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
        #common/ntpclient.cpp \
        common/singleton.cpp \
        common/staffinfo.cpp \
        controlext/standerdateedit.cpp \
        controlext/standerinputstructer.cpp \
        controlext/standerrangeedit.cpp \
        controlext/standertextedit.cpp \
        database/cmsdatabase.cpp \
        database/cmsdatebasedef.cpp \
        delegate/datedelegate.cpp \
        delegate/readonlydelegate.cpp \
        delegate/comboboxdelegate.cpp \
        delegate/texteditdelegate.cpp \
        form/cmsbasewidget.cpp \
        form/departmentdatedialog.cpp \
        form/departmententrydialog.cpp \
        form/entryadddialog.cpp \
        form/jobdatedialog.cpp \
        form/jobentrydialog.cpp \
        form/mainwindow.cpp \
        form/profiledialog.cpp \
        form/roledatedialog.cpp \
        form/roleentrydialog.cpp \
        form/searchdialog.cpp \
        form/logindialog.cpp \
        form/staffdatedialog.cpp \
        form/staffentrydialog.cpp \
        form/systemmanagerdialog.cpp\
        form/tabledatedialog.cpp \
        controlext/standerlineedit.cpp \
        controlext/standercombobox.cpp \
        form/weeklyreportcommitdialog.cpp \
        form/weeklyreportdialog.cpp \
        form/weeklyreporthistorydialog.cpp \
        main.cpp

HEADERS += \
        common/commonapi.h \
        common/controlinclude.h \
        common/filedownloader.h \
        common/staffinfo.h \
        #common/ntpclient.h \
        common/singleton.h \
        controlext/controlext.h \
        controlext/standerdateedit.h \
        controlext/standerinputstructer.h \
        controlext/standerrangeedit.h \
        controlext/standertextedit.h \
        database/cmsdatabase.h \
        database/cmsdatebasedef.h \
        delegate/readonlydelegate.h \
        delegate/comboboxdelegate.h \
        delegate/controldelegate.h \
        delegate/datedelegate.h \
        delegate/texteditdelegate.h \
        form/cmsbasewidget.h \
        form/departmentdatedialog.h \
        form/departmententrydialog.h \
        form/entryadddialog.h \
        form/jobdatedialog.h \
        form/jobentrydialog.h \
        form/mainwindow.h \
        form/profiledialog.h \
        form/roledatedialog.h \
        form/roleentrydialog.h \
        form/searchdialog.h \
        form/logindialog.h \
        form/staffdatedialog.h \
        form/staffentrydialog.h \
        form/systemmanagerdialog.h \
        form/tabledatedialog.h  \
        controlext/standerlineedit.h \
        controlext/standercombobox.h \
        form/weeklyreportcommitdialog.h \
        form/weeklyreportdialog.h \
        form/weeklyreporthistorydialog.h

FORMS += \
        form/logindialog.ui \
        form/profiledialog.ui \
        form/searchdialog.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
