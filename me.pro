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
    implab/img_create.c \
    implab/img_destruct.c \
    implab/img_copy.c \
    implab/img_rgb_create.c \
    implab/img_rgb_destruct.c \
    implab/img_yuv_create.c \
    implab/img_yuv_destruct.c \
    implab/base/Malloc2D_uchr.c \
    search_method/fullsearch_4pix.c \
    search_method/fullsearch.c \
    processor_element/pe_4bit_proposed1.c \
    processor_element/pe_4bit_proposed2.c \
    processor_element/pe_4bit_dynamic.c \
    processor_element/pe_Nbit.c \
    processor_element/pe_Nbit_xor.c \
    processor_element/pe_mix_diff_xor.c

HEADERS  += mainwindow.h \
	include/implab.h \
	include/mainwindow.h \
	include/windows.h \
	include/motion_estimation.h \
	include/search_method.h \
	include/processor_element.h

FORMS    += mainwindow.ui

OTHER_FILES +=

DISTFILES +=
