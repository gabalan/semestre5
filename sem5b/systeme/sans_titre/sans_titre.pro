#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T20:23:43
#
#-------------------------------------------------

QT       += widgets declarative qml quick network opengl sql script scripttools svg webengine webenginewidgets webkit webkitwidgets xml xmlpatterns phonon multimedia qt3support testlib dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = tst_ddd
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += tst_ddd.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
