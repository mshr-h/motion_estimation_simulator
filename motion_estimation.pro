QT += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    include/motion_estimation.h \
    include/mainwindow.h \
    include/implab.h \
    include/processor_element.h

FORMS += \
    mainwindow.ui

SOURCES += \
    main.cpp \
    implab/img_copy.c \
    implab/img_create.c \
    implab/img_destruct.c \
    implab/img_diff.c \
    implab/img_rgb_create.c \
    implab/img_rgb_destruct.c \
    implab/img_yuv_create.c \
    implab/img_yuv_destruct.c \
    implab/Malloc2D_uchr.c \
    implab/img_rgb_to_yuv.c \
    motion_estimation/fullsearch.c \
    motion_estimation/me_block_create.c \
    motion_estimation/me_block_destruct.c \
    motion_estimation/me_block_reconstruct.c \
    motion_estimation/mvec_table_destruct.c \
    motion_estimation/mvec_table_craete.c \
    motion_estimation/processor_element/pe_diff_exor.c \
    motion_estimation/processor_element/pe_diff.c \
    motion_estimation/fullsearch_4pix_only.c \
    motion_estimation/me_block_calc_average_cost.c \
    lib_q/mainwindow.cpp \
    lib_q/setupProcessorElement.cpp \
    lib_q/setupSearchMethod.cpp \
    lib_q/getResults.cpp \
    lib_q/imgT/img_to_QImage.cpp \
    lib_q/imgT/loadImageToImg_yuv.cpp \
    lib_q/imgT/QImage_to_img_rgb.cpp
