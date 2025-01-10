QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CaptureThread.cpp \
    DisplayThread.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CaptureThread.h \
    DisplayThread.h \
    FrameData.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/x64/mingw/bin/ -llibopencv_core452 -llibopencv_highgui452 -llibopencv_imgproc452 -llibopencv_calib3d452 -llibopencv_imgcodecs452 -llibopencv_videoio452

INCLUDEPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include
DEPENDPATH += $$PWD/OpenCV-MinGW-Build-OpenCV-4.5.2-x64/include
