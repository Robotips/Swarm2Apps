#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T16:33:13
#
#-------------------------------------------------

QT       += core gui widgets xml network
#Icon du programme
RC_FILE = myapp.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Swarm2monitor
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


SOURCES += main.cpp\
        mainwindow.cpp \
    robotipmodal.cpp \
    userdata.cpp \
    dataserializerunserializer.cpp \
    logwidget.cpp \
    speedometer/qcgaugewidget.cpp \
    colorWheel/colorwheel.cpp \
    settingsdialog.cpp \
    controller/robot.cpp \
    controller/comdriver.cpp \
    controller/apiobject.cpp \
    controller/swarm2tipsInterface.cpp \
    controller/apimanager.cpp \
    controller/robotinterface.cpp

HEADERS  += mainwindow.h \
    robotipmodal.h \
    userdata.h \
    dataserializerunserializer.h \
    logwidget.h \
    speedometer/qcgaugewidget.h \
    colorWheel/colorwheel.h \
    settingsdialog.h \
    controller/robot.h \
    controller/comdriver.h \
    controller/apiobject.h \
    controller/swarm2tipsInterface.h \
    controller/robotinterface.h \
    controller/apimanager.h

TRANSLATIONS = translation_fr.ts

DISTFILES +=

