QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RegexTrainer
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        regexexamples.cpp \
        regexhelper.cpp

HEADERS += \
        mainwindow.h \
        regexexamples.h \
        regexhelper.h

FORMS += \
        mainwindow.ui

win32 {
        RC_FILE += file.rc
        OTHER_FILES += file.rc
}
