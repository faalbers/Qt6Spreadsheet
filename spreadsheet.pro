#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T10:42:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spreadsheet.cpp \
    finddialog.cpp \
    gotocelldialog.cpp \
    sortdialog.cpp

HEADERS  += mainwindow.h \
    spreadsheet.h \
    finddialog.h \
    gotocelldialog.h \
    sortdialog.h

FORMS    += mainwindow.ui \
    gotocelldialog.ui \
    sortdialog.ui

RESOURCES += \
    spreadsheet.qrc
