#-------------------------------------------------
#
# Project created by QtCreator 2018-12-26T13:15:15
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camera
TEMPLATE = app

target.path=/home/test
INSTALLS += target

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32: LIBS += -L$$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/x64/mingw/bin/ -llibopencv_core452 -llibopencv_highgui452 -llibopencv_imgproc452 -llibopencv_calib3d452 -llibopencv_imgcodecs452 -llibopencv_videoio452

INCLUDEPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include
DEPENDPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include


