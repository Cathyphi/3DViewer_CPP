QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include("QtGifImage/src/gifimage/qtgifimage.pri")

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/model.cc \
    main.cpp \
    myopenglwidget.cpp \
    viewer.cpp

HEADERS += \
    ../Controller/controller.h \
    ../Controller/facade.h \
    ../Controller/observer.h \
    ../Controller/singleton.h \
    ../Model/model.h \
    controller.h \
    facade.h \
    model.h \
    myopenglwidget.h \
    observer.h \
    singleton.h \
    viewer.h

FORMS += \
    viewer.ui


macx:ICON = 3D.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3D.icns \



SUBDIRS += \



