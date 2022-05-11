QT       += core gui
QT += gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
#CONFIG += staticlib

QMAKE_CXXFLAGS += "/Zc:strictStrings-"


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CallBack.cpp \
    Controller.cpp \
    GmasInternals.cpp \
    IOType.cpp \
    MD5.cpp \
    formhelp.cpp \
    formpi.cpp \
    formsdo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CallBack.h \
    Controller.h \
    GmasInternals.h \
    IOType.h \
    IOType_Internals.h \
    MD5.h \
    enums.h \
    formhelp.h \
    formpi.h \
    formsdo.h \
    mainwindow.h

FORMS += \
    formhelp.ui \
    formpi.ui \
    formsdo.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += "c:\GMAS-294\includes"
INCLUDEPATH += "c:\GMAS-294\includes\CPP"
INCLUDEPATH += "c:\GMAS-294\includes\EMBL"

DEPENDPATH += C:/GMAS-294/libwin32

unix|win32: LIBS += -LC:/GMAS-294/libwin32/ -lmmc_lib
unix|win32: LIBS += -LC:/GMAS-294/libwin32/ -lmmcpp_lib

