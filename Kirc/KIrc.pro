#-------------------------------------------------
#
# Project created by QtCreator 2014-04-04T03:33:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = KIrc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    client.h \
    ircmessage.h \
    settingdialog.h

FORMS    += mainwindow.ui \
    settingdialog.ui

#
CONFIG += c++11
