#-------------------------------------------------
#
# Project created by QtCreator 2014-12-31T23:11:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = me
TEMPLATE = app


SOURCES += main.cpp\
				mainwindow.cpp \
    motion_estimation.cpp \
    QImage_to_img_rgb.cpp \
    img_motion_estimation.c \
    implab.c \
    fullsearch_8bit.c \
    fullsearch_4bit_4pix.c \
    fullsearch_4bit_4pix_dynamic.c \
    fullsearch_4bit_4pix_proposed.c

HEADERS  += mainwindow.h \
    include/implab.h \
    include/mainwindow.h \
    include/windows.h \
    include/motion_estimation.h

FORMS    += mainwindow.ui

OTHER_FILES +=
